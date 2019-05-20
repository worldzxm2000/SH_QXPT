#include "MainWnd.h"
#include<QJsonDocument>
#include<QFileDialog>
#include"ConfigWnd.h"
#include<QtNetwork>
#include<QSettings>
#include <iphlpapi.h>
#include"SYSLogDlg.h"
#include<QDockWidget>
#include<QApplication>
#include<QDesktopWidget>
#include<QtXml>
#include<QModelIndex>
#include<QDesktopServices>
#include"MQConfigDlg.h"
#include"Global_Var.h"
//构造函数
MainWnd::MainWnd(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint);
	move((QApplication::desktop()->width() - this->width()) / 2, (QApplication::desktop()->height() - this->height()) / 2);
	SetStatusLabel("系统运行正常");
	//消息中间件
	g_MQProducer_Data= new MQProducer(this);
	g_MQProducer_MDB= new MQProducer(this);
	g_MQProducer_WebSrv= new MQProducer(this);
	g_WebCommServer= new WebCommServer(this);
	//menu功能
	connect(ui.action_SYSLog, SIGNAL(triggered()), this, SLOT(OpenSYSLog()));
	connect(ui.action_DataLog, SIGNAL(triggered()), this, SLOT(OpenDataLog()));

	//业务类型列表
	connect(ui.ServerList, SIGNAL(NoticfyServerRun(int)), this, SLOT(Lib_Run(int)), Qt::DirectConnection);
	connect(ui.ServerList, SIGNAL(NoticfyServerStop(int)), this, SLOT(Lib_Stop(int)), Qt::DirectConnection);
	connect(ui.ServerList, SIGNAL(currentItemChanged(QTableWidgetItem *, QTableWidgetItem *)), this, SLOT(ServerList_currentItemChanged(QTableWidgetItem *, QTableWidgetItem *)));
	ui.ServerList->setContextMenuPolicy(Qt::CustomContextMenu);//右键创建Menu
	CreateServerListActions();

	
	connect(ui.MinBtn, SIGNAL(clicked()), this, SLOT(slot_minWindow()));
	connect(ui.CloseBtn, SIGNAL(clicked()), this, SLOT(close()));
	LogWrite::WriteLog("主程序已启动...");
	//ListCtrl控件当前选择行
	iSelectedRowOfServiceListCtrl = -1;

	//初始化消息中间件
	if (!InitMQ())
	{
		SetStatusLabel("无法连接消息中间件服务");
		LogWrite::WriteLog("无法连接消息中间件服务");
		QMessageBox::warning(this, "警告", "无法连接消息中间件服务");
		return;
	}
	//初始化动态库
	IniDLL();


}

//析构函数
MainWnd::~MainWnd()
{

}

void MainWnd::close()
{
	LogWrite::WriteLog("系统关闭");
	QWidget::close();
}
//窗体鼠标移动等响应
void MainWnd::slot_minWindow()
{
	this->showMinimized();
}

void MainWnd::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton) {
		m_Drag = true;
		m_DragPosition = event->globalPos() - this->pos();
		event->accept();
	}
}

void MainWnd::mouseMoveEvent(QMouseEvent *event)
{
	if (m_Drag && (event->buttons() && Qt::LeftButton)) {
		move(event->globalPos() - m_DragPosition);
		event->accept();
	}
}

void MainWnd::mouseReleaseEvent(QMouseEvent *event)
{
	m_Drag = false;
}

void MainWnd:: SetStatusLabel(QString Status)
{
	ui.StatusLabel->setText(Status);
}

//消息中间件配置窗体
bool MainWnd::InitMQ()
{
	try
	{
		activemq::library::ActiveMQCPP::initializeLibrary();
		//读取配置文件
		LoadMQConfigFile();
		//初始化消息中间件
		bool result = false;
		result = g_MQProducer_Data->start();
		result = result & g_MQProducer_MDB->start();
		result = result & g_MQProducer_WebSrv->start();
		result = result & g_WebCommServer->start();
		return result;
	}
	catch (const std::exception&)
	{
		return false;
	}

}

