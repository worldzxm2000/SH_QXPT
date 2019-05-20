/********************************************************************************
** Form generated from reading UI file 'QCToolTip.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QCTOOLTIP_H
#define UI_QCTOOLTIP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QCToolTip
{
public:
    QGroupBox *groupBox;
    QLabel *label;
    QLabel *ServerNameLabel;
    QLabel *StationLabel;
    QLabel *label_4;
    QLabel *DeviceLabel;
    QLabel *label_6;
    QLabel *OnlineLabel;
    QLabel *label_8;
    QLabel *IPLabel;
    QLabel *label_9;
    QLabel *PortLabel;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *LoginTimeLabel;
    QLabel *LastDataTimeLabel;

    void setupUi(QWidget *QCToolTip)
    {
        if (QCToolTip->objectName().isEmpty())
            QCToolTip->setObjectName(QStringLiteral("QCToolTip"));
        QCToolTip->resize(150, 310);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        QCToolTip->setFont(font);
        QIcon icon;
        icon.addFile(QStringLiteral("../Win32/Image/png/weather.png"), QSize(), QIcon::Normal, QIcon::Off);
        QCToolTip->setWindowIcon(icon);
        groupBox = new QGroupBox(QCToolTip);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(0, 0, 150, 310));
        groupBox->setStyleSheet(QLatin1String("color:white;background:rgba(46,80,108,255);\n"
""));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 10, 60, 20));
        label->setFont(font);
        ServerNameLabel = new QLabel(groupBox);
        ServerNameLabel->setObjectName(QStringLiteral("ServerNameLabel"));
        ServerNameLabel->setGeometry(QRect(80, 10, 60, 20));
        ServerNameLabel->setFont(font);
        StationLabel = new QLabel(groupBox);
        StationLabel->setObjectName(QStringLiteral("StationLabel"));
        StationLabel->setGeometry(QRect(80, 40, 60, 20));
        StationLabel->setFont(font);
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 40, 60, 20));
        label_4->setFont(font);
        DeviceLabel = new QLabel(groupBox);
        DeviceLabel->setObjectName(QStringLiteral("DeviceLabel"));
        DeviceLabel->setGeometry(QRect(80, 70, 60, 20));
        DeviceLabel->setFont(font);
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(10, 70, 60, 20));
        label_6->setFont(font);
        OnlineLabel = new QLabel(groupBox);
        OnlineLabel->setObjectName(QStringLiteral("OnlineLabel"));
        OnlineLabel->setGeometry(QRect(80, 100, 60, 20));
        OnlineLabel->setFont(font);
        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(10, 100, 60, 20));
        label_8->setFont(font);
        IPLabel = new QLabel(groupBox);
        IPLabel->setObjectName(QStringLiteral("IPLabel"));
        IPLabel->setGeometry(QRect(60, 130, 80, 20));
        IPLabel->setFont(font);
        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(10, 130, 40, 20));
        label_9->setFont(font);
        label_9->setAlignment(Qt::AlignCenter);
        PortLabel = new QLabel(groupBox);
        PortLabel->setObjectName(QStringLiteral("PortLabel"));
        PortLabel->setGeometry(QRect(80, 160, 60, 20));
        PortLabel->setFont(font);
        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(10, 160, 60, 20));
        label_10->setFont(font);
        label_10->setAlignment(Qt::AlignCenter);
        label_11 = new QLabel(groupBox);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(10, 190, 60, 20));
        label_11->setFont(font);
        label_11->setAlignment(Qt::AlignCenter);
        label_12 = new QLabel(groupBox);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(10, 250, 60, 20));
        label_12->setFont(font);
        label_12->setAlignment(Qt::AlignCenter);
        LoginTimeLabel = new QLabel(groupBox);
        LoginTimeLabel->setObjectName(QStringLiteral("LoginTimeLabel"));
        LoginTimeLabel->setGeometry(QRect(10, 220, 131, 20));
        LoginTimeLabel->setFont(font);
        LastDataTimeLabel = new QLabel(groupBox);
        LastDataTimeLabel->setObjectName(QStringLiteral("LastDataTimeLabel"));
        LastDataTimeLabel->setGeometry(QRect(10, 280, 121, 20));
        LastDataTimeLabel->setFont(font);

        retranslateUi(QCToolTip);

        QMetaObject::connectSlotsByName(QCToolTip);
    } // setupUi

    void retranslateUi(QWidget *QCToolTip)
    {
        QCToolTip->setWindowTitle(QApplication::translate("QCToolTip", "\350\256\276\345\244\207\344\277\241\346\201\257", nullptr));
        groupBox->setTitle(QString());
        label->setText(QApplication::translate("QCToolTip", "\344\270\232\345\212\241\345\220\215\347\247\260\357\274\232", nullptr));
        ServerNameLabel->setText(QApplication::translate("QCToolTip", "\344\270\232\345\212\241\345\220\215\347\247\260", nullptr));
        StationLabel->setText(QApplication::translate("QCToolTip", "\345\217\260\347\253\231\345\220\215\347\247\260", nullptr));
        label_4->setText(QApplication::translate("QCToolTip", "\345\217\260\347\253\231\345\220\215\347\247\260\357\274\232", nullptr));
        DeviceLabel->setText(QApplication::translate("QCToolTip", "\350\256\276\345\244\207\345\220\215\347\247\260", nullptr));
        label_6->setText(QApplication::translate("QCToolTip", "\350\256\276\345\244\207\345\220\215\347\247\260\357\274\232", nullptr));
        OnlineLabel->setText(QApplication::translate("QCToolTip", "\345\234\250\347\272\277\347\212\266\346\200\201", nullptr));
        label_8->setText(QApplication::translate("QCToolTip", "\345\234\250\347\272\277\347\212\266\346\200\201\357\274\232", nullptr));
        IPLabel->setText(QApplication::translate("QCToolTip", "IP", nullptr));
        label_9->setText(QApplication::translate("QCToolTip", "IP\357\274\232", nullptr));
        PortLabel->setText(QApplication::translate("QCToolTip", "\347\253\257\345\217\243", nullptr));
        label_10->setText(QApplication::translate("QCToolTip", "\347\253\257\345\217\243\357\274\232", nullptr));
        label_11->setText(QApplication::translate("QCToolTip", "\347\231\273\345\275\225\346\227\266\351\227\264:", nullptr));
        label_12->setText(QApplication::translate("QCToolTip", "\346\225\260\346\215\256\346\227\266\351\227\264:", nullptr));
        LoginTimeLabel->setText(QApplication::translate("QCToolTip", "2019-04-10 10:00:00", nullptr));
        LastDataTimeLabel->setText(QApplication::translate("QCToolTip", "2019-04-10 10:00:00", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QCToolTip: public Ui_QCToolTip {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QCTOOLTIP_H
