#include "EHTPool.h"
#include<QMessageBox>
EHTPool::EHTPool(QObject *parent)
	: QObject(parent)
{
	ThreadPool.setMaxThreadCount(1024);
}
EHTPool::EHTPool()
{
	ThreadPool.setMaxThreadCount(1024);
}
EHTPool::~EHTPool()
{
	StopAll();
}

bool EHTPool::Start(EHT* pEHT)
{
	for (int i = 0; i < EHTList.count(); i++)
	{
		if (EHTList.at(i)->GetServiceName() == pEHT->GetServiceName())
		{
			delete pEHT;
			pEHT = nullptr;
			QMessageBox::warning(nullptr, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("已存在该业务解析库"));
			return false;
		}
	}
	pEHT->Run(ThreadPool);
	EHTList.append(pEHT);
	return true;
}

void EHTPool::Stop(QString ServiceName)
{
	for (int i = EHTList.count() - 1; i > -1; i--)
	{
		if (EHTList.at(i)->GetServiceName() == ServiceName)
		{
			EHTList[i]->Stop();
			delete EHTList[i];
			EHTList[i] = nullptr;
			EHTList.removeAt(i);
		}
	}
}

void EHTPool::StopAll()
{
	for (int i = EHTList.count() - 1; i > -1; i--)
	{
		EHTList[i]->Stop();
		delete EHTList[i];
		EHTList[i] = nullptr;
		EHTList.removeAt(i);

	}
}

bool EHTPool::Pause(QString ServiceName)
{
	QList<EHT*>::iterator iter = EHTList.begin();
	while (iter != EHTList.end())
	{
		if ((*iter)->GetServiceName() == ServiceName)
		{
			return (*iter)->Stop();
		}
		iter++;
	}
	return false;
}

bool EHTPool::Run(QString KeyName)
{
	QList<EHT*>::iterator iter = EHTList.begin();
	while (iter != EHTList.end())
	{
		if ((*iter)->GetServiceName() == KeyName)
		{
			return (*iter)->Run(ThreadPool);
		}
		iter++;
	}
	return false;
}

EHT* EHTPool::GetEHT(QString ServiceName)
{

	for (QList<EHT*>::iterator iter = EHTList.begin(); iter != EHTList.end(); ++iter)
	{
		if ((*iter)->GetServiceName() == ServiceName)
		{
			return (*iter);
		}
	}
	return NULL;
}

EHT* EHTPool::GetEHT(int FUID)
{
	for (QList<EHT*>::iterator iter = EHTList.begin(); iter != EHTList.end(); ++iter)
	{
		if ((*iter)->GetFID(FUID))
		{
			return (*iter);
		}
	}
	return NULL;
}
