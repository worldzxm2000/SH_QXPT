#include "MQConfigDlg.h"
#include "Global_Var.h"
MQConfigDlg::MQConfigDlg( MQProducer* g_MQProducer_Data, MQProducer* g_MQProducer_MDB, MQProducer* g_MQProducer_WebSrv, WebCommServer* g_WebCommServer, QWidget *parent)
{
	ui.setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);
	g_MQProducer_Data = g_MQProducer_Data;
    g_MQProducer_MDB = g_MQProducer_MDB;
	g_MQProducer_WebSrv = g_MQProducer_WebSrv;
	g_WebCommServer = g_WebCommServer;
	 ui.lineEdit_admin->setText(QString::fromStdString(g_MQProducer_Data->UserName));
	 ui.lineEdit_password->setText(QString::fromStdString(g_MQProducer_Data->Password));
	 ui.lineEdit_URL->setText(QString::fromStdString(g_MQProducer_Data->brokerURI));
}

MQConfigDlg::~MQConfigDlg()
{
}


void MQConfigDlg::on_OkBtn_clicked()
{
	g_MQProducer_Data->UserName = ui.lineEdit_admin->text().trimmed().toLocal8Bit().constData();
	g_MQProducer_MDB->UserName = ui.lineEdit_admin->text().trimmed().toLocal8Bit().constData();
	g_MQProducer_WebSrv->UserName= ui.lineEdit_admin->text().trimmed().toLocal8Bit().constData();
	g_WebCommServer->UserName= ui.lineEdit_admin->text().trimmed().toLocal8Bit().constData();

	g_MQProducer_Data->Password = ui.lineEdit_password->text().trimmed().toLocal8Bit().constData();
	g_MQProducer_MDB->Password = ui.lineEdit_password->text().trimmed().toLocal8Bit().constData();
	g_MQProducer_WebSrv->Password = ui.lineEdit_password->text().trimmed().toLocal8Bit().constData();
	g_WebCommServer->Password = ui.lineEdit_password->text().trimmed().toLocal8Bit().constData();

	g_MQProducer_Data->brokerURI = ui.lineEdit_URL->text().trimmed().toLocal8Bit().constData();
	g_MQProducer_MDB->brokerURI = ui.lineEdit_URL->text().trimmed().toLocal8Bit().constData();
	g_MQProducer_WebSrv->Password = ui.lineEdit_URL->text().trimmed().toLocal8Bit().constData();
	g_WebCommServer->Password = ui.lineEdit_URL->text().trimmed().toLocal8Bit().constData();

	g_MQProducer_Data->start();
	g_MQProducer_MDB->start();
	g_MQProducer_WebSrv->start();
	g_WebCommServer->start();

}