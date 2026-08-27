#include "deepseekaiassistants.h"
#include "ui_deepseekaiassistants.h"

DeepSeekAIAssistants::DeepSeekAIAssistants(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DeepSeekAIAssistants)
{
    ui->setupUi(this);

    // 设置记录标签样式
    ui->label_history->setStyleSheet("QLabel{color:white;font-size:16px;font-weight:bold;}");
    ui->label_Question->setStyleSheet("QLabel{color:white;font-size:16px;font-weight:bold;}");
    ui->label_Response->setStyleSheet("QLabel{color:white;font-size:16px;font-weight:bold;}");
    ui->label_Time->setStyleSheet("QLabel{color:white;font-size:16px;font-weight:bold;}");

    // 设置历史记录列表控件样式
    ui->listWidget_History->setStyleSheet("QListWidget{background-color:rgba(255,255,255,0.8); border-radius:2px;padding:10px;}"
                                          "QListWidget::item{padding:5px;border-bottom:1px solid #ccc;}"
                                          "QListWidget::item:hover{background-color:#e0e0e0;}");

    // 设置窗口背景为渐变颜色
    this->setStyleSheet("background:qlineargradient(x1:0,y1:0,x2:1,y2:1,stop:0 #1e3c72,stop:1 #3a5298);");

    // 设置输入框控件样式
    ui->lineEdit_Input->setStyleSheet(
        "QLineEdit{background-color:rgba(255,255,255,0.8);border-radius:2px;padding:5px;font-size:14px;}");


    // 设置命令按钮控件样式
    ui->pushButton_Exit->setStyleSheet("QPushButton{background-color:#ff6666;color:white;border:none;padding:10px 20px;border-radius:2px;font-size:14px;}"
                                       "QPushButton:hover{background-color:#ff4d4d;}"
                                       "QPushButton:focus{outline:onoe;border:1px solid #fff;}"
                                       );

    ui->pushButton_Commit->setStyleSheet("QPushButton{background-color:#66cc66;color:white;border:none;padding:10px 20px;border-radius:2px;font-size:14px;}"
                                         "QPushButton:hover{background-color:#5cb85c;}"
                                         "QPushButton:focus{outline:onoe;border:1px solid #fff;}"
                                         );

    ui->pushButton_Admin->setStyleSheet("QPushButton{background-color:#6666ff;color:white;border:none;padding:10px 20px;border-radius:2px;font-size:14px;}"
                                        "QPushButton:hover{background-color:#5c5cff;}"
                                        "QPushButton:focus{outline:onoe;border:1px solid #fff;}"
                                        );

    // 设置文本框控件样式
    ui->textEdit_context->setStyleSheet("QTextEdit{background-color:rgba(255,255,255,0.8);border-radius:2px;padding:10px;}"
                                        "QTextEdit:hover{background-color:rgba(255,255,255,0.9);}"
                                        "QTextEdit:focus{border:1px solid #66ccff;}");


    // 设置进度条控件样式
    ui->progressBar->setStyleSheet("QProgressBar{background-color:rgba(255,255,255,0.8);border-radius:2px;height:10px;}"
                                   "QProgressBar:chunk{background-color:#66cc66;border-radius:2px;}");


    setupDatabase();

    ui->progressBar->setRange(0,100);
    ui->progressBar->setValue(0);

    networkManager = new QNetworkAccessManager(this);
    connect(networkManager,&QNetworkAccessManager::finished,this,&DeepSeekAIAssistants::onResponseReceived);

    loadHistory();//加载历史提问
    timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,&DeepSeekAIAssistants::updateTimeLabel);

    //右键菜单
    ui->listWidget_History->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->listWidget_History,&QWidget::customContextMenuRequested,this,&DeepSeekAIAssistants::showDeletelistContextMenu);
    ui->listWidget_History->setSelectionMode(QAbstractItemView::ExtendedSelection);


}

