#include "EHT.h"
#include "ConfigWnd.h"
#include"LogWrite.h"
#include<QSettings>
#include<QDir>
#include<QtXml>
#include<Windows.h>
#include<stdio.h>
#include"MainWnd.h"
#define TIMEOUT 10
QMutex m_timerMutex;
EHT::EHT(QWidget *parent)
	: QWidget(parent)
{

	m_TimeOutTimerID = startTimer(1000);
	IsExistImage = false;
	IsExistTXT = false;
	//读取SIM卡号配置文件，转成区站号
	Convert2StationID();
	//当前运行状态
	m_IsRun = false;
	SetTimeTimer = new QTimer(parent);
	connect(SetTimeTimer, SIGNAL(timeout()), this, SLOT(SetTime()));
	SetTimeTimer->start(1000 * 60 * 60*24 );
	OffLineTimer = new QTimer(parent);
	connect(OffLineTimer, SIGNAL(timeout()), this, SLOT(Disconnect()));
	OffLineTimer->start(1000 * 60 * 10);
	//Image图片重新处理时间
	ReHandleZB_IMAGE = new QTimer(parent);
	ReHandleZB_IMAGE->connect(ReHandleZB_IMAGE, SIGNAL(timeout()), this, SLOT(MoveImageToDesAddr()));
	//XML文件处理时间
	ReHandleZB_XML = new QTimer(parent);
	ReHandleZB_XML->connect(ReHandleZB_XML, SIGNAL(timeout()), this, SLOT(MoveXMLToDesAddr()));
	ReHandleZB_XML->start(1000 * 60 * 10);
	//TXT文件重新处理时间
	ReHandleZB_TXT = new QTimer(parent);
	ReHandleZB_TXT->connect(ReHandleZB_TXT, SIGNAL(timeout()), this, SLOT(MoveTXTToDesAddr()));
}
EHT::~EHT()
{
	killTimer(m_TimeOutTimerID);
}
LRESULT EHT::LoadLib(QString Lib_Path,QString IP,int Port, bool isLoad)
{
	m_LibPath = Lib_Path;
	m_Lib.setFileName(Lib_Path);
	//读取成功
	if (m_Lib.load())
	{
		GetServiceTypeID_Lib func_GetServiceTypeID = (GetServiceTypeID_Lib)m_Lib.resolve("GetServiceTypeID");//获取业务ID
		GetServiceTypeName_Lib func_GetServiceTypeName = (GetServiceTypeName_Lib)m_Lib.resolve("GetServiceTypeName");//获取业务名称
		GetPort_Lib func_GetPort = (GetPort_Lib)m_Lib.resolve("GetPort");//获取端口号
		Char2Json func_Char2Json = (Char2Json)(m_Lib.resolve("Char2Json"));//获取解析数据
		func_SetTime_Lib = (SetTime_Lib)(m_Lib.resolve("SetTime"));//获取对时
		func_SetValueToControlWidget = (SetValueToControlWidget_Lib)(m_Lib.resolve("SetValueToControlWidget"));//获取返回值
		func_SetCommand = (SetCommand_Lib)(m_Lib.resolve("SetCommand"));//获取设置命令
		GetFacilityInfo func_GetFacilityInfo = (GetFacilityInfo)(m_Lib.resolve("GetFacilityInfo"));//获取设备信息
		if (!(func_GetServiceTypeID && func_GetServiceTypeName  && 
			func_GetPort&&func_Char2Json&&func_SetTime_Lib&&func_SetCommand&&func_SetValueToControlWidget&&func_GetFacilityInfo))
		{
			UnloadLib();
			return -1;
		}
		if (!isLoad)
			return true;
		//获取业务类型
		m_ServiceID = func_GetServiceTypeID();
		//获取端口号
		m_Port = func_GetPort();
		//获取业务名称
		m_ServiceName = func_GetServiceTypeName();

		//获取IP
		m_IP = IP;
		//判断端口合法性
		if (!IsLegallyPort(Port))
		{
			UnloadLib();
			return -2;
		}
		//获取IP
		m_Port = Port;
		//获取描述
		m_Attribute = "";
		return true;
	}
	else
	{
		UnloadLib();
		return false;
	}
}
LRESULT EHT::LoadLib(QString Lib_Path, bool isLoad)
{
	m_LibPath = Lib_Path;
	m_Lib.setFileName(Lib_Path);
	//读取成功
	if (m_Lib.load())
	{
		GetServiceTypeID_Lib func_GetServiceTypeID = (GetServiceTypeID_Lib)m_Lib.resolve("GetServiceTypeID");//获取业务ID
		GetServiceTypeName_Lib func_GetServiceTypeName = (GetServiceTypeName_Lib)m_Lib.resolve("GetServiceTypeName");//获取业务名称
		GetPort_Lib func_GetPort = (GetPort_Lib)m_Lib.resolve("GetPort");//获取端口号
		Char2Json func_Char2Json = (Char2Json)(m_Lib.resolve("Char2Json"));//获取解析数据
		func_SetTime_Lib = (SetTime_Lib)(m_Lib.resolve("SetTime"));//获取对时
	
		func_SetValueToControlWidget = (SetValueToControlWidget_Lib)(m_Lib.resolve("SetValueToControlWidget"));//获取返回值
		func_SetCommand = (SetCommand_Lib)(m_Lib.resolve("SetCommand"));//获取设置命令
		GetFacilityInfo func_GetFacilityInfo = (GetFacilityInfo)(m_Lib.resolve("GetFacilityInfo"));//获取设备信息
		if (!(func_GetServiceTypeID && func_GetServiceTypeName  &&
			func_GetPort&&func_Char2Json&&func_SetTime_Lib&&func_SetCommand&&func_SetValueToControlWidget&&func_GetFacilityInfo))
		{
			UnloadLib();
			return -1;
		}
		if (!isLoad)
			return true;
		//获取业务类型
		m_ServiceID = func_GetServiceTypeID();
		//获取端口号
		m_Port = func_GetPort();
		//获取业务名称
		m_ServiceName = func_GetServiceTypeName();
		//开启IP和端口设置窗体
		ConfigWnd CfgWnd;
		CfgWnd.DialogMode = true;//设置 false为读取
		CfgWnd.SetServicePort(m_Port);
		int r = CfgWnd.exec();
		if (r != QDialog::Accepted)
		{
			UnloadLib();
			return 0;
		}
		//获取IP
		m_IP = CfgWnd.m_IP;
		//判断端口合法性
		if (!IsLegallyPort(CfgWnd.m_Port))
		{
			UnloadLib();
			return -2;
		}
		//获取IP
		m_Port = CfgWnd.m_Port;
		//获取描述
		m_Attribute = CfgWnd.m_Attribute;
		return 1;
	}
	else
	{
		UnloadLib();
		return 0;
	}
}
bool EHT::UnloadLib()
{
	return	m_Lib.unload();
}
int EHT::GetServiceID()
{
	return m_ServiceID;
}
QString EHT::GetServiceName()
{
	return m_ServiceName;
}
int EHT::GetPort()
{
	return m_Port;
}
u_int EHT::FindSocket(QString UID,bool &IsExist)
{
	for (int i = 0; i < Clients.size(); i++)
	{
		if (Clients[i]->FUID == UID)
		{
			IsExist = true;
			//离线
			if (Clients[i]->Online == false)
				return 0;
			//在线
			return Clients[i]->Socket;
		}
	}
	return 0;
}
QString EHT::GetAttribute()
{
	return m_Attribute;
}
Char2Json EHT::GetDataFunc()
{
	return m_DataFunc;
}
bool EHT::Run(QThreadPool &ThreadPool)
{
	if (pIOCP == NULL)
	{
		//端口被占用
		if (!IsLegallyPort(m_Port))
		{
			UnloadLib();
			return false;
		}
		InitIOCP();
		LoadLib(m_LibPath, false);
	}
	pIOCP->func_Char2Json = (Char2Json)m_Lib.resolve("Char2Json");
	pIOCP->func_GetFacilityInfo= (GetFacilityInfo)m_Lib.resolve("GetFacilityInfo");
	m_DataFunc= (Char2Json)m_Lib.resolve("Char2Json");
	pIOCP->SetListenedPort(m_Port, m_IP);
	ThreadPool.start(pIOCP);
	m_IsRun = true;
	return true;
}
bool EHT::Stop()
{
	if (pIOCP != nullptr)
		//关闭IOCP
		pIOCP->Stop();
	
	UnloadLib();
	m_IsRun = false;
	pIOCP = nullptr;
	func_SetTime_Lib = nullptr;
	func_SetValueToControlWidget = nullptr;
	func_SetCommand = nullptr;
	return true;
}
void EHT::InitIOCP()
{
	//IOCP子线程
	pIOCP = new IOCP();
	//设备连接通知
	//connect(pIOCP,SIGNAL(NewConnectionSignal(QString,int,int,uint)),this,SLOT(NewConnectionSlot(QString,int,int,uint)),Qt::QueuedConnection);
	connect(pIOCP,&IOCP::NewConnectionSignal,this,&EHT::NewConnectionSlot, Qt::QueuedConnection);
	//设备离线通知
	//connect(pIOCP, SIGNAL(OffLineSignal(unsigned int)), this, SLOT(OffLineSlot(unsigned int)), Qt::QueuedConnection);
	connect(pIOCP,&IOCP::OffLineSignal,this,&EHT::OffLineSlot,Qt::QueuedConnection);
	//设备数据错误通知
	connect(pIOCP, SIGNAL(ErrorMSGSignal(int)), this, SLOT(GetErrorSlot(int)), Qt::QueuedConnection);
	//设备新数据通知
	connect(pIOCP, SIGNAL(NewDataSignal(QVariant)), this, SLOT(NewDataSlot(QVariant)), Qt::QueuedConnection);
	connect(pIOCP, SIGNAL(NewDataSignal(QVariant,int)), this, SLOT(NewDataSlot(QVariant, int)), Qt::QueuedConnection);
	//设备操作状态通知
     connect(pIOCP, &IOCP::OperationResultSignal, this, &EHT::OperationResultSlot);
	//TXT显示
	connect(pIOCP, SIGNAL(ShowTxt(QString, QVariant)), this->parent(), SLOT(ShowTxtToUI(QString, QVariant)), Qt::QueuedConnection);
	pIOCP->g_MQProducer_Data = g_MQProducer_Data;
	pIOCP->g_MQProducer_MDB = g_MQProducer_MDB;
	pIOCP->g_MQProducer_WebSrv = g_MQProducer_WebSrv;
	pIOCP->g_WebCommServer = g_WebCommServer;
}
bool EHT::IsRun()
{
	return m_IsRun;
}
bool EHT::IsLegallyPort(int Port)
{
	//初始化WSA    加载socket动态链接库
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsaData;     // 接收Windows Socket的结构信息
	if (WSAStartup(sockVersion, &wsaData) != 0)
		return false;
	SOCKET BindSocket;
	BindSocket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	SOCKADDR_IN  srvAddr;
	//获取本地IP
	LPCSTR  ch;
	QByteArray ba = m_IP.toLatin1();
	ch = ba.data();
	srvAddr.sin_addr.S_un.S_addr = inet_addr(ch);
	srvAddr.sin_family = AF_INET;
	srvAddr.sin_port = htons(Port);
	//绑定SOCKET到本机
	int bindResult = ::bind(BindSocket, (SOCKADDR*)&srvAddr, sizeof(SOCKADDR_IN));
	if (SOCKET_ERROR == bindResult)
		return false;
	closesocket(BindSocket);
	return true;
}
void EHT::NewConnectionSlot(QString IP, int Port, int m_Port, uint Socket)
{
	QString status;
	status = QString("新的连接:") + IP + ":" + QString::number(Port) + QString(",监听端口:") + QString::number(m_Port);
	emit NewConnectionSignal(status);
}
void EHT::OffLineSlot(unsigned int Socket)
{
	for (int i = 0; i < Clients.size(); i++)
	{
		//找到离线
		if (Clients[i]->Socket == Socket)
		{
			QDateTime current_date_time = QDateTime::currentDateTime();
			QString current_date = current_date_time.toString("yyyy-MM-dd hh:mm:ss");
			LogWrite::WriteLog(QString("台站号 ") + Clients[i]->StationID + QString(",设备号 ") + Clients[i]->DeviceID + QString("已经断开连接"));
			Clients[i]->Socket = 0;//Socket置零
			Clients[i]->Online = false;//设置离线状态

			QJsonObject HBJson;
			HBJson.insert("FUID", Clients.at(i)->FUID);
			HBJson.insert("HBTime", current_date);
			HBJson.insert("ServiceTypeID", m_ServiceID);
			HBJson.insert("StationID", Clients.at(i)->StationID);
			HBJson.insert("OnLineStatus", false);
			QJsonDocument document;
			document.setObject(HBJson);
			QByteArray byteArray = document.toJson(QJsonDocument::Compact);
			LPCSTR dataChar;
			dataChar = byteArray.data();
			//发送至消息中间件
			if (g_MQProducer_Data->send(dataChar) == 0)
				GetErrorSlot(10304);
			break;
		}
	}
}
void EHT::NewDataSlot(QVariant Var)
{
	LPPER_HANDLE_DATA perHandleData = Var.value<LPPER_HANDLE_DATA>();
	//台站号为空
	if (perHandleData->StationID == NULL&&perHandleData->DeviceID==NULL)
		return;
	//站号转变
	if (m_ServiceID == NXSQ || m_ServiceID == NW)
	{
		if (SIM2Staion.contains(perHandleData->StationID))
		{
			//找到特定的“键-值”对
			QMap<QString, QString>::iterator it = SIM2Staion.find(perHandleData->StationID);
			perHandleData->StationID = it.value();
		}
	}
	//创建设备唯一标识
	int FUID=CreateUID(m_ServiceName, perHandleData->StationID, perHandleData->DeviceID);
	perHandleData->FUID =FUID;
	QDateTime current_date_time = QDateTime::currentDateTime();
	for (int i = 0; i < Clients.count(); i++)
	{
		//存在
		if(FUID==Clients.at(i)->FUID)
		{
			//离线设备 重新上线线提示
			if (Clients.at(i)->Online == false)
			{
				//上线通知
				QJsonObject HBJson;
				HBJson.insert("FUID", QString::number(FUID));
				HBJson.insert("ServiceTypeID",m_ServiceID);
				HBJson.insert("StationID", perHandleData->StationID);
				HBJson.insert("HBTime", current_date_time.toString("yyyy-MM-dd hh:mm:ss"));
				HBJson.insert("StationID", perHandleData->StationID);
				HBJson.insert("OnLineStatus", true);
				QJsonDocument document;
				document.setObject(HBJson);
				QByteArray byteArray = document.toJson(QJsonDocument::Compact);
				LPCSTR dataChar;
				dataChar = byteArray.data();
				//发送至消息中间件
				if (g_MQProducer_Data->send(dataChar) == 0)
					GetErrorSlot(10304);
				//高标准粮田和三农上线需对时
				if (m_ServiceID == NTXQH || m_ServiceID == SN)
					func_SetTime_Lib(perHandleData->StationID, perHandleData->Socket);
				LogWrite::WriteLog(QString("新设备上线,台站号为：") + Clients[i]->StationID + QString(",设备号为：") + Clients[i]->DeviceID);
				//更新登录时间
				Clients[i]->LoginTime = current_date_time;
			}
			//设备更新信息
			Clients[i]->LatestTimeOfHeartBeat = current_date_time;//更新时间
			Clients[i]->Socket = perHandleData->Socket;//更新Socket号
			Clients[i]->IP = perHandleData->IP;//更新IP
			Clients[i]->Port = perHandleData->Port;//更新端口
			Clients[i]->Online = true;//设置在线
			return;
		}
	}
	//不存在插入
	FACILITYINFO *clientinfo=new FACILITYINFO;
	clientinfo->FUID = FUID;
	clientinfo->ServiceName = m_ServiceName;
	clientinfo->IP = perHandleData->IP;
	clientinfo->Port = perHandleData->Port,
	clientinfo->Socket = perHandleData->Socket;
	clientinfo->StationID = perHandleData->StationID;
	clientinfo->DeviceID = perHandleData->DeviceID;
	clientinfo->LoginTime = current_date_time;
	clientinfo->Online = true;
	clientinfo->LatestTimeOfHeartBeat = current_date_time;
	Clients.push_back(clientinfo);
	//高标准粮田和三农上线需对时
	if (m_ServiceID == NTXQH || m_ServiceID == SN)
	{
		func_SetTime_Lib(perHandleData->StationID, perHandleData->Socket);
	}
	//新设备上线
	QJsonObject HBJson;
	HBJson.insert("FUID", QString::number(FUID));
	HBJson.insert("ServiceTypeID", m_ServiceID);
	HBJson.insert("StationID", perHandleData->StationID);
	HBJson.insert("HBTime", current_date_time.toString("yyyy-MM-dd hh:mm:ss"));
	HBJson.insert("StationID",perHandleData->StationID);
	HBJson.insert("OnLineStatus", true);
	QJsonDocument document;
	document.setObject(HBJson);
	QByteArray byteArray = document.toJson(QJsonDocument::Compact);
	LPCSTR dataChar;
	dataChar = byteArray.data();
	//发送至消息中间件
	if (g_MQProducer_Data->send(dataChar)==0)
		GetErrorSlot(10304);
	
	LogWrite::WriteLog(QString("新设备已连接，台站号为：") + clientinfo->StationID+QString("，设备号为：")+ clientinfo->DeviceID);
	QVariant var;
	var.setValue(clientinfo);
	emit  OnLineSignal(var);;//刷新UI
}
void EHT::NewDataSlot(QVariant Var, int File)
{
	LPPER_HANDLE_DATA perHandleData = Var.value<LPPER_HANDLE_DATA>();
	//台站号为空
	if (perHandleData->StationID == NULL)
		return;
	//农委站号转变
	if (m_ServiceID ==NXSQ||m_ServiceID==NW)
	{
		if (SIM2Staion.contains(perHandleData->StationID))
		{
			//找到特定的“键-值”对
			QMap<QString, QString>::iterator it = SIM2Staion.find(perHandleData->StationID);
			perHandleData->StationID = it.value();
		}
	}
	switch (File)
	{
	case IMAGE:
	{
		IsExistImage = false;
		ReHandleZB_IMAGE->start(1000 * 10);
	}
	break;
	case TXT:
	{
		IsExistTXT= false;
		ReHandleZB_TXT->start(1000* 10);
	}
		break;
	default:
		break;
	}
	//创建设备唯一标识
	int UID = CreateUID(m_ServiceName, perHandleData->StationID, perHandleData->DeviceID);
	QDateTime current_date_time = QDateTime::currentDateTime();
	for (int i = 0; i < Clients.count(); i++)
	{
		//存在
		//if (Clients[i].DeviceID.toUpper().compare(DeviceID.toUpper()) == 0 && Clients[i].StationID.toUpper().compare(StationID.toUpper()) == 0)
		if(UID==Clients[i]->FUID)
		{
			Clients[i]->LatestTimeOfHeartBeat = current_date_time;//更新时间
			Clients[i]->Socket = perHandleData->Socket;//更新Socket号
			Clients[i]->IP = perHandleData->IP;//更新IP
			Clients[i]->Port = perHandleData->Port;//更新端口
			Clients[i]->Online = true;//设置在线
			return;
		}
	}
	//不存在插入
	FACILITYINFO *clientinfo = new FACILITYINFO;
	clientinfo->FUID = CreateUID(m_ServiceName, perHandleData-> StationID, perHandleData->DeviceID);
	clientinfo->ServiceName = m_ServiceName;
	clientinfo->IP = perHandleData->IP;
	clientinfo->Port = perHandleData->Port,
	clientinfo->Socket = perHandleData->Socket;
	clientinfo->StationID = perHandleData->StationID;
	clientinfo->DeviceID = perHandleData->DeviceID;
	clientinfo->LoginTime = current_date_time;
	clientinfo->Online = true;
	clientinfo->LatestTimeOfHeartBeat = current_date_time;
	Clients.push_back(clientinfo);
	LogWrite::WriteLog(QString("新设备已连接，台站号为：") + clientinfo->StationID + QString("，设备号为：") + clientinfo->DeviceID);
	QVariant var;
	var.setValue(clientinfo);
	emit  OnLineSignal(var);;//刷新UI
}
void EHT::MoveImageToDesAddr()
{
	if (IsExistImage)
		ReHandleZB_IMAGE->stop();
	
	QString fileName = "E:\\EcologyImage";
	QDir dir(fileName);
	QStringList filter;
	filter << QString("*.jpeg") << QString("*.jpg") << QString("*.png") << QString("*.tiff") << QString("*.gif") << QString("*.bmp");
	dir.setFilter(QDir::Files | QDir::NoSymLinks);//设置类型过滤器，只为文件格式
	dir.setNameFilters(filter);
	QList<QFileInfo> *fileInfo = new QList<QFileInfo>(dir.entryInfoList(filter));
	int dir_count = dir.count();
	for (int i = 0; i < dir_count; i++)
	{
		//找到是图片
		QString path = fileInfo->at(i).filePath();
		QString name = fileInfo->at(i).fileName();
		int sizeOfImg = fileInfo->at(i).size();
		//获取图片名称
		QStringList namestrlit = name.split(".");
		if (namestrlit.count() < 1)
			continue;
		QStringList strName = name.split("_");
		if (strName.count() != 4)
			continue;
		QStringList strDll = strName.at(3).split(".");
		QString DeviceID = strDll.at(0);
		QString OBcurrent_date = strName.at(2);
		QString StationID = strName.at(0);

		QDateTime current_date_time = QDateTime::fromString("yyyyMMddhhmmss");
		QString yy = current_date_time.toString("yyyy");
		QString mm = current_date_time.toString("MM");
		QString dd = current_date_time.toString("dd");

		//生成原始图和缩略图
		QString DesFile_Image = "D://Tomcat 8.0//webapps//byd//upload//yszb//" + yy+"//"+mm+"//"+dd;//原始图
		QString DesFile_MinImage = "D://Tomcat 8.0//webapps//byd//upload//slzb//" +yy + "//" + mm + "//" + dd;//缩略图
		QDir dir(DesFile_Image);
		if (!dir.exists())
			dir.mkpath(DesFile_Image);//创建多级目录
		QDir dir_mi(DesFile_MinImage);
		if (!dir_mi.exists())
			dir_mi.mkpath(DesFile_MinImage);//创建多级目录
		DesFile_Image += "//" + name;
		DesFile_MinImage += "//" + name;
		QImage minImage;
		minImage.load(path);
		minImage = minImage.scaled(300, 200, Qt::KeepAspectRatio);
		minImage.save(DesFile_MinImage, "JPG");
		//XML文件处理
		QJsonObject Json;
	
		//原图名称
		Json.insert("ImageName",name);
		//原图路径
		Json.insert("ImagePath","//byd//upload//yszb//" + yy + "//" + mm + "//" + dd +"//" + name);
		//缩略图路径
		Json.insert("MinImgPath", "//byd//upload//slzb//" + yy + "//" + mm + "//" + dd + "//" + name);
		//设备ID
		Json.insert("DeviceID", DeviceID);
		//设备是否含有区站号
		Json.insert("ContainSID", false);
		Json.insert("StationID", DeviceID);
		//观测时间
		Json.insert("ObserveTime", OBcurrent_date);
		//业务号
		Json.insert("ServiceTypeID", "18");

		QJsonDocument document;
		document.setObject(Json);
		QByteArray byteArray = document.toJson(QJsonDocument::Compact);
		LPCSTR dataChar;
		dataChar = byteArray.data();
		if (g_MQProducer_Data->send(dataChar)==0)
		{

			GetErrorSlot(10304);
		}
		//复制成功后 删除源文件
		QFile::copy(path, DesFile_Image);
		QFile::remove(path);
		IsExistImage = true;
	}
}
void EHT::MoveTXTToDesAddr()
{
	if (IsExistTXT)
		ReHandleZB_TXT->stop();
	QDateTime current_date_time = QDateTime::currentDateTime();
	QString current_date = current_date_time.toString("yyyy-MM-dd");
	QString fileName = "E:\\EcologyImage";
	QDir dir(fileName);
	QStringList filter;
	filter << QString("*.txt");
	dir.setFilter(QDir::Files | QDir::NoSymLinks);//设置类型过滤器，只为文件格式
	dir.setNameFilters(filter);
	QList<QFileInfo> *fileInfo = new QList<QFileInfo>(dir.entryInfoList(filter));
	int dir_count = dir.count();
	for (int i = 0; i < dir_count; i++)
	{
		//找到是TXT
		QString path = fileInfo->at(i).filePath();
		QString name = fileInfo->at(i).fileName();
		QString DesFile_TXT = "D://SH_ZB_TXT//" + current_date;//目的路径
		QDir dir(DesFile_TXT);
		if (!dir.exists())
			dir.mkpath(DesFile_TXT);//创建多级目录
		DesFile_TXT += "\\" + name;
		
		//复制成功后 删除源文件
		QFile::copy(path, DesFile_TXT);
		QFile::remove(path);
		IsExistTXT = true;
	}
}
void EHT::MoveXMLToDesAddr()
{
	QJsonObject Json;
	QDateTime current_date_time = QDateTime::currentDateTime();
	QString current_date = current_date_time.toString("yyyy-MM-dd");
	QString fileName = "E:\\EcologyImage";
	QDir dir(fileName);
	QStringList filter;
	filter << QString("*.xml");
	dir.setFilter(QDir::Files | QDir::NoSymLinks);//设置类型过滤器，只为文件格式
	dir.setNameFilters(filter);
	QList<QFileInfo> *fileInfo = new QList<QFileInfo>(dir.entryInfoList(filter));
	int dir_count = dir.count();
	for (int i = 0; i < dir_count; i++)
	{
		//找到是XML
		QString path = fileInfo->at(i).filePath();
		QString name = fileInfo->at(i).fileName();
		QStringList strName = name.split("_");
		if (strName.count() != 4)
			continue;
		QStringList strDll = strName.at(3).split(".");
		QString DeviceID = strDll.at(0);
		QString OBcurrent_date = strName.at(2);
		QString StationID = strName.at(0);

		QString DesFile_XML = "D://SH_ZB_XML//" + current_date;//目的路径
		QDir dir(DesFile_XML);
		if (!dir.exists())
			dir.mkpath(DesFile_XML);//创建多级目录
		DesFile_XML += "\\" + name;
		//复制成功后 删除源文件
		QFile::copy(path, DesFile_XML);
	    QFile::remove(path);
		//解析文件
		QFile file(DesFile_XML); //相对路径、绝对路径、资源路径都行
		if (!file.open(QFile::ReadOnly))
			return;

		QDomDocument doc;
		if (!doc.setContent(&file))
		{
			file.close();
			return;
		}
		file.close();
	
		QDomElement root = doc.documentElement(); //返回根节点
		QDomNode node = root.firstChildElement("currentCoverage");
		Json.insert("Coverage", node.toElement().text());
		node = root.firstChildElement("density");
		Json.insert("Density", node.toElement().text());
		node = root.firstChildElement("height");
		Json.insert("CanopyHeight", node.toElement().text());
		//设备ID
		Json.insert("DeviceID", DeviceID);
		//设备是否含有区站号
		Json.insert("ContainSID", false);
		Json.insert("StationID", DeviceID);
		//观测时间
		Json.insert("ObserveTime", OBcurrent_date);
		//业务号
		Json.insert("ServiceTypeID", "18");

		QJsonDocument document;
		document.setObject(Json);
		QByteArray byteArray = document.toJson(QJsonDocument::Compact);
		LPCSTR dataChar;
		dataChar = byteArray.data();
		if (g_MQProducer_Data->send(dataChar) == 0)
			GetErrorSlot(10304);
	}
}
void EHT::OperationResultSlot(QJsonObject Json, QVariant Var)
{
	LPPER_HANDLE_DATA PerHandleData = Var.value<LPPER_HANDLE_DATA>();
	QStringList ValueList;
	QJsonObject Params = Json.find("Parameter").value().toObject();
	int ParamsCount = Params.find("Count").value().toInt();
	QStringList commLst;
	for (int i = 0; i < ParamsCount; i++)
	{
		QJsonValue value = Params.find("Params" + QString::number(i + 1)).value();  // 获取指定 key 对应的 value
		if (value.isString()) 
		{
			// 判断 value 是否为字符串
			QString paramter = Params.find("Params" + QString::number(i + 1)).value().toString();
			if (paramter != NULL)
				ValueList.append(paramter);
		}
		else if (value.isDouble())
		{
			int paramter = Params.find("Params" + QString::number(i + 1)).value().toInt();
			if (paramter != NULL)
				ValueList.append(QString::number(paramter));
		}
	}
	//发送至消息队列
	if(0!=PerHandleData->FUID)
		ResponseTo(Json,PerHandleData->FUID);
}
void EHT:: GetErrorSlot(int ErrorMSG)
{
	QString strMSG;
	switch (ErrorMSG)
	{
	case 1:
		strMSG = QString("系统运行正常");
		break;
	case 10300: case 10301: case 10302:
		strMSG = QString("通信初始化失败！");
		break;
	case 10304:
		strMSG = QString("消息中间件通信异常！");
		break;
	case 10305:
		strMSG = QString("数据内存溢出");
		break;
	case 10036:
		strMSG = QString("Web监听端口异常");
		break;
	case -4:
		strMSG = QString("服务器间通信异常！");
		break;
	case 10311:
		strMSG = QString("端口号监听失败！");
		break;
	default:
		strMSG = QString::number(ErrorMSG);
		break;
	}
	RefreshStatus(strMSG);
	LogWrite::WriteLog(strMSG);
}
void EHT::Convert2StationID()
{
	//读取Command.ini路径
	QString path = QCoreApplication::applicationDirPath() + "//SIM2STATION.ini";
	//打开INI文件
	QSettings configIniRead(path, QSettings::IniFormat);
	//终端命令个数
	int Count = configIniRead.value("NW/Count").toInt();
	//遍历终端命令
	for (int i = 0; i < Count; i++)
	{
		QString key = "/NW/STATION" + QString::number(i);
		QString StationID = configIniRead.value(key).toString();
		key = "/NW/SIM" + QString::number(i);
		QString SIMID = configIniRead.value(key).toString();
		SIM2Staion.insert(SIMID, StationID);
	}
}
void EHT::SetTime()
{
	if (!m_IsRun)
		return;
	for (int i = 0; i < Clients.size(); i++)
	{
		//判断是否在线
			if (Clients[i]->Online == false)
				continue;
			func_SetTime_Lib(Clients[i]->StationID,Clients[i]->Socket);
			LogWrite::WriteLog(QString( "台站号：") + Clients[i]->StationID + QString("，设备号 ") + Clients[i]->DeviceID +QString( "自动矫正时钟."));
	}
}
void EHT::OfflineCheck()
{
	QDateTime currentTime = QDateTime::currentDateTime();
	for (int i = 0; i < Clients.size(); i++)
	{
		int time_t = currentTime.toTime_t() - Clients[i]->LatestTimeOfHeartBeat.toTime_t();
			//大于5分钟
			if (time_t >300 && (Clients.at(i)->Online == true))
			{
				Clients[i]->Online = false;
				QJsonObject HBJson;
				HBJson.insert("FUID", Clients.at(i)->FUID);
				QDateTime current_date_time = QDateTime::currentDateTime();
				QString current_date = current_date_time.toString("yyyy-MM-dd hh:mm:ss");
				HBJson.insert("ServiceTypeID", m_ServiceID);
				HBJson.insert("StationID",Clients.at(i)->StationID);
				HBJson.insert("HBTime", current_date);
				HBJson.insert("OnLineStatus", false);
				QJsonDocument document;
				document.setObject(HBJson);
				QByteArray byteArray = document.toJson(QJsonDocument::Compact);
				LPCSTR dataChar;
				dataChar = byteArray.data();
				//发送至消息中间件
				if (g_MQProducer_Data->send(dataChar) == 0)
					GetErrorSlot(10304);
				LogWrite::WriteLog(QString("未检测到心跳包,区站号:") + Clients[i]->StationID + QString(",设备号:") + Clients[i]->DeviceID + QString("已离线"));
			}
	}
}
int  EHT::OnLineCount()
{
	int Count = 0;
	for (int i = 0; i < Clients.count(); i++)
	{
		if (Clients[i]->Online == true)
			Count++;
	}
	return Count;
}
void EHT::timerEvent(QTimerEvent *event)
{
	for (int i = ClientsQ.count() - 1; i > -1; i--)
	{
		if (++(ClientsQ[i].Count) > TIMEOUT)
		{
			m_timerMutex.lock();
			ClientsQ.removeAt(i);
			m_timerMutex.unlock();
		}
	}
}
void EHT::ResponseTo(QJsonObject Json,int FUID)
{
	//查找请求列表是否有此设备的请求
	for (int i = ClientsQ.count() - 1; i > -1; i--)
	{
		if (ClientsQ[i].FUID == FUID)
		{
			Json.insert("UID", ClientsQ[i].UID);
			//发送至Web服务器
			QJsonDocument document;
			document.setObject(Json);
			QByteArray byteArray = document.toJson(QJsonDocument::Compact);
			LPCSTR dataChar;
			dataChar = byteArray.data();
			if (g_MQProducer_WebSrv->send(dataChar) == 0)
				GetErrorSlot(10304);
			m_timerMutex.lock();
			ClientsQ.removeAt(i);
			m_timerMutex.unlock();
			break;
		}
	}
}
int EHT::CreateUID(QString ServiceName, QString StationID, QString DeviceID)
{

	int UID = 0;
	for (int i = 0; i < ServiceName.count(); i++)
	{
		UID += (int)ServiceName.at(i).unicode();
	}
	for (int i = 0; i < StationID.count(); i++)
	{
		UID += (int)StationID.at(i).unicode();
	}
	for (int i = 0; i < DeviceID.count(); i++)
	{
		UID += (int)DeviceID.at(i).unicode();
	}
	return UID;
}
void EHT::RequestFor(QString UID, int FUID, int Command, QStringList CommLst)
{
	//当前业务处在未监听状态
	if (!m_IsRun)
		return;
	u_int Socket = 0;
	//查找时候含有UID
	bool IsExist = false;
	Socket = FindSocket(UID,IsExist);
	//此业务不含该设备
	if (false == IsExist)
		return;
	switch (Socket)
	{
	//设备已离线处理
	case 0:
	{
		QJsonObject json, subJson;
		json.insert("UID", UID);
		json.insert("FUID",FUID);
		subJson.insert("Count", 1);
		subJson.insert("Params1", "offline");
		json.insert("Command", Command);
		json.insert("Parameter", subJson);
		//发送至Web响应消息队列
		QJsonDocument document;
		document.setObject(json);
		QByteArray byteArray = document.toJson(QJsonDocument::Compact);
		LPCSTR dataChar;
		dataChar = byteArray.data();
		if (g_MQProducer_WebSrv->send(dataChar)== 0)
			GetErrorSlot(10304);
		return;
	}
	//设备在线
	default:
	{
		WebSrvClient client;
		client.UID = UID;
		client.Count = 0;
		ClientsQ.append(client);
		break;
	}
	}
	func_SetCommand(Socket, Command, CommLst);
}
bool EHT::GetFID(int FUID)
{
	for (int i = 0; i < Clients.count(); i++)
	{
		if (Clients.at(i)->FUID == FUID)
			return true;
	}
	return false;
}
/* 未完成
void EHT::OffShowTxt(uint Socket,bool IsConnect)
{
	//关闭信号槽
	disconnect(pIOCP, SIGNAL(ShowTxt(QString, QVariant)), this->parent(), SLOT(ShowTxtToUI(QString, QVariant)));
	for (QList<FACILITYINFO *>::iterator iter=Clients.begin();iter!=Clients.end(); iter++)
	{
		//设备在当前业务内,并且打开
		if (Socket == (*iter)->Socket && IsConnect)
			//connect(pIOCP, SIGNAL(ShowTxt(QString, QVariant)), this->parent(), SLOT(ShowTxtToUI(QString, QVariant)));
		connect(pIOCP, &IOCP::ShowTxt, (MainWnd *)this->parent(), &MainWnd::ShowTxtToUI, Qt::QueuedConnection);
		break;
	}
}
*/

