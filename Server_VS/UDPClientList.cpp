#include "UDPClientList.h"
#include<QMutex>
#include<qDebug>
#define TIMEOUT 14
QMutex time_mutex;//队列互斥锁 
UDPClientList::UDPClientList()
{
	
}

UDPClientList::~UDPClientList()
{
}

//获取对应地址，并将地址从队列移除
SOCKADDR_IN  UDPClientList::GetClient(QString ServiceID,QString StationID,QString DeviceID)
{
	time_mutex.lock();
	SOCKADDR_IN from;
	//通过业务、台站号和设备号查找UDP号
	
	/*for (int i = clients.count()-1; i >=0; i++)
	{
		if (clients[i].GetServiceID() == ServiceID.toInt() && clients[i].GetStationID() == StationID&&clients[i].GetDeviceID() == DeviceID)
		{
			if (clients[i].IsActive())
			{
				from = clients[i].GetUDP_Addr();
				//RemoveItem(clients[i]);
				break;
			}
		}
	}*/
	time_mutex.unlock();
	//qDebug() << "get client number is:" << clients.count();
	return from;
}
//添加UDP链接地址
void UDPClientList::AddClient(UDPClient client)
{
	//QList<UDPClient>::iterator it;
	//clients.insert(it, client);
	////s.append()
	//connect(&client, SIGNAL(remove(UDPClient)),this , SLOT(Pop(UDPClient)));

	//qDebug() << "add client number is:" << clients.count();
}


//超时判断，将超时无反馈的连接移除
/*void UDPClientList::CheckTimeOut()
{
	time_mutex.lock();
	for (int i = clients.count() - 1; i >= 0; i--)
	{
		if (++clients[i].Count > TIMEOUT)
			clients.removeAt(i);
	}

	if (clients.count() == 0)
		timer->stop();
	qDebug() << "time check number is:" << clients.count();
	time_mutex.unlock();
}*/
