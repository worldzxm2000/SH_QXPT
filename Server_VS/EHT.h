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
	//SQL���ݶ���
	MQProducer *g_MQProducer_Data;
	//MangoBD���ݶ���
	MQProducer *g_MQProducer_MDB;
	//WebSrv��Ӧ����
	MQProducer *g_MQProducer_WebSrv;
	//WebSrv�������
	WebCommServer *g_WebCommServer;
	/*
	* @brief ��ʼ��IOCP�����ò���
	* @return ����˵��
	��
	*/
	void InitIOCP();
	/*
	* @brief ����ҵ�������
	* @param Lib_Path ����1 Lib�����ַ
	* @param isLoad ����2 �Ƿ�Ϊ���ع�������
	true: ��һ�μ��أ�
	false: �Ѽ��ع���
	* @return ����˵��
	1���ɹ����ؽ�����
	0��ȡ�����ؽ�����
	-1: ��ҵ������⣻
	-2: ҵ������˿ڱ�ռ��
	*/
	LRESULT LoadLib(QString Lib_Path, bool isLoad);
	/*
	* @brief ����ҵ�������
	* @param Lib_Path ����1 Lib�����ַ
	* @param IP ����2 ҵ�����IP
	* @param Port ����3 ҵ������˿�
	* @param isLoad ����4 �Ƿ�Ϊ���ع�������
	true: ��һ�μ��أ�
	false: �Ѽ��ع���
	* @return ����˵��
	1���ɹ����ؽ�����
	0��ȡ�����ؽ�����
	-1: ��ҵ������⣻
	-2: ҵ������˿ڱ�ռ��
	*/
	LRESULT LoadLib(QString Lib_Path, QString IP, int Port, bool isLoad);
	/*
	* @brief ж��ҵ��Lib����
	* @return ����˵��
	true: ж�سɹ�
	false��ж��ʧ��
	*/
	bool UnloadLib();
	/*
	* @brief ��ȡҵ��ID
	* @return ����˵��
	value: ҵ��ID
	*/
	int GetServiceID();
	/*
	* @brief ��ȡҵ������
	* @return ����˵��
	value: ҵ������
	*/
	QString GetServiceName();
	/**
	* @brief ��ȡҵ������˿ں�
	* @return ����˵��
	value: ҵ������˿ں�
	*/
	int GetPort();
	/**
	* @brief ͨ���豸UID�����豸Socket��
	* @param UID    ����1 �豸UID��
	* @return ����˵��
	0 : δ�ҵ�Socket�Ż��߸��豸�Ѿ�����
	value: ���豸��Socket��
	*/
	u_int FindSocket(QString UID,bool &IsExist);
	/**
	* @brief ҵ������
	* @return ����˵��
	value: ҵ������˵��
	*/
	QString GetAttribute();
	/*
	* @brief ��ȡ���ݽ���
	* @return ����˵��
	value: Lib�����������ݽ�������
	*/
	Char2Json GetDataFunc();
	/*
	* @brief �����������ݷ�������IOCP�࣬��ӵ�ThreadPool������
	* @param ThreadPool    ����1 �̳߳�
	* @return ����˵��
	true: �����ɹ�
	false������ʧ��
	*/
	bool Run(QThreadPool &ThreadPool);
	/*
	* @brief �����������ݷ���ж��Lib�⣬�ر�IOCP
	* @return ����˵��
	true: �رճɹ�
	false���ر�ʧ��
	*/
	bool Stop();
	/*
	* @brief ��������״̬
	* @return ����˵��
	true:���ڼ���
	false��ֹͣ����
	*/
	bool IsRun();
	/*
	* @brief  ��ȡ�����豸����
	* @param event ����1 ��װ����Э��Json
	* @return ����˵��
	��
	* @Other ÿһ����м�����������������10ʱ��Time Out��
	*/
	int  OnLineCount();
	/*
	* @brief  �ҵ���ҵ�����Ƿ����豸UID
	* @param FUID ����1 �豸UID
	* @return ����˵��
	true����ҵ���и��豸
	false����ҵ�񲻺������豸
	*/
	bool GetFID(int FUID);
	///*
	//* @brief    �ر�TXT��ʾ
	//* @param Socket ����1 �豸Socket��
	//* @param IsConnect ����2 ��/�رտ���
	//* @return ����˵��
	//  ��
	//* @Other ͨ���豸Socket�ҵ���ҵ�񣬹ر�����TXT��ʾ��δ���
	//*/
	//void OffShowTxt(uint Socket,bool IsConnect);
