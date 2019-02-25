#pragma once

#include <QObject>
#include<QTimer>
#include"param.h"

class UDPClient : public QObject
{
	Q_OBJECT

public:
	UDPClient(QObject *parent);
	~UDPClient();
private:
	int m_TimerId;//超时定时器
	SOCKADDR_IN m_UDP_Addr;//UDP地址	
    int Count;//超时计数器
	int m_ServiceID;//业务号
	QString m_StationID;//区站号
	QString m_DeviceID;//设备号
	bool m_IsActive;
	virtual void timerEvent(QTimerEvent *event);
public:
	void SetParams(sockaddr_in udp_addr, int serviceid, QString stationid, QString deviceid);
	int GetServiceID();//获取业务号
	QString GetStationID();//获取台站号
	QString GetDeviceID();//获取设备号
	SOCKADDR_IN GetUDP_Addr();//获取udp地址
    bool IsActive();//获取任务状态
};
