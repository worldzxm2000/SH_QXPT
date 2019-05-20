/********************************************************************************
** Form generated from reading UI file 'MainWnd.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWND_H
#define UI_MAINWND_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>
#include "SrvTableWidget.h"
#include "FcltyTableWidget.h"
QT_BEGIN_NAMESPACE

class Ui_Server_VSClass
{
public:
    QAction *actionDMTM;
    QAction *action1;
    QAction *action_SYSLog;
    QAction *action_DataLog;
    QWidget *centralWidget;
    QGroupBox *groupBox_Main;
    QGroupBox *groupBox_M;
    QPushButton *RemoveBtn;
    QPushButton *SettingBtn;
    QPushButton *LogBtn;
    QPushButton *AddBtn;
    QLabel *NameLabel;
    QLabel *ImageLabel;
    QGroupBox *groupBox_C;
    QPushButton *MinBtn;
    QPushButton *CloseBtn;
    QGroupBox *groupBox_F;
    FcltyTableWidget *ClientList;
    QGroupBox *groupBox_S;
    SrvTableWidget *ServerList;
    QLabel *OnLineCountLabel;
    QLabel *StatusLabel;
    QGroupBox *groupBox_CM;
    QTextEdit *Send_textEdit;
    QCheckBox *HexSwitchBtn;
    QPushButton *SndTxtBtn;
    QPushButton *ClearTxtBtn;
    QLabel *SndCountLabel;
    QCheckBox *ShowTxtSwitchBtn;
    QTextBrowser *RecvTxtBrower;

    void setupUi(QMainWindow *Server_VSClass)
    {
        if (Server_VSClass->objectName().isEmpty())
            Server_VSClass->setObjectName(QStringLiteral("Server_VSClass"));
        Server_VSClass->resize(1023, 533);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(10);
        Server_VSClass->setFont(font);
        QIcon icon;
        icon.addFile(QStringLiteral("../Image/png/Weather.ico"), QSize(), QIcon::Normal, QIcon::Off);
        Server_VSClass->setWindowIcon(icon);
        Server_VSClass->setWindowOpacity(1);
        Server_VSClass->setStyleSheet(QLatin1String("background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0  rgba(52,152,219, 255), stop:1 rgba(44, 62, 80, 255)); color:white;\n"
""));
        actionDMTM = new QAction(Server_VSClass);
        actionDMTM->setObjectName(QStringLiteral("actionDMTM"));
        action1 = new QAction(Server_VSClass);
        action1->setObjectName(QStringLiteral("action1"));
        action_SYSLog = new QAction(Server_VSClass);
        action_SYSLog->setObjectName(QStringLiteral("action_SYSLog"));
        action_DataLog = new QAction(Server_VSClass);
        action_DataLog->setObjectName(QStringLiteral("action_DataLog"));
        centralWidget = new QWidget(Server_VSClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setAutoFillBackground(false);
        centralWidget->setStyleSheet(QStringLiteral(""));
        groupBox_Main = new QGroupBox(centralWidget);
        groupBox_Main->setObjectName(QStringLiteral("groupBox_Main"));
        groupBox_Main->setGeometry(QRect(0, 0, 1024, 540));
        groupBox_Main->setStyleSheet(QStringLiteral("background:transparent;border-width: 2px;border-style: solid;border-color:transparent"));
        groupBox_M = new QGroupBox(groupBox_Main);
        groupBox_M->setObjectName(QStringLiteral("groupBox_M"));
        groupBox_M->setGeometry(QRect(5, 40, 191, 51));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(12);
        groupBox_M->setFont(font1);
        groupBox_M->setStyleSheet(QStringLiteral("background:transparent;border-width: 0px;border-style: solid;border-color: rgb(255, 255, 255);"));
        RemoveBtn = new QPushButton(groupBox_M);
        RemoveBtn->setObjectName(QStringLiteral("RemoveBtn"));
        RemoveBtn->setGeometry(QRect(55, 10, 35, 35));
        RemoveBtn->setStyleSheet(QLatin1String("QPushButton{background-color:transparent;border-width:0px;}\n"
"QPushButton:hover{border-width: 2px;border-style: solid;border-color: rgb(255, 255, 255);border-radius:5;}\n"
"QToolTip{border:0px;background:rgb(46,80,108,255);color:white}"));
        QIcon icon1;
        icon1.addFile(QStringLiteral("../Image/png/Remove.png"), QSize(), QIcon::Normal, QIcon::Off);
        RemoveBtn->setIcon(icon1);
        RemoveBtn->setIconSize(QSize(32, 32));
        SettingBtn = new QPushButton(groupBox_M);
        SettingBtn->setObjectName(QStringLiteral("SettingBtn"));
        SettingBtn->setGeometry(QRect(100, 10, 35, 35));
        SettingBtn->setStyleSheet(QLatin1String("QPushButton{background-color:transparent;border-width:0px;}\n"
"QPushButton:hover{border-width: 2px;border-style: solid;border-color: rgb(255, 255, 255);border-radius:5;}\n"
"QToolTip{border:0px;background:rgb(46,80,108,255);color:white}"));
        QIcon icon2;
        icon2.addFile(QStringLiteral("../Image/png/setting.png"), QSize(), QIcon::Normal, QIcon::Off);
        SettingBtn->setIcon(icon2);
        SettingBtn->setIconSize(QSize(32, 32));
        LogBtn = new QPushButton(groupBox_M);
        LogBtn->setObjectName(QStringLiteral("LogBtn"));
        LogBtn->setGeometry(QRect(145, 10, 35, 35));
        LogBtn->setStyleSheet(QLatin1String("QPushButton{background-color:transparent;border-width:0px;}\n"
"QPushButton:hover{border-width: 2px;border-style: solid;border-color: rgb(255, 255, 255);border-radius:5;}\n"
"QToolTip{border:0px;background:rgb(46,80,108,255);color:white}"));
        QIcon icon3;
        icon3.addFile(QStringLiteral("../Image/png/log.png"), QSize(), QIcon::Normal, QIcon::Off);
        LogBtn->setIcon(icon3);
        LogBtn->setIconSize(QSize(32, 32));
        AddBtn = new QPushButton(groupBox_M);
        AddBtn->setObjectName(QStringLiteral("AddBtn"));
        AddBtn->setGeometry(QRect(10, 10, 35, 35));
        AddBtn->setStyleSheet(QLatin1String("QPushButton{background-color:transparent;border-width:0px;}\n"
"QPushButton:hover{border-width: 2px;border-style: solid;border-color: rgb(255, 255, 255);border-radius:5;}\n"
"QToolTip{border:0px;background:rgb(46,80,108,255);color:white}"));
        QIcon icon4;
        icon4.addFile(QStringLiteral("../Image/png/Add.png"), QSize(), QIcon::Normal, QIcon::Off);
        AddBtn->setIcon(icon4);
        AddBtn->setIconSize(QSize(32, 32));
        NameLabel = new QLabel(groupBox_Main);
        NameLabel->setObjectName(QStringLiteral("NameLabel"));
        NameLabel->setGeometry(QRect(40, 10, 151, 20));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font2.setBold(true);
        font2.setItalic(true);
        font2.setWeight(75);
        NameLabel->setFont(font2);
        NameLabel->setStyleSheet(QStringLiteral("background:transparent;border-width: 0px;border-style: solid;border-color: rgb(255, 255, 255);"));
        ImageLabel = new QLabel(groupBox_Main);
        ImageLabel->setObjectName(QStringLiteral("ImageLabel"));
        ImageLabel->setGeometry(QRect(5, 5, 30, 30));
        ImageLabel->setStyleSheet(QStringLiteral("background:transparent;border-width: 0px;border-style: solid;border-color: rgb(255, 255, 255);"));
        ImageLabel->setPixmap(QPixmap(QString::fromUtf8("../Image/png/weather.png")));
        groupBox_C = new QGroupBox(groupBox_Main);
        groupBox_C->setObjectName(QStringLiteral("groupBox_C"));
        groupBox_C->setGeometry(QRect(970, 5, 51, 26));
        groupBox_C->setStyleSheet(QStringLiteral("background:transparent;border-width: 2px;border-style: solid;border-color: rgb(255, 255, 255);"));
        MinBtn = new QPushButton(groupBox_C);
        MinBtn->setObjectName(QStringLiteral("MinBtn"));
        MinBtn->setGeometry(QRect(5, 5, 16, 16));
        MinBtn->setStyleSheet(QLatin1String("QPushButton{background-color:transparent;border-width:0px;}\n"
"QPushButton:hover{border-width: 2px;border-style: solid;border-color: rgb(255, 255, 255);}\n"
"QToolTip{border:0px;background:rgb(46,80,108,255);color:white}"));
        QIcon icon5;
        icon5.addFile(QStringLiteral("../Image/png/minus.png"), QSize(), QIcon::Normal, QIcon::Off);
        MinBtn->setIcon(icon5);
        CloseBtn = new QPushButton(groupBox_C);
        CloseBtn->setObjectName(QStringLiteral("CloseBtn"));
        CloseBtn->setGeometry(QRect(30, 5, 16, 16));
        CloseBtn->setStyleSheet(QLatin1String("QPushButton{background-color:transparent;border-width:0px;}\n"
"QPushButton:hover{border-width: 2px;border-style: solid;border-color: rgb(255, 255, 255);}\n"
"QToolTip{border:0px;background:rgb(46,80,108,255);color:white}"));
        QIcon icon6;
        icon6.addFile(QStringLiteral("../Image/png/close.png"), QSize(), QIcon::Normal, QIcon::Off);
        CloseBtn->setIcon(icon6);
        groupBox_F = new QGroupBox(groupBox_Main);
        groupBox_F->setObjectName(QStringLiteral("groupBox_F"));
        groupBox_F->setGeometry(QRect(250, 100, 351, 400));
        groupBox_F->setFont(font1);
        groupBox_F->setStyleSheet(QStringLiteral("QGroupBox{border:2px solid rgb(255,255,255);margin-top: 3ex;border-radius:5;}QGroupBox::title {subcontrol-origin: margin;subcontrol-position: top left;left:10px; margin-left: 0px;padding:0 1px;}"));
        ClientList = new FcltyTableWidget(groupBox_F);
        ClientList->setObjectName(QStringLiteral("ClientList"));
        ClientList->setGeometry(QRect(15, 31, 321, 351));
        ClientList->setStyleSheet(QLatin1String("QListView {show-decoration-selected: 1;border-color:white;color:white; font:12pt}\n"
"QListView::item {min-height:40px; border-style: none;color: white;font: 12pt '\\346\\226\\260\\345\\256\\213\\344\\275\\223';}\n"
"QListView::item:selected { border: white; border-style: solid;background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 transparent, stop:0.01 transparent,stop:0.011 rgba(46,80,108,255), stop:1 rgba(46,80,108,255));color: white;}\n"
"QListView::item:hover {color: rgb(255,255,255);background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(255, 255, 255, 255), stop:0.01 rgba(255, 255, 255, 255),stop:0.011 #11998e, stop:1 #11998e)}"));
        groupBox_S = new QGroupBox(groupBox_Main);
        groupBox_S->setObjectName(QStringLiteral("groupBox_S"));
        groupBox_S->setGeometry(QRect(5, 100, 241, 400));
        groupBox_S->setFont(font1);
        groupBox_S->setStyleSheet(QStringLiteral("QGroupBox{border:2px solid rgb(255,255,255);margin-top: 3ex;border-radius:5;}QGroupBox::title {subcontrol-origin: margin;subcontrol-position: top left;left:10px; margin-left: 0px;padding:0 1px;}"));
        ServerList = new SrvTableWidget(groupBox_S);
        ServerList->setObjectName(QStringLiteral("ServerList"));
        ServerList->setGeometry(QRect(10, 30, 221, 341));
        ServerList->setStyleSheet(QLatin1String("QTableWidget{show-decoration-selected: 1;background:transparent;color:white;border-width: 2px;border-style: solid;border-color: rgb(255, 255, 255);font-size:20px;}\n"
"QTableWidget::item::selected{ background:rgba(46,80,108,255)}\n"
"QTableWidget::item::hover{ background:#11998e}"));
        OnLineCountLabel = new QLabel(groupBox_S);
        OnLineCountLabel->setObjectName(QStringLiteral("OnLineCountLabel"));
        OnLineCountLabel->setGeometry(QRect(10, 375, 211, 21));
        StatusLabel = new QLabel(groupBox_Main);
        StatusLabel->setObjectName(QStringLiteral("StatusLabel"));
        StatusLabel->setGeometry(QRect(5, 505, 1014, 25));
        QFont font3;
        font3.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        StatusLabel->setFont(font3);
        StatusLabel->setStyleSheet(QStringLiteral(""));
        groupBox_CM = new QGroupBox(groupBox_Main);
        groupBox_CM->setObjectName(QStringLiteral("groupBox_CM"));
        groupBox_CM->setEnabled(false);
        groupBox_CM->setGeometry(QRect(610, 100, 411, 401));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_CM->sizePolicy().hasHeightForWidth());
        groupBox_CM->setSizePolicy(sizePolicy);
        groupBox_CM->setFont(font1);
        groupBox_CM->setStyleSheet(QStringLiteral("QGroupBox{border:2px solid rgb(255,255,255);margin-top: 3ex;border-radius:5;}QGroupBox::title {subcontrol-origin: margin;subcontrol-position: top left;left:10px; margin-left: 0px;padding:0 1px;}"));
        groupBox_CM->setAlignment(Qt::AlignJustify|Qt::AlignTop);
        groupBox_CM->setFlat(false);
        Send_textEdit = new QTextEdit(groupBox_CM);
        Send_textEdit->setObjectName(QStringLiteral("Send_textEdit"));
        Send_textEdit->setGeometry(QRect(10, 280, 291, 111));
        Send_textEdit->setStyleSheet(QStringLiteral("border-width: 2px;border-style: solid;border-color: rgb(255, 255, 255);"));
        HexSwitchBtn = new QCheckBox(groupBox_CM);
        HexSwitchBtn->setObjectName(QStringLiteral("HexSwitchBtn"));
        HexSwitchBtn->setGeometry(QRect(310, 310, 71, 20));
        HexSwitchBtn->setStyleSheet(QLatin1String("QCheckBox{background-color:transparent;border-width:0px;}\n"
"QCheckBox:hover{border-width: 2px;border-style: solid;border-color: rgb(255, 255, 255);border-radius:5;}"));
        SndTxtBtn = new QPushButton(groupBox_CM);
        SndTxtBtn->setObjectName(QStringLiteral("SndTxtBtn"));
        SndTxtBtn->setGeometry(QRect(310, 335, 38, 38));
        SndTxtBtn->setStyleSheet(QLatin1String("QPushButton{background-color:transparent;border-width:0px;}\n"
"QPushButton:hover{border-width: 2px;border-style: solid;border-color: rgb(255, 255, 255);border-radius:5;}\n"
"QToolTip{border:0px;background:rgb(46,80,108,255);color:white}"));
        QIcon icon7;
        icon7.addFile(QStringLiteral("../Image/png/send.png"), QSize(), QIcon::Normal, QIcon::Off);
        SndTxtBtn->setIcon(icon7);
        SndTxtBtn->setIconSize(QSize(32, 32));
        ClearTxtBtn = new QPushButton(groupBox_CM);
        ClearTxtBtn->setObjectName(QStringLiteral("ClearTxtBtn"));
        ClearTxtBtn->setGeometry(QRect(360, 335, 38, 38));
        ClearTxtBtn->setStyleSheet(QLatin1String("QPushButton{background-color:transparent;border-width:0px;}\n"
"QPushButton:hover{border-width: 2px;border-style: solid;border-color: rgb(255, 255, 255);border-radius:5;}\n"
"QToolTip{border:0px;background:rgb(46,80,108,255);color:white}"));
        QIcon icon8;
        icon8.addFile(QStringLiteral("../Image/png/clear.png"), QSize(), QIcon::Normal, QIcon::Off);
        ClearTxtBtn->setIcon(icon8);
        ClearTxtBtn->setIconSize(QSize(32, 32));
        SndCountLabel = new QLabel(groupBox_CM);
        SndCountLabel->setObjectName(QStringLiteral("SndCountLabel"));
        SndCountLabel->setGeometry(QRect(310, 380, 91, 16));
        ShowTxtSwitchBtn = new QCheckBox(groupBox_CM);
        ShowTxtSwitchBtn->setObjectName(QStringLiteral("ShowTxtSwitchBtn"));
        ShowTxtSwitchBtn->setGeometry(QRect(310, 280, 91, 20));
        ShowTxtSwitchBtn->setStyleSheet(QLatin1String("QCheckBox{background-color:transparent;border-width:0px;}\n"
"QCheckBox:hover{border-width: 2px;border-style: solid;border-color: rgb(255, 255, 255);border-radius:5;}"));
        RecvTxtBrower = new QTextBrowser(groupBox_CM);
        RecvTxtBrower->setObjectName(QStringLiteral("RecvTxtBrower"));
        RecvTxtBrower->setGeometry(QRect(5, 21, 401, 251));
        RecvTxtBrower->setStyleSheet(QStringLiteral("border-width: 2px;border-style: solid;border-color: rgb(255, 255, 255);"));
        Server_VSClass->setCentralWidget(centralWidget);

        retranslateUi(Server_VSClass);

        QMetaObject::connectSlotsByName(Server_VSClass);
    } // setupUi

    void retranslateUi(QMainWindow *Server_VSClass)
    {
        Server_VSClass->setWindowTitle(QApplication::translate("Server_VSClass", "\346\260\224\350\261\241\350\247\202\346\265\213\350\246\201\347\264\240\344\270\255\345\277\203\347\253\231", nullptr));
        actionDMTM->setText(QApplication::translate("Server_VSClass", "\350\241\245\346\212\204\346\225\260\346\215\256", nullptr));
#ifndef QT_NO_TOOLTIP
        actionDMTM->setToolTip(QApplication::translate("Server_VSClass", "\350\241\245\346\212\204\346\225\260\346\215\256", nullptr));
#endif // QT_NO_TOOLTIP
        action1->setText(QApplication::translate("Server_VSClass", "1", nullptr));
        action_SYSLog->setText(QApplication::translate("Server_VSClass", "\347\263\273\347\273\237\346\227\245\345\277\227", nullptr));
        action_DataLog->setText(QApplication::translate("Server_VSClass", "\346\225\260\346\215\256\346\227\245\345\277\227", nullptr));
        groupBox_Main->setTitle(QString());
        groupBox_M->setTitle(QString());
#ifndef QT_NO_TOOLTIP
        RemoveBtn->setToolTip(QApplication::translate("Server_VSClass", "\345\210\240\351\231\244\350\247\243\346\236\220\345\272\223", nullptr));
#endif // QT_NO_TOOLTIP
        RemoveBtn->setText(QString());
#ifndef QT_NO_TOOLTIP
        SettingBtn->setToolTip(QApplication::translate("Server_VSClass", "\345\217\202\346\225\260\350\256\276\347\275\256", nullptr));
#endif // QT_NO_TOOLTIP
        SettingBtn->setText(QString());
#ifndef QT_NO_TOOLTIP
        LogBtn->setToolTip(QApplication::translate("Server_VSClass", "\346\237\245\347\234\213\346\227\245\345\277\227", nullptr));
#endif // QT_NO_TOOLTIP
        LogBtn->setText(QString());
#ifndef QT_NO_TOOLTIP
        AddBtn->setToolTip(QApplication::translate("Server_VSClass", "\346\267\273\345\212\240\350\247\243\346\236\220\345\272\223", nullptr));
#endif // QT_NO_TOOLTIP
        AddBtn->setText(QString());
        NameLabel->setText(QApplication::translate("Server_VSClass", "\346\260\224\350\261\241\350\247\202\346\265\213\350\246\201\347\264\240\344\270\255\345\277\203\347\253\231", nullptr));
        ImageLabel->setText(QString());
        groupBox_C->setTitle(QString());
#ifndef QT_NO_TOOLTIP
        MinBtn->setToolTip(QApplication::translate("Server_VSClass", "\346\234\200\345\260\217\345\214\226", nullptr));
#endif // QT_NO_TOOLTIP
        MinBtn->setText(QString());
#ifndef QT_NO_TOOLTIP
        CloseBtn->setToolTip(QApplication::translate("Server_VSClass", "\345\205\263\351\227\255", nullptr));
#endif // QT_NO_TOOLTIP
        CloseBtn->setText(QString());
        groupBox_F->setTitle(QApplication::translate("Server_VSClass", "\350\256\276\345\244\207\345\210\227\350\241\250", nullptr));
        groupBox_S->setTitle(QApplication::translate("Server_VSClass", "\344\270\232\345\212\241\345\210\227\350\241\250", nullptr));
        OnLineCountLabel->setText(QApplication::translate("Server_VSClass", "\350\256\276\345\244\207\345\234\250\347\272\277\344\270\252\346\225\260\357\274\2320", nullptr));
        StatusLabel->setText(QApplication::translate("Server_VSClass", "\347\263\273\347\273\237\350\277\220\350\241\214\346\255\243\345\270\270", nullptr));
        groupBox_CM->setTitle(QApplication::translate("Server_VSClass", "\346\216\247\345\210\266\345\221\275\344\273\244", nullptr));
        HexSwitchBtn->setText(QApplication::translate("Server_VSClass", "hex", nullptr));
#ifndef QT_NO_TOOLTIP
        SndTxtBtn->setToolTip(QApplication::translate("Server_VSClass", "\345\217\221\351\200\201", nullptr));
#endif // QT_NO_TOOLTIP
        SndTxtBtn->setText(QString());
#ifndef QT_NO_TOOLTIP
        ClearTxtBtn->setToolTip(QApplication::translate("Server_VSClass", "\346\270\205\351\231\244", nullptr));
#endif // QT_NO_TOOLTIP
        ClearTxtBtn->setText(QString());
        SndCountLabel->setText(QApplication::translate("Server_VSClass", "\345\217\221\351\200\201\344\270\252\346\225\260\357\274\2320", nullptr));
        ShowTxtSwitchBtn->setText(QApplication::translate("Server_VSClass", "\346\230\276\347\244\272\346\216\245\346\224\266\346\225\260\346\215\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Server_VSClass: public Ui_Server_VSClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWND_H
