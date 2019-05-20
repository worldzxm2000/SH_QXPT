#pragma once

#include <QObject>
#include <QWidget>
#include<QLibrary>
#include<QThreadPool>
#include"IOCP.h"
#include<QMap>
#include<QTimer>
#include"Global_Var.h"
#include <QVariant>
class EHT : public QWidget
{
	Q_OBJECT

public:
	EHT(QWidget *parent);
	~EHT();
public:
	//SQL数据队列
	MQProducer *g_MQProducer_Data;
	//MangoBD数据队列
	MQProducer *g_MQProducer_MDB;
	//WebSrv响应队列
	MQProducer *g_MQProducer_WebSrv;
	//WebSrv请求队列
	WebCommServer *g_WebCommServer;
	/*
	* @brief 初始化IOCP，设置参数
	* @return 返回说明
	无
	*/
	void InitIOCP();
	/*
	* @brief 加载业务解析库
	* @param Lib_Path 参数1 Lib库类地址
	* @param isLoad 参数2 是否为加载过解析库
	true: 第一次加载；
	false: 已加载过；
	* @return 返回说明
	1：成功加载解析库
	0：取消加载解析库
	-1: 非业务解析库；
	-2: 业务监听端口被占用
	*/
	LRESULT LoadLib(QString Lib_Path, bool isLoad);
	/*
	* @brief 加载业务解析库
	* @param Lib_Path 参数1 Lib库类地址
	* @param IP 参数2 业务监听IP
	* @param Port 参数3 业务监听端口
	* @param isLoad 参数4 是否为加载过解析库
	true: 第一次加载；
	false: 已加载过；
	* @return 返回说明
	1：成功加载解析库
	0：取消加载解析库
	-1: 非业务解析库；
	-2: 业务监听端口被占用
	*/
	LRESULT LoadLib(QString Lib_Path, QString IP, int Port, bool isLoad);
	/*
	* @brief 卸载业务Lib库类
	* @return 返回说明
	true: 卸载成功
	false：卸载失败
	*/
	bool UnloadLib();
	/*
	* @brief 获取业务ID
	* @return 返回说明
	value: 业务ID
	*/
	int GetServiceID();
	/*
	* @brief 获取业务名称
	* @return 返回说明
	value: 业务名称
	*/
	QString GetServiceName();
	/**
	* @brief 获取业务监听端口号
	* @return 返回说明
	value: 业务监听端口号
	*/
	int GetPort();
	/**
	* @brief 通过设备UID查找设备Socket号
	* @param UID    参数1 设备UID号
	* @return 返回说明
	0 : 未找到Socket号或者该设备已经离线
	value: 该设备的Socket号
	*/
	u_int FindSocket(QString UID,bool &IsExist);
	/**
	* @brief 业务描述
	* @return 返回说明
	value: 业务描述说明
	*/
	QString GetAttribute();
	/*
	* @brief 获取数据解析
	* @return 返回说明
	value: Lib解析库中数据解析函数
	*/
	Char2Json GetDataFunc();
	/*
	* @brief 启动监听数据服务，启动IOCP类，添加到ThreadPool池里面
	* @param ThreadPool    参数1 线程池
	* @return 返回说明
	true: 启动成功
	false：启动失败
	*/
	bool Run(QThreadPool &ThreadPool);
	/*
	* @brief 结束监听数据服务，卸载Lib库，关闭IOCP
	* @return 返回说明
	true: 关闭成功
	false：关闭失败
	*/
	bool Stop();
	/*
	* @brief 返回运行状态
	* @return 返回说明
	true:正在监听
	false：停止监听
	*/
	bool IsRun();
	/*
	* @brief  获取在线设备个数
	* @param event 参数1 封装发送协议Json
	* @return 返回说明
	无
	* @Other 每一秒进行计数，当计数器超过10时，Time Out。
	*/
	int  OnLineCount();
	/*
	* @brief  找到该业务类是否含有设备UID
	* @param FUID 参数1 设备UID
	* @return 返回说明
	true：该业务含有该设备
	false：该业务不含该有设备
	*/
	bool GetFID(int FUID);
	///*
	//* @brief    关闭TXT显示
	//* @param Socket 参数1 设备Socket号
	//* @param IsConnect 参数2 打开/关闭开关
	//* @return 返回说明
	//  无
	//* @Other 通过设备Socket找到该业务，关闭其他TXT显示，未完成
	//*/
	//void OffShowTxt(uint Socket,bool IsConnect);
private:
	//获取连接客户端数组
	QList<FACILITYINFO*> Clients;
	//植被重新处理定时器
	QTimer *ReHandleZB_IMAGE;
	QTimer *ReHandleZB_XML;
	QTimer *ReHandleZB_TXT;
	//是否存在JPG文件
	bool IsExistImage;
	//是否存在TXT
	bool IsExistTXT;
	//计数定时器标识
	int m_TimeOutTimerID;
	//IOCP运行状态
	bool m_IsRun;
	//IOCP处理线程
	IOCP *pIOCP;
	//Lib加载类
	QLibrary m_Lib;
	//服务监听IP号
	QString m_IP;
	//服务监听端口号
	int m_Port;
	//业务类型
	int m_ServiceID;
	//业务名称
	QString m_ServiceName;
	//描述
	QString m_Attribute;
	//数据解析
	Char2Json m_DataFunc;
	//SIM卡号对应区站号
	QMap<QString, QString> SIM2Staion;
	//自动对时时钟
	QTimer *SetTimeTimer;
	//离线检测时钟
	QTimer *OffLineTimer;
	//对时命令
	SetTime_Lib func_SetTime_Lib;
	//显示返回值
	SetValueToControlWidget_Lib func_SetValueToControlWidget;
	//终端命令
	SetCommand_Lib func_SetCommand;
	//路径
	QString m_LibPath;
	//Web请求连接池
	QList<WebSrvClient> ClientsQ;
	/*
	* @brief 判断端口合法性
	@param Port    参数1 端口号
	* @return 返回说明
	true:端口无占用
	false：端口已被占用
	*/
	bool IsLegallyPort(int Port);
	/*
	* @brief  读取SIM卡号配置文件，转成区站号（农委）
	* @param 无
	* @return 返回说明
	无
	*/
	void Convert2StationID();
	/*
	* @brief   WebSrv请求超时检测
	* @param event 参数1 定时器ID信息
	* @return 返回说明
	无
	* @Other 每一秒进行计数，当计数器超过10时，Timeout。
	*/
	virtual void timerEvent(QTimerEvent *event);
	/*
	* @brief    查找相对应的Web请求
	* @param Json 参数1 封装发送协议Json
	* @param FUID 参数2 响应设备UID号
	* @return 返回说明
	无
	* @Other 通过设备UID找到请求响应的UID，发至MQ。
	*/
	void ResponseTo(QJsonObject json, int FUID);
	/*
	* @brief    通过业务名称、台站号和设备号创建设备UID
	* @param ServiceName 参数1 业务名称
	* @param StationID 参数2 台站号
	* @param DeviceID 参数3 设备号
	* @return 返回说明
	value:设备UID号
	* @Other 通过设备FUID找到请求响应的UID，发至MQ。
	*/
	int  CreateUID(QString ServiceName, QString StationID, QString DeviceID);

private slots:
	/*
	* @brief    自动检测离线
	* @param PerHandleData 无
	* @return 返回说明
	无
	*/
	void OfflineCheck();
	/*
	* @brief  矫正时钟
	* @param 无
	* @return 返回说明
	无
	*/
	void SetTime();
	/*
	* @brief    有新的连接加入
	* @param IP    参数1     新连接IP地址
	* @param Port  参数2     新连接端口号
	* @param m_Port  参数3   服务器监听端口号
	* @param Socket  参数4   Socket号
	* @return 返回说明
	无
	*/
	void NewConnectionSlot(QString IP, int Port, int m_Port, uint Socket);
	/*
	* @brief    设备离线通知
	* @param Socket  参数1   Socket号
	* @return 返回说明
	无
	*/
	void OffLineSlot(unsigned int CltSocket);
	/*
	* @brief    设备上传数据
	* @param PerHandleData  参数1   连接的数据结构体
	* @return 返回说明
	无
	* @Other 设备第一次连接创建设备UID，通过UID查找设备内存；设备上下线提示；特殊设备的上线对时
	*/
	void NewDataSlot(QVariant var);
	/*
	* @brief    设备上传数据（湿地植被）
	* @param PerHandleData  参数1   连接的数据结构体
	* @param File 参数2  植被传送类型
	* @return 返回说明
	无
	* @Other 设备第一次连接创建设备UID，通过UID查找设备内存；设备上下线提示；特殊设备的上线对时
	*/
	void NewDataSlot(QVariant Var, int File);
	/*
	* @brief  获取错误
	* @param ErrorMSG 参数1 错误代码
	* @return 返回说明
	无
	*/
	void GetErrorSlot(int ErrorMSG);
	/*
	* @brief 设备命令返回结果处理
	* @param Json 参数1 设备返回结果Json
	* @paran Var 参数2 设备连接信息
	* @return 返回说明
	无
	@Other 设备返回结果，
	*/
	void OperationResultSlot(QJsonObject json, QVariant Var);
	/*
	* @brief    设备上传数据（湿地植被）图片处理
	* @param PerHandleData 无
	* @return 返回说明
	无
	* @Other 接收到图片处理命令后，在FTP指定磁盘寻找图片，处理后拷贝到指定磁盘位置
	*/
	void MoveImageToDesAddr();
	/*
	* @brief    设备上传数据（湿地植被）文本处理
	* @param PerHandleData 无
	* @return 返回说明
	无
	* @Other 接收到文本处理命令后，在FTP指定磁盘寻找文本，处理后拷贝到指定磁盘位置
	*/
	void MoveTXTToDesAddr();
	/*
	* @brief    设备上传数据（湿地植被）XML处理
	* @param PerHandleData 无
	* @return 返回说明
	无
	* @Other 接收到XML处理命令后，在FTP指定磁盘寻找文本，处理后拷贝到指定磁盘位置
	*/
	void MoveXMLToDesAddr();
	/*
	* @brief   读取设备参数指令
	* @param UID 参数1 WebSrv请求UID
	* @param FUID 参数2 台站UID
	* @param Command 参数3 命令号
	* @param CommLst 参数4 命令组
	* @return 返回说明
	无
	* @Other 通过设备FUID找到请求响应的UID，发至MQ。
	*/
	void RequestFor(QString UID, int FUID, int Command, QStringList CommLst);

signals:
	/*
	* @brief   新连接通知
	* @param Status 参数1 新连接通知
	* @return 返回说明
	无
	*/
	void NewConnectionSignal(QString Status);
	/*
	* @brief  设备发送数据信息
	* @param Var 参数1 设备连接信息
	* @return 返回说明
	无
	*/
	void OnLineSignal(QVariant Var);
	/*
	* @brief  界面显示状态信息
	* @param Result 参数1 状态信息
	* @return 返回说明
	无
	*/
	void RefreshStatus(QString Status);
};
