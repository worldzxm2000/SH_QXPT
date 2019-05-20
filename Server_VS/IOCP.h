#ifndef IOCP_H
#define IOCP_H

#endif // IOCP_H
#include<QWidget>
#include<QObject>
#include"Global.h"
#include"Global_Var.h"
#include<Windows.h>
#include<qvector.h>
#include<qthread.h>
#include<QRunnable>
#include<QString>
#include<QJsonObject>
#include <mswsock.h> 
#include<QTimer>
#include <QVariant>
class  IOCP:public QObject,public QRunnable
{

    Q_OBJECT

public:
    IOCP();
    ~IOCP();
	//SQL数据队列
	MQProducer *g_MQProducer_Data;
	//MangoBD数据队列
	MQProducer *g_MQProducer_MDB;
	//WebSrv响应队列
	MQProducer *g_MQProducer_WebSrv;
	//WebSrv请求队列
	WebCommServer *g_WebCommServer;
	//数据解析
	Char2Json func_Char2Json;
	//获取设备信息
	GetFacilityInfo func_GetFacilityInfo;
	/*
	* @brief 设置监听号
	* @param Port 参数1 监听IP
	* @param IP  参数2 监听端口
	* @return 返回说明
	无
	*/
    void SetListenedPort(int Port, QString IP);
	/*
	* @brief 停止业务监听
	* @return 返回说明
	无
	*/
	void Stop();
protected:
	/*
	* @brief 监听线程
	* @return 返回说明
	无
	* @Other 同步阻塞接收新的Socket
	*/
	void run();
private:
	// 业务监听端口号
	int m_Port;
	//业务监听IP
	QString m_IP;
	/*
	//异步接收连接结构体
	LPFN_ACCEPTEX lpfnAcceptEx = NULL;
	LPFN_GETACCEPTEXSOCKADDRS lpfnGetAcceptExSockaddrs;
	*/
	//服务器端
	SOCKET m_SrvSocket;
	//连接信息数组
	QVector<LPPER_HANDLE_DATA> Sockets;
	//创建完成端口号
	HANDLE m_CompletionPort;
	//创建线程个数
	int m_ThreadsCount;
	//定时器标识号
	int m_TimeOutTimerID;
	//清理废弃资源定时器标号
	int m_ReleaseTimerID;
	/*
	* @brief IOCP处理线程
	* @param pParam 参数1 父类句柄等信息
	* @return 返回说明
	value :线程执行结果
	@Other 阻塞线程直到有I/O产生，依次判断处理
	*/
    static unsigned __stdcall ServerWorkThread(LPVOID pParam);
	/*
	* @brief IOCP处理设备发送数据
	* @param perIOData 参数1 I/O结构体，存储I/O数据
	* @param len 参数2 I/O数据个数
	* @param PerHandleData 参数3 连接结构体信息
	* @return 返回说明
	@Other 数据处理函数，调用Lib中数据解析函数，对数据解析。
	*/
    void DoRecvData(LPPER_IO_DATA perIOData, DWORD len, LPPER_HANDLE_DATA PerHandleData);
	/*
	* @brief 定时器处理
	* @param event 参数1 定时器信息
	* @return 返回说明
	无
	*/
	void timerEvent(QTimerEvent * event);
	/*
	* @brief 删除连接资源
	* @param lpPerhandleData 参数1 连接信息结构体
	* @return 返回说明
	无
	*/
	void ReleaseSocket(LPPER_HANDLE_DATA &lpPerhandleData);
    //信号量
signals:
	/*
	* @brief 发送错误信息
	* @param ErrorMSG 参数1 错误代码
	* @return 返回说明
	无
	*/
	void ErrorMSGSignal(int ErrorMSG);
	/*
	* @brief 界面显示接收数据
	* @param Txt 参数1 设备发送数据
	* @param PerHandleData 参数2 连接信息
	* @return 返回说明
	无
	*/
	void ShowTxt(QString Txt, QVariant PerHandleData);
	
	/*
	* @brief 数据通知
	* @param Var 参数1 连接信息
	* @return 返回说明
	无
	* @Other 数据通知(要素数据或者心跳数据)
	*/
	void NewDataSignal(QVariant Var);
	/*
	* @brief 数据通知（湿地植被）
	* @param Var 参数1 连接信息
	* @param File 参数2 处理文件类型（图片、TXT或者XML）
	* @return 返回说明
	无
	* @Other 数据通知(要素数据或者心跳数据)
	*/
	void NewDataSignal(QVariant Var,int File);
	/*
	* @brief    有新的连接加入
	* @param IP    参数1     新连接IP地址
	* @param Port  参数2     新连接端口号
	* @param m_Port  参数3   服务器监听端口号
	* @param Socket  参数4   Socket号
	* @return 返回说明
	无
	*/
	void NewConnectionSignal(QString IP, int Port, int m_Port, uint Socket);
	/*
	* @brief 设备命令返回结果处理
	* @param Json 参数1 设备返回结果Json
	* @paran Var 参数2 设备连接信息
	* @return 返回说明
	无
	@Other 设备返回结果，
	*/
	void OperationResultSignal(QJsonObject json, QVariant Var);
	/*
	* @brief    设备离线通知
	* @param Socket  参数1   Socket号
	* @return 返回说明
	无
	*/
	void OffLineSignal(unsigned int CltSocket);
};