//加载解析库
void MainWnd::IniDLL()
{
	QFile file(QCoreApplication::applicationDirPath()+"//DLL//DLL.xml");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Truncate | QIODevice::Text))
		return;
	QTextStream out(&file);
	QString strTemp;
	strTemp = out.readAll();
	QDomDocument doc;
	doc.setContent(strTemp, false);
	QDomElement root = doc.documentElement();//根节点AgrMetObservationData
	QDomNode node = root.firstChild();//获得第一个子节点 name
	while (!node.isNull())
	{
		QDomElement e= node.toElement();
		//获取路径
		QString Path = e.attribute("Path");
		//获取名称
		QString Name = e.attribute("Name");
		int Port = e.attribute("Port").toInt();
		QString IP = e.attribute("IP");
		LRESULT pResult=AddDLL(Path,IP,Port);
		switch (pResult)
		{
		case -1:
			QMessageBox::information(this, tr("错误"), tr("动态链接库加载错误！"));
			return;
		case -2:
			QMessageBox::information(this, tr("错误"), tr("端口已被占用！"));
			return;
		}
		node = node.nextSibling();
	}
}

//读取MQ配置文件
void MainWnd::LoadMQConfigFile()
{
	QString UserName, Password, BrokerURI;
	//读取Command.ini路径
	QString path = QCoreApplication::applicationDirPath() + "//MQConfig.ini";
	//打开INI文件
	QSettings configIniRead(path, QSettings::IniFormat);
	UserName = configIniRead.value("MQActive/UserName").toString();
	Password = configIniRead.value("MQActive/Password").toString();
	BrokerURI = configIniRead.value("MQActive/BrokerURI").toString();
	
	g_MQProducer_Data->UserName = UserName.toStdString();
	g_MQProducer_Data->Password = Password.toStdString() ;
	g_MQProducer_Data->brokerURI = BrokerURI.toStdString();
	g_MQProducer_Data->destURI = "NXSQ";

	g_MQProducer_MDB->UserName = UserName.toStdString();
	g_MQProducer_MDB->Password = Password.toStdString();
	g_MQProducer_MDB->brokerURI = BrokerURI.toStdString();
	g_MQProducer_MDB->destURI = "NOSQLData";

	g_MQProducer_WebSrv->UserName = UserName.toStdString();
	g_MQProducer_WebSrv->Password = Password.toStdString();
	g_MQProducer_WebSrv->brokerURI = BrokerURI.toStdString();
	g_MQProducer_WebSrv->destURI = "Cmm_Response";

	g_WebCommServer->UserName = UserName.toStdString();
	g_WebCommServer->Password = Password.toStdString();
	g_WebCommServer->brokerURI = BrokerURI.toStdString();
	g_WebCommServer->destURI = "Cmm_Request";
}

//添加Lib服务
void MainWnd::on_AddBtn_clicked()
{
	//加载动态解析DLL
	LRESULT pResult = AddDLL();
	switch (pResult)
	{
	case -1:
		QMessageBox::information(this, tr("错误"), tr("动态链接库加载错误！"));
		break;
	case -2:
		QMessageBox::information(this, tr("错误"), tr("端口已被占用！"));
		break;
	default:
		break;
	}
}

//移除Lib
void MainWnd::on_RemoveBtn_clicked()
{
	if (iSelectedRowOfServiceListCtrl < 0 || iSelectedRowOfServiceListCtrl > ui.ServerList->rowCount() - 1)
		return;
	QString ServiceName = ui.ServerList->item(iSelectedRowOfServiceListCtrl, 1)->text();
	//从UI列表中移除
	ui.ServerList->removeRow(iSelectedRowOfServiceListCtrl);
	//移除EHT
	EHTPool.Stop(ServiceName);
	//移除设备列表
	for (int i = ui.ClientList->count() - 1; i > -1; i--)
	{
		if (ui.ClientList->item(i)->text() == ServiceName)
		{
			ui.ClientList->takeItem(i);
		}
	}
	
}

