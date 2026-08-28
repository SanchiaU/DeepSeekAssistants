#include "deletehistorydialog.h"

DeleteHistoryDialog::DeleteHistoryDialog(QWidget *parent):QDialog(parent){
    setupUI();
    loadDeleteHistory();
}
void DeleteHistoryDialog::setupUI(){

    setWindowTitle("管理员：查阅删除历史记录");
    setFixedSize(650,400);
    setStyleSheet("background:qlineargradient(x1:0,y1:0,x2:0,y2:1,stop:0 #2c3e50,stop:1 #3498db);");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QLabel *titleLabel = new QLabel("已经删除的记录列表");
    mainLayout->addWidget(titleLabel);

    listWidget = new QListWidget();
    listWidget->setStyleSheet("QListWidget{background-color:rgba(255,255,255,0.9);border-radius:8px;padding:5px;}"
                              "QListWidget:item{padding:8px;border-bottom:1px solid #ddd}"
                              "QListWidget::item:hover{background-color:#e8f4ff}");
    mainLayout->addWidget(listWidget);

    listWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(listWidget,&QListWidget::customContextMenuRequested,this,&DeleteHistoryDialog::showDeleteMenu);

}
void DeleteHistoryDialog::loadDeleteHistory(){
    //查询已经删除的记录
    QSqlQuery query("select original_id,question,deleted_date from deleted_history order by deleted_date desc");
    if(!query.exec()){
        QMessageBox::critical(this,"错误","系统提示：无法加载历史记录："+query.lastError().text());
        return;
    }
    while(query.next()){
        int originalId = query.value(0).toInt();
        QString question = query.value(1).toString();
        QDateTime deleteTime = query.value(2).toDateTime();

        QString displayText = QString("[ID:%1] %2\n删除时间%3").arg(originalId).arg(question.left(50)).arg(deleteTime.toString("yyyy-MM-dd HH:mm:ss"));
        QListWidgetItem *item = new QListWidgetItem(displayText);
        item->setData(Qt::UserRole,originalId);
        item->setToolTip(QString("QUESTION:%1\n").arg(question));
        listWidget->addItem(item);
    }
}


void DeleteHistoryDialog::showDeleteMenu(const QPoint &pos){
    QMenu menu(this);
    QAction *deleteAction = menu.addAction("永久删除");

    connect(deleteAction,&QAction::triggered,this,&DeleteHistoryDialog::deleteSeletcRecords);
    menu.exec(listWidget->mapToGlobal(pos));
}
void DeleteHistoryDialog::deleteSeletcRecords(){
    QList<QListWidgetItem*>selected = listWidget->selectedItems();
    if(selected.isEmpty()){
        return;
    }
    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        "确认删除",
        QString("系统提示：确认要永久删除选中的%1条记录吗？").arg(selected.size()),
        QMessageBox::Yes|QMessageBox::No);
    if(reply!=QMessageBox::Yes)return;
    QSqlDatabase db = QSqlDatabase::database();
    if(!db.isOpen()){
        QMessageBox::critical(this,"错误","系统提示：数据库连接失败，请重新检查？");
        return;
    }
    QFile logFile("operation.log");
    if(!logFile.open(QIODevice::Append|QIODevice::Text)){
        QMessageBox::warning(this,"警告","系统提示：无法写入日志，请重新检查？");
    }
    db.transaction();
    bool success = true;
    foreach(QListWidgetItem *item,selected){
        int originalId = item->data(Qt::UserRole).toInt();
        QString question = item->toolTip().split("\n")[0].mid(9);
        QSqlQuery query;
        query.prepare("delete from deleted_history where original_id=?");
        query.addBindValue(originalId);
        if(!query.exec()){
            QMessageBox::critical(this,"错误",QString("系统提示：删除失败：%1\n%2").arg(query.lastError().text()).arg(query.lastQuery()));
            break;
        }
        if(logFile.isOpen()){
            QTextStream stream(&logFile);
            stream<<QDateTime::currentDateTime().toString("[yyyy-MM-dd HH:mm:ss]")
                   <<"DELETE_PREMANENT|ID:"<<originalId
                   <<"|QUESTION:"<<question<<"\n";
        }
    }
    if(success){
        db.commit();
        refreshHistory();
        QMessageBox::information(this,"成功","系统提示，已永远删除选定记录！！！");
    }else{
        db.rollback();
        QMessageBox::information(this,"失败","系统提示：操作已经回滚！！！");
    }


}
void DeleteHistoryDialog::refreshHistory(){
    listWidget->clear();
    loadDeleteHistory();
}