DeepSeekAIAssistants::~DeepSeekAIAssistants()
{
    delete ui;
}
void DeepSeekAIAssistants::setupDatabase(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("ai_assiatant.db");

    if(!db.open()){
        QMessageBox::critical(this,"数据库连接错误","Prompt:Failed to pen database:"+db.lastError().text());
        return;
    }
    //创建数据库（如果不存在）
    QSqlQuery query;
    query.exec("create table if not exists history("
            "id integer primary key autoincrement,"
            "question TEXT,"
            "answer TEXT);");
    //创建新表
    query.exec("create table if not exists deleted_history("
            "deleted_id integer primary key autoincrement,"
            "original_id integer not null,"
            "question text not null,"
            "answer text,"
            "deleted_date datetime not null);");


}
void DeepSeekAIAssistants::onResponseReceived(QNetworkReply *reply){
    if(reply->error()==QNetworkReply::NoError){
        QByteArray respinseData = reply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(respinseData);
        QJsonObject jsonObject = jsonResponse.object();

        //检查json中是否包含"choices"字段
        if(jsonObject.contains("choices")){
            QJsonArray choices = jsonObject["choices"].toArray();
            if(!choices.isEmpty()){
                QJsonObject firstChoices = choices[0].toObject();

                QString assistantResponse = firstChoices["message"].toObject()["content"].toString();

                ui->textEdit_context->append("Assistant:"+assistantResponse);

                saveAnswer(assistantResponse);
            }

        }
    }else{
        ui->textEdit_context->append("Error:"+reply->errorString());
    }
    ui->progressBar->setValue(100);
    timer->stop();
    qint64 elapsedSeconds=elapsedTimer.elapsed()/1000;
    ui->label_Time->setText("Time elapsed: "+QString::number(elapsedSeconds)+" seconds");

    reply->deleteLater();

}
void DeepSeekAIAssistants::saveAnswer(const QString &answer){
    QSqlQuery query;
    query.prepare("update history set answer=:answer where id=(select max(id) from history)");
    query.bindValue(":answer",answer);

    if(!query.exec()){
        QMessageBox::critical(this,"Database Error","Prompt:Failed to save answer:"+query.lastError().text());

        return;
    }
}
void DeepSeekAIAssistants::loadHistory(){
    QSqlQuery query("select id,question from history");
    while(query.next()){
        int id = query.value(0).toInt();
        QString question = query.value(1).toString();
        QListWidgetItem *item = new QListWidgetItem(question);
        item->setData(Qt::UserRole,id);
        ui->listWidget_History->addItem(item);
    }
}

void DeepSeekAIAssistants::on_listWidget_History_itemClicked(QListWidgetItem *item)
{
    //点击历史提问时候，要显示对应的回答内容
    QString question = item->text();
    QString answer = getAnswerForQuestion(question);

    ui->textEdit_context->clear();
    ui->textEdit_context->append("Question:"+question);
    ui->textEdit_context->append("Answer:"+answer);

}
QString DeepSeekAIAssistants::getAnswerForQuestion(const QString &question){//获取历史回答
    //获取历史回答
    QSqlQuery query;
    query.prepare("Select answer from history where question=:question");
    query.bindValue(":question",question);

    if(query.exec()&&query.next()){
        return query.value(0).toString();
    }
    return "No answer found.";
}
void DeepSeekAIAssistants::updateTimeLabel(){
    //更新计时器显示
    qint64 elapsedSeconds = elapsedTimer.elapsed()/1000;
    ui->label_Time->setText("Time elapsed:"+QString::number(elapsedSeconds)+"seconds");

}
void DeepSeekAIAssistants::saveQuestion(const QString &question){
    QSqlQuery query;
    query.prepare("insert into history (question) values(:question)");
    query.bindValue(":question",question);
    if(!query.exec()){
        QMessageBox::warning(this,"Database ERROR","Failed to save question:"+query.lastError().text());
    }else{
        //处理执行成功后的操作
        int newid = query.lastInsertId().toInt();
        QListWidgetItem *newItem = new QListWidgetItem(question);
        newItem->setData(Qt::UserRole,newid);//将数据库id存储在列表项的UserRole数据当中
        ui->listWidget_History->addItem(newItem);
    }

}
void DeepSeekAIAssistants::onDownloadProgress(qint64 bytesReceived,qint64 bytesTotal){//下载进度
    if(bytesTotal>0){
        int progress = static_cast<int>((bytesReceived*100)/bytesTotal);
        ui->progressBar->setValue(progress);
    }
}