//打开系统运行日志
void MainWnd::on_LogBtn_clicked()
{
	SYSLogDlg SysLogdlg("SYSLog");
	SysLogdlg.exec();
}

//打开参数设置
void MainWnd::on_SettingBtn_clicked()
{
	MQConfigDlg *mq = new MQConfigDlg(g_MQProducer_Data, g_MQProducer_MDB, g_MQProducer_WebSrv, g_WebCommServer,this);
	mq->show();
}

//发送命令按钮事件
void MainWnd::on_SndTxtBtn_clicked()
{
	u_int Socket = ui.ClientList->GetSocket();
	QString Txt = ui.Send_textEdit->toPlainText();
	QString RecvTxt = ui.RecvTxtBrower->toPlainText();
	RecvTxt += ("发送：") + Txt + "\r\n";
	ui.RecvTxtBrower->setText(RecvTxt);
	//hex发送
	if (ui.HexSwitchBtn->isChecked())
	{
		QStringList list=Txt.split(" ");
		for (int  i = 0; i < list.count(); i++)
		{
			QString item = list[i];
			int count = item.count();
			if (count == 1)
				list[i] = '0' + list[i];
		}
		Txt = list.join(" ");
	}
	QByteArray ba = Txt.toLocal8Bit();
	LPCSTR ch = ba.data();
	//hex发送
	if (ui.HexSwitchBtn->isChecked())
		ba = QByteArray::fromHex(ba);
	//字符串发送
	::send(Socket, ba,ba.length(), 0);
}

//清空接收
void MainWnd::on_ClearTxtBtn_clicked()
{
	ui.RecvTxtBrower->clear();
}


//添加解析DLL
LRESULT MainWnd::AddDLL()
{
	QString LibPath;
	//打开选择文件的对话框
	QFileDialog fileDialog(this);
	fileDialog.setWindowTitle(tr("选择加载动态链接库"));
	fileDialog.setDirectory(".");
	fileDialog.setNameFilter(tr("DLL Files(*.dll)"));
	if (fileDialog.exec() != QDialog::Accepted)
		return 0;
	LibPath = fileDialog.selectedFiles()[0];
	//创建
	EHT *pEHT = new EHT(this);
	//新连接
	connect(pEHT, SIGNAL(NewConnectionSignal(QString, int, unsigned int, QString)), SLOT(NewConnectionSlot(QString, int, unsigned int, QString)));
	//数据或心跳通知
	connect(pEHT, SIGNAL(OnLineSignal(QVariant)), this, SLOT(RefreshListCtrl(QVariant)));
	//系统状态更新
	connect(pEHT, SIGNAL(RefreshStatus(QString)), this, SLOT(RefreshStatus(QString)));
	pEHT->g_MQProducer_Data = g_MQProducer_Data;
	pEHT->g_MQProducer_MDB = g_MQProducer_MDB;
	pEHT->g_MQProducer_WebSrv = g_MQProducer_WebSrv;
	pEHT->g_WebCommServer = g_WebCommServer;
	connect(pEHT->g_WebCommServer, SIGNAL(NewWebRequest(QString, int, int, QStringList)), pEHT, SLOT(RequestFor( QString, int, int, QStringList)), Qt::AutoConnection);
	pEHT->InitIOCP();
	LRESULT pResult = pEHT->LoadLib(LibPath, true);
	if (pResult < 1)
	{
		pEHT->Stop();
		pEHT->UnloadLib();
		return pResult;
	}
	if(EHTPool.Start(pEHT))
		ui.ServerList->AddRow(pEHT->GetServiceName());
	return 1;
}

