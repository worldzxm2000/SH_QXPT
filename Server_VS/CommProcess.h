#pragma once

#include <QObject>
using namespace std;
class CommProcess : public QObject
{
	Q_OBJECT

public:
	CommProcess(QObject *parent);
	~CommProcess();
	//接收Web发送命令
	void WebCommToFacility(string WebComm);
	//接收设备发送值
	void FacilityValueToWeb();
};