void DeepSeekAIAssistants::on_pushButton_Commit_clicked()
{
    QString userInput = ui->lineEdit_Input->text();

    if(userInput.isEmpty()){
        QMessageBox::critical(this,"ERROR","Input cannot be empty");
        return;
    }
    //构造请求数据
    QJsonObject requestData;
    requestData["model"] = "deepseek-v4-pro";
    requestData["stream"] = false;
    requestData["max_tokens"] = 2048;
    requestData["temperature"] = 0.7;

    QJsonArray messages;

    QJsonObject systemMessage;
    systemMessage["role"] = "system";
    systemMessage["content"] = "You are a helpful assistant.";
    messages.append(systemMessage);

    QJsonObject userMessage;
    userMessage["role"] = "user";
    userMessage["content"] = userInput;
    messages.append(userMessage);

    requestData["messages"] = messages;

    QJsonDocument doc(requestData);
    QByteArray data = doc.toJson();

    QNetworkRequest request(QUrl("https://api.deepseek.com/chat/completions"));
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    request.setRawHeader("Authorization","Bearer sk-af85dd698b40450ca644e0125a6e85bb");
    request.setRawHeader("Accept","application/json");
    //request.setRawHeader("Authorization","Bearer sk-把Key填写到这里就可以");

    //使用网络管理器发送post请求
    QNetworkReply *reply = networkManager->post(request,data);
    connect(reply,&QNetworkReply::downloadProgress,this,&DeepSeekAIAssistants::onDownloadProgress);
    saveQuestion(userInput);

    ui->progressBar->setValue(0);

    elapsedTimer.start();
    timer->start(1000);
    ui->label_Time->setText("Time elapsed: 0 seconds");
}


void DeepSeekAIAssistants::on_pushButton_Exit_clicked()
{
    QApplication::quit();
}
void DeepSeekAIAssistants::showDeletelistContextMenu(const QPoint &pos){
    //显示历史记录右键菜单
    QList<QListWidgetItem*>selectedItems = ui->listWidget_History->selectedItems();
    if(selectedItems.isEmpty())return;
    QMenu contextMenu(this);
    QAction *deleteAction = new QAction("删除历史记录",this);
    //连接删除动作的trigered信号
    connect(deleteAction,&QAction::triggered,this,[this,selectedItems](){
        QMessageBox::StandardButton reply = QMessageBox::warning(this,"删除确认","确定要删除选中的历史记录吗？\n删除后数据将不可恢复！",QMessageBox::Yes|QMessageBox::No);
        if(reply!=QMessageBox::Yes)return;
        QSqlDatabase db = QSqlDatabase::database();
        if(!db.isOpen()){
            QMessageBox::critical(this,"错误","系统提示：数据库连接异常！");
            return;
        }
        bool transactionOk = true;
        QVector<int> deletedids;
        db.transaction();
        for(QListWidgetItem *item:selectedItems){
            if(!item)continue;
            int recordid = item->data(Qt::UserRole).toInt();
            QSqlQuery selectQuery;
            selectQuery.prepare("Select question,answer From history where id=?");
            selectQuery.addBindValue(recordid);
            if(!selectQuery.exec()||!selectQuery.next()){
                transactionOk = false;
                QMessageBox::critical(this,"错误",QString("无法读取记录：%1").arg(selectQuery.lastError().text()));
                break;//查询失败，终止
            }
            QString question = selectQuery.value(0).toString();
            QString answer = selectQuery.value(1).toString();

            QSqlQuery insertQuery;
            insertQuery.prepare("insert into deleted_history"
                              "(original_id,question,answer,deleted_date)"
                              "values(?,?,?,?);"
                              );
            insertQuery.addBindValue(recordid);
            insertQuery.addBindValue(question);
            insertQuery.addBindValue(answer);
            insertQuery.addBindValue(QDateTime::currentDateTime());

            if(!insertQuery.exec()){
                transactionOk = false;
                QMessageBox::critical(this,"错误",QString("系统提示：备份失败：%1").arg(insertQuery.lastError().text()));
                break;//备份失败
            }
            //删除原始记录
            QSqlQuery deleteQuery;
            deleteQuery.prepare("DELETE from history where id=?");
            deleteQuery.addBindValue(recordid);
            if(!deleteQuery.exec()){
                transactionOk = false;
                QMessageBox::critical(this,"错误",QString("系统提示：删除失败：%1").arg(insertQuery.lastError().text()));
                break;//删除失败
            }
            deletedids.append(recordid);//记录删除的ID

        }
        //根据事务执行情况提交或者回滚
        if(transactionOk && db.commit()){
            qDeleteAll(selectedItems);
        }else{
            db.rollback();
            QMessageBox::critical(this,"错误","系统提示：操作已回滚！");
        }

    });
    contextMenu.addAction(deleteAction);
    contextMenu.exec(ui->listWidget_History->mapToGlobal(pos));

}

void DeepSeekAIAssistants::on_pushButton_Admin_clicked()
{

}