private:
	//��ȡ���ӿͻ�������
	QList<FACILITYINFO*> Clients;
	//ֲ�����´���ʱ��
	QTimer *ReHandleZB_IMAGE;
	QTimer *ReHandleZB_XML;
	QTimer *ReHandleZB_TXT;
	//�Ƿ����JPG�ļ�
	bool IsExistImage;
	//�Ƿ����TXT
	bool IsExistTXT;
	//������ʱ����ʶ
	int m_TimeOutTimerID;
	//IOCP����״̬
	bool m_IsRun;
	//IOCP�����߳�
	IOCP *pIOCP;
	//Lib������
	QLibrary m_Lib;
	//�������IP��
	QString m_IP;
	//��������˿ں�
	int m_Port;
	//ҵ������
	int m_ServiceID;
	//ҵ������
	QString m_ServiceName;
	//����
	QString m_Attribute;
	//���ݽ���
	Char2Json m_DataFunc;
	//SIM���Ŷ�Ӧ��վ��
	QMap<QString, QString> SIM2Staion;
	//�Զ���ʱʱ��
	QTimer *SetTimeTimer;
	//���߼��ʱ��
	QTimer *OffLineTimer;
	//��ʱ����
	SetTime_Lib func_SetTime_Lib;
	//��ʾ����ֵ
	SetValueToControlWidget_Lib func_SetValueToControlWidget;
	//�ն�����
	SetCommand_Lib func_SetCommand;
	//·��
	QString m_LibPath;
	//Web�������ӳ�
	QList<WebSrvClient> ClientsQ;
	/*
	* @brief �ж϶˿ںϷ���
	@param Port    ����1 �˿ں�
	* @return ����˵��
	true:�˿���ռ��
	false���˿��ѱ�ռ��
	*/
	bool IsLegallyPort(int Port);
	/*
	* @brief  ��ȡSIM���������ļ���ת����վ�ţ�ũί��
	* @param ��
	* @return ����˵��
	��
	*/
	void Convert2StationID();
	/*
	* @brief   WebSrv����ʱ���
	* @param event ����1 ��ʱ��ID��Ϣ
	* @return ����˵��
	��
	* @Other ÿһ����м�����������������10ʱ��Timeout��
	*/
	virtual void timerEvent(QTimerEvent *event);
	/*
	* @brief    �������Ӧ��Web����
	* @param Json ����1 ��װ����Э��Json
	* @param FUID ����2 ��Ӧ�豸UID��
	* @return ����˵��
	��
	* @Other ͨ���豸UID�ҵ�������Ӧ��UID������MQ��
	*/
	void ResponseTo(QJsonObject json, int FUID);
	/*
	* @brief    ͨ��ҵ�����ơ�̨վ�ź��豸�Ŵ����豸UID
	* @param ServiceName ����1 ҵ������
	* @param StationID ����2 ̨վ��
	* @param DeviceID ����3 �豸��
	* @return ����˵��
	value:�豸UID��
	* @Other ͨ���豸FUID�ҵ�������Ӧ��UID������MQ��
	*/
	int  CreateUID(QString ServiceName, QString StationID, QString DeviceID);

