#pragma once

#include <QWidget>
#include "ui_MQConfig.h"
#include<QMouseEvent>
#include"Global.h"
#include"Global_Var.h"
class MQConfigDlg : public QWidget
{
	Q_OBJECT

public:
	MQConfigDlg( MQProducer* g_MQProducer_Data, MQProducer* g_MQProducer_MDB, MQProducer* g_MQProducer_WebSrv, WebCommServer* g_WebCommServer, QWidget *parent = Q_NULLPTR);
	~MQConfigDlg();
	MQProducer *g_MQProducer_Data ;
	MQProducer *g_MQProducer_MDB ;
	MQProducer *g_MQProducer_WebSrv ;
	WebCommServer *g_WebCommServer ;
private:
	Ui::MQConfig ui;
private slots:
    void on_OkBtn_clicked();
};
