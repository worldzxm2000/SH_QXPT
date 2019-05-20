#pragma once

#include <QObject>
#include "EHT.h"
class EHTPool : public QObject
{
	Q_OBJECT

public:
	EHTPool(QObject *parent);
    EHTPool();
	~EHTPool();
	/*
	* @brief    创建监听服务
	* @param pEHT 参数1 业务类
	* @return 返回说明
	true：创建成功
	false:创建失败
	*/
	bool Start(EHT *pEHT);
	/*
	* @brief    结束监听服务
	* @param pEHT 参数1 业务类
	* @return 返回说明
	  无
	*/
	void Stop(QString ServiceName);
	/*
	* @brief    结束所有监听
	* @param pEHT 参数1 业务类
	* @return 返回说明
	  无
	*/
	void StopAll();
	/*
	* @brief    暂停监听
	* @param ServiceName 参数1 业务名称
	* @return 返回说明
	true：监听成功
	false:监听失败
	*/
	bool Pause(QString ServiceName);
	/*
	* @brief    开启监听
	* @param ServiceName 参数1 业务名称
	* @return 返回说明
	  true：监听成功
      false:监听失败
	*/
	bool Run(QString ServiceName);
	/*
	* @brief    找到解析业务
	* @param ServiceName 参数1 业务名称
	* @param FUID 参数2 设备UID
	* @return 返回说明
	          EHT* 设备所在的业务类
	* @Other 通过设备UID或者业务名称找到该业务
	*/
	EHT* GetEHT(QString ServiceName);
	EHT* GetEHT(int FUID);
	///*
	//* @brief    关闭TXT显示
	//* @param Socket 参数1 设备Socket号
	//* @param IsConnect 参数2 打开/关闭开关
	//* @return 返回说明
    //	  无
	//* @Other 通过设备Socket找到该业务，关闭其他TXT显示
	//*/
	//void OffShowTxt(uint Socket,bool IsConnect);
private:
	//业务解析类
	QList<EHT *> EHTList;
	//线程池
	QThreadPool ThreadPool;
};