private slots:
	/*
	* @brief    �Զ��������
	* @param PerHandleData ��
	* @return ����˵��
	��
	*/
	void OfflineCheck();
	/*
	* @brief  ����ʱ��
	* @param ��
	* @return ����˵��
	��
	*/
	void SetTime();
	/*
	* @brief    ���µ����Ӽ���
	* @param IP    ����1     ������IP��ַ
	* @param Port  ����2     �����Ӷ˿ں�
	* @param m_Port  ����3   �����������˿ں�
	* @param Socket  ����4   Socket��
	* @return ����˵��
	��
	*/
	void NewConnectionSlot(QString IP, int Port, int m_Port, uint Socket);
	/*
	* @brief    �豸����֪ͨ
	* @param Socket  ����1   Socket��
	* @return ����˵��
	��
	*/
	void OffLineSlot(unsigned int CltSocket);
	/*
	* @brief    �豸�ϴ�����
	* @param PerHandleData  ����1   ���ӵ����ݽṹ��
	* @return ����˵��
	��
	* @Other �豸��һ�����Ӵ����豸UID��ͨ��UID�����豸�ڴ棻�豸��������ʾ�������豸�����߶�ʱ
	*/
	void NewDataSlot(QVariant var);
	/*
	* @brief    �豸�ϴ����ݣ�ʪ��ֲ����
	* @param PerHandleData  ����1   ���ӵ����ݽṹ��
	* @param File ����2  ֲ����������
	* @return ����˵��
	��
	* @Other �豸��һ�����Ӵ����豸UID��ͨ��UID�����豸�ڴ棻�豸��������ʾ�������豸�����߶�ʱ
	*/
	void NewDataSlot(QVariant Var, int File);
	/*
	* @brief  ��ȡ����
	* @param ErrorMSG ����1 �������
	* @return ����˵��
	��
	*/
	void GetErrorSlot(int ErrorMSG);
	/*
	* @brief �豸����ؽ������
	* @param Json ����1 �豸���ؽ��Json
	* @paran Var ����2 �豸������Ϣ
	* @return ����˵��
	��
	@Other �豸���ؽ����
	*/
	void OperationResultSlot(QJsonObject json, QVariant Var);
	/*
	* @brief    �豸�ϴ����ݣ�ʪ��ֲ����ͼƬ����
	* @param PerHandleData ��
	* @return ����˵��
	��
	* @Other ���յ�ͼƬ�����������FTPָ������Ѱ��ͼƬ������󿽱���ָ������λ��
	*/
	void MoveImageToDesAddr();
	/*
	* @brief    �豸�ϴ����ݣ�ʪ��ֲ�����ı�����
	* @param PerHandleData ��
	* @return ����˵��
	��
	* @Other ���յ��ı������������FTPָ������Ѱ���ı�������󿽱���ָ������λ��
	*/
	void MoveTXTToDesAddr();
	/*
	* @brief    �豸�ϴ����ݣ�ʪ��ֲ����XML����
	* @param PerHandleData ��
	* @return ����˵��
	��
	* @Other ���յ�XML�����������FTPָ������Ѱ���ı�������󿽱���ָ������λ��
	*/
	void MoveXMLToDesAddr();
	/*
	* @brief   ��ȡ�豸����ָ��
	* @param UID ����1 WebSrv����UID
	* @param FUID ����2 ̨վUID
	* @param Command ����3 �����
	* @param CommLst ����4 ������
	* @return ����˵��
	��
	* @Other ͨ���豸FUID�ҵ�������Ӧ��UID������MQ��
	*/
	void RequestFor(QString UID, int FUID, int Command, QStringList CommLst);

signals:
	/*
	* @brief   ������֪ͨ
	* @param Status ����1 ������֪ͨ
	* @return ����˵��
	��
	*/
	void NewConnectionSignal(QString Status);
	/*
	* @brief  �豸����������Ϣ
	* @param Var ����1 �豸������Ϣ
	* @return ����˵��
	��
	*/
	void OnLineSignal(QVariant Var);
	/*
	* @brief  ������ʾ״̬��Ϣ
	* @param Result ����1 ״̬��Ϣ
	* @return ����˵��
	��
	*/
	void RefreshStatus(QString Status);
};
