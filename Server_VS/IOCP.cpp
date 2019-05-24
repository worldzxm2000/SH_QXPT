#include "IOCP.h"
#include<process.h>
#include<qmessagebox.h>
#include"LogWrite.h"
#include<qdebug.h>
#include<qthread.h>
#include<qjsondocument.h>
#include<qdir.h>
#include <mswsock.h> 
#include <QDebug>
#define SEND 0
#define RECV 1
#define TIMEOUT 10
using namespace std;
QMutex m_timerMutexSocket;
IOCP::IOCP()
{
	m_ThreadsCount = 0;
	m_ReleaseTimerID = startTimer(1000*60*24);
}
IOCP::~IOCP()
{

}
void IOCP::SetListenedPort(int Port, QString IP)
{
	this->m_Port = Port;
	this->m_IP = IP;
	//开启定时器，做连接超时判断
	m_TimeOutTimerID = startTimer(1 * 1000);
}
void IOCP::Stop()
{
	//关闭定时器
	killTimer(m_TimeOutTimerID);
	killTimer(m_ReleaseTimerID);
	int result = -1;
	//先终止子进程，然后再断开Sokcet
	for (int i = 0; i < m_ThreadsCount; i++)
	{
		// 通知所有的完成端口操作退出  
		result = PostQueuedCompletionStatus(m_CompletionPort, 0, NULL, NULL);
	}
	//断开socket连接
	for (int i = 0; i < Sockets.count(); i++)
	{
		 shutdown(Sockets.at(i)->Socket, 2);
		 closesocket(Sockets.at(i)->Socket);
		emit OffLineSignal(Sockets.at(i)->Socket);
	}
	Sockets.clear();
	result = closesocket(m_SrvSocket);
	WSACleanup();
	LogWrite::WriteLog(QString::fromLocal8Bit("服务已关闭，端口号为：") + QString::number(m_Port));
}
void IOCP::run()
{
	//初始化WSA    加载socket动态链接库
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsaData;     // 接收Windows Socket的结构信息
	if (WSAStartup(sockVersion, &wsaData) != 0)
	{
		ErrorMSGSignal(10301);
		return;
	}
	//创建完成端口
	m_CompletionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
	//创建完成端口线程
	SYSTEM_INFO mySysInfo;
	GetSystemInfo(&mySysInfo);
	m_ThreadsCount = (mySysInfo.dwNumberOfProcessors);
	for (int i = 0; i < m_ThreadsCount; ++i)
	{
		HANDLE threadhandle = (HANDLE)_beginthreadex(NULL, 0, ServerWorkThread, (HANDLE)this, 0, NULL);
		::ResumeThread(threadhandle);
	}
	//设置socket
	m_SrvSocket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	SOCKADDR_IN  srvAddr;
	//获取本地IP
	LPCSTR  ch;
	QByteArray ba = m_IP.toLatin1();
	ch = ba.data();
	srvAddr.sin_addr.S_un.S_addr = inet_addr(ch);
	srvAddr.sin_family = AF_INET;
	srvAddr.sin_port = htons(m_Port);
	//绑定SOCKET到本机
	if (SOCKET_ERROR == ::bind(m_SrvSocket, (SOCKADDR*)&srvAddr, sizeof(SOCKADDR_IN)))
	{
		ErrorMSGSignal(10302);
		return;
	}
	// 将SOCKET设置为监听模式
	if (SOCKET_ERROR == ::listen(m_SrvSocket, SOMAXCONN))
	{
		ErrorMSGSignal(10303);
		return;
	}

	//同步阻塞accept
	while (1)
	{
		LPPER_HANDLE_DATA PerHandleData = new PER_HANDLE_DATA;;
		SOCKADDR_IN saRemote;
		int RemoteLen = sizeof(saRemote);
		//接收客户端连接
		SOCKET acceptSocket;
		//WSAID_ACCEPTEX
		acceptSocket = accept(m_SrvSocket, (SOCKADDR*)&saRemote, &RemoteLen);
		if (SOCKET_ERROR == acceptSocket)
			// 接收失败或者关闭
			break;

		//客户端socket与IOCP关联
		PerHandleData->FUID = 0;//设备UID
		PerHandleData->Socket = acceptSocket;//Sccket号
		PerHandleData->Port = saRemote.sin_port;//端口号
		PerHandleData->IP = inet_ntoa(saRemote.sin_addr);	//客户端IP
		PerHandleData->Available = false;//未识别连接
		PerHandleData->Timer = 0;//超时计数
		//客户端socket绑定IOCP
		CreateIoCompletionPort((HANDLE)(PerHandleData->Socket), m_CompletionPort, (DWORD)PerHandleData, 0);
		//IO重叠
		LPPER_IO_DATA PerIoData = NULL;
		PerIoData = (LPPER_IO_DATA)GlobalAlloc(GPTR, sizeof(PER_IO_DATA));
		ZeroMemory(&(PerIoData->overlapped), sizeof(OVERLAPPED));
		PerIoData->databuff.len = 4 * 1024;
		PerIoData->databuff.buf = PerIoData->buffer;
		PerIoData->operationType = RECV;

		//客户端socket添加入客户端数组
		Sockets.push_back(PerHandleData);
		//获取设备信息,判断连接是否为设备
		func_GetFacilityInfo(acceptSocket);
		
		emit NewConnectionSignal(PerHandleData->IP, PerHandleData->Port, m_Port, PerHandleData->Socket);
		DWORD RecvBytes = 0;
		DWORD Flags = 0;
		//接收数据
		WSARecv(PerHandleData->Socket, &(PerIoData->databuff), 1, &RecvBytes, &Flags, &(PerIoData->overlapped), NULL);
	}
}
void IOCP::timerEvent(QTimerEvent * event)
{
	if (m_TimeOutTimerID == event->timerId())
	{
		//定时释放资源
		for (int i = Sockets.count() - 1; i > -1; i--)
		{
			LPPER_HANDLE_DATA perhandledata = Sockets.at(i);
			//释放已经删除的连接信息
			if (perhandledata == NULL)
			{
				ReleaseSocket(perhandledata);
				continue;
			}
			else
			{
				//判断连接是否为有效连接，如果没有台站和设备号信息，视为无效连接，删除。
				if (false == Sockets[i]->Available)
				{
					if (++Sockets[i]->Timer > TIMEOUT)
					{
						shutdown(Sockets.at(i)->Socket, 2);
						closesocket(Sockets[i]->Socket);
					}
				}
			}
		}
	}
	//判断连接是否为有效连接,删除过期连接。
	else if (m_ReleaseTimerID==event->timerId())
	{
		for (int i = Sockets.count() - 1; i > -1; i--)
		{
			QString test = "test\r\n";
			QByteArray ba = test.toLocal8Bit();
			char *pStr = ba.data();
			int result = ::send(Sockets[i]->Socket,pStr, ba.count(), 0);
			if (result < 0)
			{
				shutdown(Sockets.at(i)->Socket, 2);
				closesocket(Sockets.at(i)->Socket);
			}
		}
	}
}
unsigned IOCP::ServerWorkThread(LPVOID pParam)
{
	try
	{
		IOCP *pIOCP = (IOCP *)pParam;
		DWORD BytesTransferred = 0;
		HANDLE m_CompletionPort = pIOCP->m_CompletionPort;
		LPOVERLAPPED IpOverlapped;
		LPPER_IO_DATA PerIoData = NULL;
		LPPER_HANDLE_DATA PerHandleData = NULL;
		DWORD RecvBytes;
		DWORD Flags = 0;
		BOOL bRet = FALSE;
		DWORD error = 0;
		while (1)
		{
			bRet = GetQueuedCompletionStatus(m_CompletionPort, &BytesTransferred, (PULONG_PTR)&PerHandleData, (LPOVERLAPPED*)&IpOverlapped, INFINITE);
			//GetQueuedCompletionStatus 返回值 false
			if (bRet == FALSE)
			{

				if (NULL == IpOverlapped)
					/*	If *lpOverlapped is NULL and the function does not dequeue a completion packet from the completion port,the return value is zero.
						The function does not store information in the variables pointed to by the lpNumberOfBytesTransferred and lpCompletionKey parameters.
						To get extended error information, call GetLastError.If the function did not dequeue a completion packet because the wait timed out, GetLastError returns WAIT_TIMEOUT.
						如果 *lpOverlapped为空并且函数没有从完成端口取出完成包，返回值则为0。
						函数则不会在lpNumberOfBytes and lpCompletionKey所指向的参数中存储信息。
						调用GetLastError可以得到一个扩展错误信息。
						如果函数由于等待超时而未能出列完成包，GetLastError返回WAIT_TIMEOUT.   */
				{
					error = GetLastError();
					LogWrite::WriteLog("iocp has bug at 168,error msg is " + QString::number(error));
					continue;
				}
				//IpOverlapped != NULL
				if (PerHandleData == NULL)
				{
					continue;
				}
				else
				{
					/*  If *lpOverlapped is not NULL and the function dequeues a completion packet for a failed I / O operation from the completion port, the return value is zero.
						The function stores information in the variables pointed to by lpNumberOfBytesTransferred, lpCompletionKey, and lpOverlapped.
						To get extended error information, call GetLastError
						如果 *lpOverlapped不为空并且函数从完成端口出列一个失败I / O操作的完成包，返回值为0。
						函数在指向lpNumberOfBytesTransferred, lpCompletionKey, and lpOverlapped的参数指针中存储相关信息。
						调用GetLastError可以得到扩展错误信息 。
						If a socket handle associated with a completion port is closed, GetQueuedCompletionStatus returns ERROR_SUCCESS, with lpNumberOfBytes equal zero.
						如果关联到一个完成端口的一个socket句柄被关闭了，则GetQueuedCompletionStatus返回ERROR_SUCCESS（也是0）, 并且lpNumberOfBytes等于0  */

						//释放掉资源（服务器主动断开触发）
					if (NULL != pIOCP)
					{
						LogWrite::WriteLog(QString::fromLocal8Bit("服务器断开连接:") + PerHandleData->IP);
						emit pIOCP->OffLineSignal(PerHandleData->Socket);
						pIOCP->ReleaseSocket(PerHandleData);
						GlobalFree(PerIoData);
					
					//	delete PerHandleData;
					//	PerHandleData = NULL;
					}
					continue;
				}

			}
			//GetQueuedCompletionStatus 返回值 true
			else
			{
				//这个宏的作用是：根据一个结构体实例中的成员的地址，取到整个结构体实例的地址
				//PER_IO_DATA的成员overlapped的地址为&IpOverlapped，结果就可以获得PER_IO_DATA的地址
				PerIoData = (LPPER_IO_DATA)CONTAINING_RECORD(IpOverlapped, PER_IO_DATA, overlapped);
				if (NULL == PerIoData)
					//关闭了服务器监听，直接退出IOCP子线程
				{
					LogWrite::WriteLog(QString::fromLocal8Bit("服务器关闭连接"));
					break;
				}

				// 检查在套接字上是否有错误发生
				if (0 == BytesTransferred && RECV != PerIoData->operationType)
				{
					//释放掉资源（设备主动断开连接触发）
					if (NULL != pIOCP)
					{
						LogWrite::WriteLog(QString::fromLocal8Bit("设备断开连接:") + PerHandleData->IP);
						emit pIOCP->OffLineSignal(PerHandleData->Socket);
						shutdown(PerHandleData->Socket, 2);
						closesocket(PerHandleData->Socket);
						pIOCP->ReleaseSocket(PerHandleData);
						GlobalFree(PerIoData);
					}
					continue;
				}
				else
				{
					/*	If the function dequeues a completion packet for a successful I / O operation from the completion port, the return value is nonzero.
						The function stores information in the variables pointed to by the lpNumberOfBytesTransferred, lpCompletionKey, and lpOverlapped parameters.
						如果函数从完成端口取出一个成功I / O操作的完成包，返回值为非0。
						函数在指向lpNumberOfBytesTransferred, lpCompletionKey, and lpOverlapped的参数中存储相关信息。*/

						//线程处理函数，处理设备发送数据
					pIOCP->DoRecvData(PerIoData, BytesTransferred, PerHandleData);
				}
			}
			//为下一个重叠调用建立IO操作
			ZeroMemory(&(PerIoData->overlapped), sizeof(OVERLAPPED));
			memset(PerIoData->buffer, 0, 4 * 1024);
			PerIoData->databuff.len = 4 * 1024;
			PerIoData->databuff.buf = PerIoData->buffer;
			PerIoData->operationType = 0;
			WSARecv(PerHandleData->Socket, &(PerIoData->databuff), 1, &RecvBytes, &Flags, &(PerIoData->overlapped), NULL);
		}

		return 0;
	}
	catch (QString  exception)
	{
		return 0;
	}

}
void IOCP::DoRecvData(LPPER_IO_DATA perIOData, DWORD len, LPPER_HANDLE_DATA PerHandleData)
{
	try
	{
		//接收封装统一的Json
		QJsonObject JsonObj;
		//单次接收的数据，分为字节或者字符串处理
		/***********************需改进，收到char数组，可直接处理，不必再转成QString****************/
		QString RecvStr = QString(QLatin1String(perIOData->buffer, len));
		QVariant varnt;
		varnt.setValue(PerHandleData);
		emit ShowTxt(RecvStr, varnt);
		//去除多余符号
		//RecvStr = RecvStr.trimmed();
		PerHandleData->Frame += RecvStr;
		LRESULT pResult = -1;
		//数据内存判断，如果数据内存大于40M说明有错误数据 需要清空内存，否则会造成内存溢
		if (PerHandleData->Frame.length() > 40960)
		{
			PerHandleData->Frame.clear();
			emit ErrorMSGSignal(10305);
			return;
		}
		//接收到数据为HTTP请求，非设备数据
		if (PerHandleData->Frame.toUpper().contains("HTTP"))
		{
			LogWrite::WriteLog(QString::fromLocal8Bit("接收到非设备数据:") + PerHandleData->Frame);
			shutdown(PerHandleData->Socket, 2);
			closesocket(PerHandleData->Socket);
			ReleaseSocket(PerHandleData);
			return;
		}
		///**************************解析动态链接库***********************************
		pResult = func_Char2Json(PerHandleData->Frame, JsonObj);
		//判断接收情况
		switch (pResult)
		{
		//1：解析成功
		case 1:
		{
			//接收到数据个数
			int Count = JsonObj.find("DataLength").value().toInt();
			//遍历JSON中数据
			for (int i = 0; i < Count; i++)
			{
				//解析数据数组
				QJsonObject data_json = JsonObj.find(QString::number(i + 1)).value().toObject();
				//获取数据类型（1为观测数据，2位操作数据，3为心跳数据）
				int DataType = data_json.find("DataType").value().toInt();
				switch (DataType)
				{
				case 1://观测数据
				{
					//JSON转成字符串
					QJsonDocument document;
					document.setObject(data_json);
					QByteArray byteArray = document.toJson(QJsonDocument::Compact);
					LPCSTR dataChar;
					dataChar = byteArray.data();
					QString ServiceID = data_json.find("ServiceTypeID").value().toString();
					//获取区站号
					PerHandleData->StationID = data_json.find("StationID").value().toString();
					//获取设备号
					PerHandleData->DeviceID = data_json.find("DeviceID").value().toString();
					if (ServiceID.toInt() == 18)//植被
					{
						//获取文件处理类型
						int file = data_json.find("FileType").value().toInt();
						//通知EHT,新的数据
						QVariant varnt;
						varnt.setValue(PerHandleData);
						emit NewDataSignal(varnt,file);
						break;
					}
					if (ServiceID.toInt() == 23)//宁夏墒情
					{
						//宁夏墒情，每帧数据需要返回OK命令
						QString Ok = "OK\r\n";
						QByteArray ba = Ok.toLatin1();
						LPCSTR ch = ba.data();
						int len = Ok.length();
						::send(PerHandleData->Socket, ch, len, 0);
					}

					//发送至消息中间件
					if (g_MQProducer_Data->send(dataChar)==0||g_MQProducer_MDB->send(dataChar) == 0)
						emit ErrorMSGSignal(10304);
					//通知EHT,新的数据
					QVariant varnt;
					varnt.setValue(PerHandleData);
					emit NewDataSignal(varnt);
					//数据来源为可用设备
					PerHandleData->Available = true;
					break;
				}
				case 2://操作数据
				{
					//获取终端返回数据
					QVariant varnt;
					varnt.setValue(PerHandleData);
					emit OperationResultSignal(data_json, varnt);
				
					//数据来源为可用设备
					PerHandleData->Available = true;
					break;
				}
				case 3://心跳数据
				{
					//获取区站号
					PerHandleData->StationID = data_json.find("StationID").value().toString();
					//获取设备号
					PerHandleData->DeviceID = data_json.find("DeviceID").value().toString();
					QVariant varnt;
					varnt.setValue(PerHandleData);
					emit NewDataSignal(varnt);
					//数据来源为可用设备
					PerHandleData->Available = true;
					break;
				}
				}
			
			}
			break;
		}
		default://-1：表示未知数据
			break;
		}
	}
	catch (const std::exception&)
	{
		LogWrite::WriteLog("解析数据发生异常错误!");
		return;
	}

}
void IOCP::ReleaseSocket(LPPER_HANDLE_DATA &lpPerhandleData)
{
	//多线程锁，释放Perhandledata资源
	m_timerMutexSocket.lock();
	Sockets.removeOne(lpPerhandleData);
	m_timerMutexSocket.unlock();
	delete lpPerhandleData;
	lpPerhandleData = NULL;
}