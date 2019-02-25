#include "UDPClient.h"
#include<qDebug>
#define TIMEOUT 14*1000


UDPClient::UDPClient(QObject *parent)
	: QObject(parent)
{
	Count = 0;
	m_IsActive = true;
}

UDPClient::~UDPClient()
{
	qDebug() << "udpclient is deleted" ;
}

//设置参数
void UDPClient::SetParams(SOCKADDR_IN UDP_Addr,int ServiceID,QString StationID,QString DeviceID)
{
	m_UDP_Addr = UDP_Addr;
	m_ServiceID = ServiceID;
	m_StationID = StationID;
	m_DeviceID = DeviceID;
	m_TimerId = startTimer(TIMEOUT);
}
//获取业务号
int UDPClient::GetServiceID()
{
	return m_ServiceID;
}
//获取台站号
QString UDPClient::GetStationID()
{
	return m_StationID;
}
//获取设备号
QString UDPClient::GetDeviceID()
{
	return m_DeviceID;
}
//获取UDP
SOCKADDR_IN UDPClient::GetUDP_Addr()
{
	return m_UDP_Addr;
}
//超时判断，将超时无反馈的连接移除
void UDPClient::timerEvent(QTimerEvent *event)
{
	//判断任务是否超时
	if (++Count < TIMEOUT)
		return;
   // 超时响应
	killTimer(m_TimerId);
	m_IsActive = false;
}

bool UDPClient::IsActive()
{
	return m_IsActive;
}