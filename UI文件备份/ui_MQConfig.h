/********************************************************************************
** Form generated from reading UI file 'MQConfig.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MQCONFIG_H
#define UI_MQCONFIG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MQConfig
{
public:
    QGroupBox *groupBox;
    QGroupBox *groupBox_IP;
    QLineEdit *lineEdit_URL;
    QGroupBox *groupBox_QZ;
    QLineEdit *lineEdit_admin;
    QGroupBox *groupBox_FTPSEVER;
    QLineEdit *lineEdit_password;
    QPushButton *OKBtn;

    void setupUi(QWidget *MQConfig)
    {
        if (MQConfig->objectName().isEmpty())
            MQConfig->setObjectName(QStringLiteral("MQConfig"));
        MQConfig->setWindowModality(Qt::WindowModal);
        MQConfig->resize(337, 193);
        MQConfig->setMaximumSize(QSize(337, 193));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(9);
        MQConfig->setFont(font);
        QIcon icon;
        icon.addFile(QStringLiteral("../Image/png/mq.png"), QSize(), QIcon::Normal, QIcon::Off);
        MQConfig->setWindowIcon(icon);
        MQConfig->setStyleSheet(QStringLiteral("background:rgb(77,77,77);color:white"));
        groupBox = new QGroupBox(MQConfig);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 321, 181));
        groupBox_IP = new QGroupBox(groupBox);
        groupBox_IP->setObjectName(QStringLiteral("groupBox_IP"));
        groupBox_IP->setGeometry(QRect(10, 10, 301, 61));
        lineEdit_URL = new QLineEdit(groupBox_IP);
        lineEdit_URL->setObjectName(QStringLiteral("lineEdit_URL"));
        lineEdit_URL->setGeometry(QRect(10, 20, 281, 20));
        groupBox_QZ = new QGroupBox(groupBox);
        groupBox_QZ->setObjectName(QStringLiteral("groupBox_QZ"));
        groupBox_QZ->setGeometry(QRect(10, 80, 121, 51));
        lineEdit_admin = new QLineEdit(groupBox_QZ);
        lineEdit_admin->setObjectName(QStringLiteral("lineEdit_admin"));
        lineEdit_admin->setGeometry(QRect(10, 20, 101, 20));
        groupBox_FTPSEVER = new QGroupBox(groupBox);
        groupBox_FTPSEVER->setObjectName(QStringLiteral("groupBox_FTPSEVER"));
        groupBox_FTPSEVER->setGeometry(QRect(140, 80, 171, 51));
        lineEdit_password = new QLineEdit(groupBox_FTPSEVER);
        lineEdit_password->setObjectName(QStringLiteral("lineEdit_password"));
        lineEdit_password->setGeometry(QRect(10, 20, 151, 20));
        OKBtn = new QPushButton(groupBox);
        OKBtn->setObjectName(QStringLiteral("OKBtn"));
        OKBtn->setGeometry(QRect(10, 140, 75, 23));
        QWidget::setTabOrder(lineEdit_URL, lineEdit_admin);
        QWidget::setTabOrder(lineEdit_admin, lineEdit_password);
        QWidget::setTabOrder(lineEdit_password, OKBtn);

        retranslateUi(MQConfig);

        QMetaObject::connectSlotsByName(MQConfig);
    } // setupUi

    void retranslateUi(QWidget *MQConfig)
    {
        MQConfig->setWindowTitle(QApplication::translate("MQConfig", "\346\266\210\346\201\257\344\270\255\351\227\264\344\273\266\350\256\276\347\275\256", nullptr));
        groupBox->setTitle(QString());
        groupBox_IP->setTitle(QApplication::translate("MQConfig", "ULR", nullptr));
        lineEdit_URL->setText(QString());
        groupBox_QZ->setTitle(QApplication::translate("MQConfig", "\350\264\246\346\210\267\345\220\215", nullptr));
        groupBox_FTPSEVER->setTitle(QApplication::translate("MQConfig", "\345\257\206\347\240\201", nullptr));
        OKBtn->setText(QApplication::translate("MQConfig", "\350\256\276\347\275\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MQConfig: public Ui_MQConfig {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MQCONFIG_H