//添加解析DLL
LRESULT MainWnd::AddDLL(QString Path,QString IP,int Port)
{
	//创建
	EHT *pEHT = new EHT(this);
	//新连接
	connect(pEHT, SIGNAL(NewConnectionSignal(QString)), SLOT(NewConnectionSlot(QString)));
	//数据或心跳通知
	connect(pEHT, SIGNAL(OnLineSignal(QVariant)), this, SLOT(RefreshListCtrl(QVariant)));
	//系统运行状态
	connect(pEHT, SIGNAL(RefreshStatus(QString)), this, SLOT(RefreshStatus(QString)));
	pEHT->g_MQProducer_Data = g_MQProducer_Data;
	pEHT->g_MQProducer_MDB = g_MQProducer_MDB;
	pEHT->g_MQProducer_WebSrv = g_MQProducer_WebSrv;
	pEHT->g_WebCommServer = g_WebCommServer;
	pEHT->InitIOCP();
	LRESULT pResult = pEHT->LoadLib(Path,IP,Port,true);
	if (pResult < 1)
		return pResult;
	ui.ServerList->AddRow(pEHT->GetServiceName());
	EHTPool.Start(pEHT);
	return 1;
}

//新连接设备
void MainWnd::NewConnectionSlot(QString Status)
{
	SetStatusLabel(Status);
	LogWrite::WriteLog(Status);
}

//获得错误信息
void MainWnd::GetErrorMSG(int error)
{
	QString strMSG;
	switch (error)
	{
	case 10301:
		strMSG = QString("WSA初始化失败！");
		break;
	case 10302:
		strMSG = QString("Sokcet bind失败！");
		break;
	case 10303:
		strMSG = QString("Socket listen失败！");
		break;
	case 10036:
		strMSG = QString("Web监听端口异常");
		break;
	case -1:
		strMSG = QString("Web发送命令错误!");
		break;
	case -4:
		strMSG = QString("服务器间通信异常！");
		break;
	case -5:
		strMSG = QString("发送Web服务器失败！");
		break;
	case 10311:
		strMSG = QString("端口号监听失败！");
		break;
	default:
		strMSG = QString::number(error);
		break;
	}
	LogWrite::WriteLog(strMSG);
}

//刷新设备ListCtrl控件
void MainWnd::RefreshListCtrl(QVariant Var)
{
	FACILITYINFO * client = Var.value<FACILITYINFO*>();
	ui.ClientList->AddRow(client);
}

//业务列表右键事件
void MainWnd::on_ServerList_customContextMenuRequested(const QPoint &pos)
{
	//获取鼠标位置
	QModelIndex index = ui.ServerList->indexAt(pos);
	iSelectedRowOfServiceListCtrl = index.row();
	if (iSelectedRowOfServiceListCtrl == -1)
		return;
	//菜单出现的位置为当前鼠标的位置
	pop_Menu_Service.exec(QCursor::pos());

}

//业务列表右键菜单
void MainWnd::CreateServerListActions()
{
	//创建一个action
	action_Attributes.setText("属性");
	action_TxtFile.setText("备份文件");
	connect(&action_Attributes, SIGNAL(triggered()), this, SLOT(Lib_Attri()));
	connect(&action_TxtFile, SIGNAL(triggered()), this, SLOT(OpenTxtFile()));
	pop_Menu_Service.addAction(&action_Attributes);
	pop_Menu_Service.addAction(&action_TxtFile);
	pop_Menu_Service.setStyleSheet("background:rgba(46,80,108,255);color:white");
}


//启动Lib服务
bool MainWnd::Lib_Run(int Row)
{
	if (Row<0)
		return false;
	QTableWidgetItem* SelectedItem = ui.ServerList->item(Row, 1); //获取选择行
	bool b = EHTPool.Run(ui.ServerList->item(Row, 1)->text());
	if (!b)
		QMessageBox::warning(this, "警告", "端口号被其他程序占用！");
	return b;
}

//停止Lib服务
bool MainWnd::Lib_Stop(int Row)
{
	if (Row<0)
		return false;
	QTableWidgetItem* SelectedItem = ui.ServerList->item(Row, 0); //获取选择行	
	QString ServerName = ui.ServerList->item(Row, 1)->text();
	SetStatusLabel(ServerName + "已停止");
	ui.ClientList->clearSelection();
	return EHTPool.Pause(ServerName);
}

