#ifndef DEEPSEEKAIASSISTANTS_H
#define DEEPSEEKAIASSISTANTS_H

#include <QWidget>

#include<QSqlQuery>
#include<QSqlDatabase>
#include<QSqlError>

#include<QMessageBox>

#include<QNetworkAccessManager>
#include<QNetworkRequest>
#include<QNetworkReply>

#include<QElapsedTimer>  //高精度计时器
#include<QTimer>  //定时器

#include<QJsonDocument>  //json文档解析操作
#include<QJsonObject>
#include<QJsonArray>

#include<QListWidgetItem>
#include<QListWidget>

#include<QMenu>

//引入加密哈希计算头文件
#include<QCryptographicHash>
#include<QInputDialog>

#include"deletehistorydialog.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class DeepSeekAIAssistants;
}
QT_END_NAMESPACE

class DeepSeekAIAssistants : public QWidget
{
    Q_OBJECT

public:
    DeepSeekAIAssistants(QWidget *parent = nullptr);
    ~DeepSeekAIAssistants();

    void setupDatabase();//初始化数据库连接
    //网络请求管理
    QNetworkAccessManager *networkManager;
    QElapsedTimer elapsedTimer;
    QTimer *timer;

    void saveAnswer(const QString &answer);

    void loadHistory();//加载历史记录

    QString getAnswerForQuestion(const QString &question);//获取历史回答

    void updateTimeLabel();

    void saveQuestion(const QString &question);//保存提问记录

    void showDeletelistContextMenu(const QPoint &pos);

    int m_loginAttempts = 0;//记录密码错误次数
    bool m_isLocked;
    QTimer *m_unlockTimer;//解锁计时器
    QByteArray getStorePasswordHash();


private slots:
    //网络响应处理
    void onResponseReceived(QNetworkReply *reply);


    void on_listWidget_History_itemClicked(QListWidgetItem *item);

    void onDownloadProgress(qint64 bytesReceived,qint64 bytesTotal);//下载进度

    void on_pushButton_Commit_clicked();

    void on_pushButton_Exit_clicked();

    void on_pushButton_Admin_clicked();

private:
    Ui::DeepSeekAIAssistants *ui;
};
#endif // DEEPSEEKAIASSISTANTS_H
