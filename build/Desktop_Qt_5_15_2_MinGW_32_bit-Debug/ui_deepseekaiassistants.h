/********************************************************************************
** Form generated from reading UI file 'deepseekaiassistants.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEEPSEEKAIASSISTANTS_H
#define UI_DEEPSEEKAIASSISTANTS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DeepSeekAIAssistants
{
public:
    QGridLayout *gridLayout;
    QWidget *LeftLayout_2;
    QVBoxLayout *LeftLayout;
    QLabel *label_history;
    QListWidget *listWidget_History;
    QWidget *RightLeftout;
    QVBoxLayout *RightLayout_2;
    QLabel *label_Question;
    QLineEdit *lineEdit_Input;
    QWidget *leftrightpushbutton;
    QHBoxLayout *IrhorizontalLayout;
    QPushButton *pushButton_Exit;
    QPushButton *pushButton_Commit;
    QPushButton *pushButton_Admin;
    QLabel *label_Response;
    QTextEdit *textEdit_context;
    QProgressBar *progressBar;
    QLabel *label_Time;

    void setupUi(QWidget *DeepSeekAIAssistants)
    {
        if (DeepSeekAIAssistants->objectName().isEmpty())
            DeepSeekAIAssistants->setObjectName(QString::fromUtf8("DeepSeekAIAssistants"));
        DeepSeekAIAssistants->resize(1230, 832);
        gridLayout = new QGridLayout(DeepSeekAIAssistants);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        LeftLayout_2 = new QWidget(DeepSeekAIAssistants);
        LeftLayout_2->setObjectName(QString::fromUtf8("LeftLayout_2"));
        LeftLayout_2->setMaximumSize(QSize(300, 16777215));
        LeftLayout = new QVBoxLayout(LeftLayout_2);
        LeftLayout->setObjectName(QString::fromUtf8("LeftLayout"));
        label_history = new QLabel(LeftLayout_2);
        label_history->setObjectName(QString::fromUtf8("label_history"));

        LeftLayout->addWidget(label_history);

        listWidget_History = new QListWidget(LeftLayout_2);
        listWidget_History->setObjectName(QString::fromUtf8("listWidget_History"));

        LeftLayout->addWidget(listWidget_History);


        gridLayout->addWidget(LeftLayout_2, 0, 0, 1, 1);

        RightLeftout = new QWidget(DeepSeekAIAssistants);
        RightLeftout->setObjectName(QString::fromUtf8("RightLeftout"));
        RightLayout_2 = new QVBoxLayout(RightLeftout);
        RightLayout_2->setObjectName(QString::fromUtf8("RightLayout_2"));
        label_Question = new QLabel(RightLeftout);
        label_Question->setObjectName(QString::fromUtf8("label_Question"));

        RightLayout_2->addWidget(label_Question);

        lineEdit_Input = new QLineEdit(RightLeftout);
        lineEdit_Input->setObjectName(QString::fromUtf8("lineEdit_Input"));

        RightLayout_2->addWidget(lineEdit_Input);

        leftrightpushbutton = new QWidget(RightLeftout);
        leftrightpushbutton->setObjectName(QString::fromUtf8("leftrightpushbutton"));
        IrhorizontalLayout = new QHBoxLayout(leftrightpushbutton);
        IrhorizontalLayout->setObjectName(QString::fromUtf8("IrhorizontalLayout"));
        pushButton_Exit = new QPushButton(leftrightpushbutton);
        pushButton_Exit->setObjectName(QString::fromUtf8("pushButton_Exit"));

        IrhorizontalLayout->addWidget(pushButton_Exit);

        pushButton_Commit = new QPushButton(leftrightpushbutton);
        pushButton_Commit->setObjectName(QString::fromUtf8("pushButton_Commit"));

        IrhorizontalLayout->addWidget(pushButton_Commit);

        pushButton_Admin = new QPushButton(leftrightpushbutton);
        pushButton_Admin->setObjectName(QString::fromUtf8("pushButton_Admin"));

        IrhorizontalLayout->addWidget(pushButton_Admin);


        RightLayout_2->addWidget(leftrightpushbutton);

        label_Response = new QLabel(RightLeftout);
        label_Response->setObjectName(QString::fromUtf8("label_Response"));

        RightLayout_2->addWidget(label_Response);

        textEdit_context = new QTextEdit(RightLeftout);
        textEdit_context->setObjectName(QString::fromUtf8("textEdit_context"));

        RightLayout_2->addWidget(textEdit_context);

        progressBar = new QProgressBar(RightLeftout);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(24);

        RightLayout_2->addWidget(progressBar);

        label_Time = new QLabel(RightLeftout);
        label_Time->setObjectName(QString::fromUtf8("label_Time"));

        RightLayout_2->addWidget(label_Time);


        gridLayout->addWidget(RightLeftout, 0, 1, 1, 1);


        retranslateUi(DeepSeekAIAssistants);

        QMetaObject::connectSlotsByName(DeepSeekAIAssistants);
    } // setupUi

    void retranslateUi(QWidget *DeepSeekAIAssistants)
    {
        DeepSeekAIAssistants->setWindowTitle(QCoreApplication::translate("DeepSeekAIAssistants", "DeepSeekAIAssistants", nullptr));
        label_history->setText(QCoreApplication::translate("DeepSeekAIAssistants", "Access history", nullptr));
        label_Question->setText(QCoreApplication::translate("DeepSeekAIAssistants", "Please enter the question:", nullptr));
        pushButton_Exit->setText(QCoreApplication::translate("DeepSeekAIAssistants", "Exit", nullptr));
        pushButton_Commit->setText(QCoreApplication::translate("DeepSeekAIAssistants", "commit", nullptr));
        pushButton_Admin->setText(QCoreApplication::translate("DeepSeekAIAssistants", "administrator", nullptr));
        label_Response->setText(QCoreApplication::translate("DeepSeekAIAssistants", "DeepSeekAssistant Response:", nullptr));
        label_Time->setText(QCoreApplication::translate("DeepSeekAIAssistants", "Time elapsed:0 seconds", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DeepSeekAIAssistants: public Ui_DeepSeekAIAssistants {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEEPSEEKAIASSISTANTS_H
