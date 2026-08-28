#ifndef DELETEHISTORYDIALOG_H
#define DELETEHISTORYDIALOG_H

#include <QDialog>
#include<QListWidget>

#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QLabel>
#include<QDateTime>
#include<QMessageBox>
#include<QTextStream>

#include<QSqlError>
#include<QSqlQuery>

#include<QMenu>
#include<QFile>

class DeleteHistoryDialog : public QDialog
{
    Q_OBJECT
public:
    explicit DeleteHistoryDialog(QWidget *parent = nullptr);
    void loadDeleteHistory();
private:
    void setupUI();
    QListWidget *listWidget;
private slots:
    void showDeleteMenu(const QPoint &pos);//参数pos是鼠标点击的位置坐标
    void deleteSeletcRecords();//删除选中的记录
private:
    void refreshHistory();//刷新列表

};

#endif // DELETEHISTORYDIALOG_H
