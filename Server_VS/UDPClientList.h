#pragma once

#include <QObject>
#include<QList>
#include<QTimer>
#include"UDPClient.h"
class UDPClientList : public QObject
{
	Q_OBJECT

public:
	UDPClientList();
	~UDPClientList();
	SOCKADDR_IN GetClient(QString ServiceID, QString StationID, QString DeviceID);
	void AddClient(UDPClient client);
	//void SetThread(QThread *parent);
protected:
	QList<UDPClient> clients;


};