//查看业务属性
void MainWnd::Lib_Attri()
{
	if (iSelectedRowOfServiceListCtrl < 0)
		return;
	QString ServiceName = ui.ServerList->item(iSelectedRowOfServiceListCtrl, 1)->text();
	ConfigWnd CfgWnd(this);
	//不能修改
	CfgWnd.DialogMode = false;
	//描述
	CfgWnd.m_Attribute = EHTPool.GetEHT(ServiceName)->GetAttribute();
	////端口号
	CfgWnd.m_Port = EHTPool.GetEHT(ServiceName)->GetPort();
	CfgWnd.exec();
}

void MainWnd::OpenTxtFile()
{
	if (iSelectedRowOfServiceListCtrl < 0)
		return;
	QString ServiceName = ui.ServerList->item(iSelectedRowOfServiceListCtrl, 1)->text();
	QString filePath = QCoreApplication::applicationDirPath() + "/" + ServiceName;
	if (!QDesktopServices::openUrl(QUrl::fromLocalFile(filePath)))
		QMessageBox::information(this, tr("错误"), tr("备份文件路径不正确！"));
}
//业务列表点击
void MainWnd::on_ServerList_cellClicked(int row, int column)
{
	iSelectedRowOfServiceListCtrl = row;
	if (iSelectedRowOfServiceListCtrl < 0 || iSelectedRowOfServiceListCtrl > ui.ServerList->rowCount() - 1)
		return;
	GetServiceInfo(row);

}
//业务列表改变
void MainWnd::on_ServerList_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
	iSelectedRowOfServiceListCtrl = currentRow;
	if (iSelectedRowOfServiceListCtrl < 0 || iSelectedRowOfServiceListCtrl > ui.ServerList->rowCount() - 1)
		return;
	GetServiceInfo(currentRow);
}

//获取在线设备个数
void MainWnd:: GetServiceInfo(int SelectedRowOfServiceListCtrl)
{
	//获取当前业务信息
	QString ServiceName = ui.ServerList->item(SelectedRowOfServiceListCtrl, 1)->text();
	int Count = EHTPool.GetEHT(ServiceName)->OnLineCount();
	
	ui.OnLineCountLabel->setText("在线设备个数: " + QString::number(Count));
	//刷新设备列表
	ui.ClientList->SortbySelected(ServiceName);
}

void MainWnd::RefreshStatus(QString Status)
{
	SetStatusLabel(Status);
}

void MainWnd::ShowTxtToUI(QString Txt, QVariant Var)
{
	//显示Txt Switch按钮关闭，返回
	if (false == ui.ShowTxtSwitchBtn->isChecked())
		return;
	//显示当前选择设备的Txt
	LPPER_HANDLE_DATA PerHandleData = Var.value<LPPER_HANDLE_DATA>();
	if (u_int Socket = ui.ClientList->GetSocket() != PerHandleData->Socket)
		return;
	//hex Switch按钮显示选择
	if (ui.HexSwitchBtn->isChecked())
	{
		QString ConvStr;
		for (int i = 0; i < Txt.length(); i++)
		{
			int inter = Txt[i].unicode();
			ConvStr += QString("%1").arg(inter & 0xFF, 2, 16, QLatin1Char('0')) + " ";
		}
		Txt = ConvStr;
	}
	ui.RecvTxtBrower->append("接收:" + Txt+"\r\n");
}

void MainWnd::on_list_itemClicked(QListWidgetItem* Item)
{
	ui.groupBox_CM->setEnabled(true);

}
/*未完成
void MainWnd::on_ShowTxtSwitchBtn_clicked(bool checked)
{
	u_int Socket = ui.ClientList->GetSocket();
	EHTPool.OffShowTxt(Socket,checked);
}
*/

