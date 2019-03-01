#ifndef PARAM_H
#define PARAM_H
#define WIN32_LEAN_AND_MEAN
#include<WinSock2.h>
#include<Windows.h>
#include"SimpleProducer.h"
#include"WebCommServer.h"
#include<QDateTime> 
typedef LRESULT(*Char2Json)(QString &buff,QJsonObject &json);//�������ݺ���
typedef int(*GetServiceTypeID_Lib)();//��ȡҵ������
typedef QString(*GetServiceTypeName_Lib)();//��ȡҵ������
typedef int(*GetPort_Lib)();//��ȡ�˿�
typedef QString(*GetVersionNo_Lib)();//��ȡ�汾��
typedef void(*GetControlWidget_Lib)(QString StationID, uint Socket, QWidget* parent);//��ȡ���Դ���
typedef void(*SetTime_Lib)(QString StationID, uint Socket);//��ʱ����
typedef void(*SetCommand_Lib)(uint Socket, int CommandType,QString Params1,QString Params2,QString StationID);//�ն�����
typedef void(*SetValueToControlWidget_Lib)(QStringList ValueList);//����ֵ
extern 	SimpleProducer g_SimpleProducer, g_SimpleProducer_ZDH,g_SimpleProducer_Command;
extern WebCommServer g_WebCommServer ;
const int DataBuffSize = 4 * 1024;
typedef void* HLIB;		//��̬����
typedef struct
{
	OVERLAPPED overlapped;
	WSABUF databuff;//���ν����ֽ�
	char buffer[DataBuffSize]; //�ܽ����ֽ�
	int BufferLen;  //���ν����ֽڴ�С
	int operationType; // ��¼�ص�IO�������� accp��recv
	

}PER_IO_OPERATEION_DATA, *LPPER_IO_OPERATION_DATA, *LPPER_IO_DATA, PER_IO_DATA;

typedef struct
{
	SOCKET Socket;  //�ͻ���socekt
	QString ClientIP;//�ͻ���IP
	int Port;//�ͻ��˶˿�
	int Count;//�����ݽ�����
	QString Frame;//һ֡����
	QString StationID;//̨վ��
	QString DeviceID;//�豸��
}PER_HANDLE_DATA, *LPPER_HANDLE_DATA;

//IOCP�нṹ��
typedef struct
{
	HANDLE CompletionPort;//IO�˿ں�
	HANDLE Parent;//�����ַ
}PARAMS,*LPPARAMS;


//ҵ���б�
enum ServiceID
{
	NW = 01,//ũί
	JTQX = 02,//��ͨ����
	NTXQH = 03,//ũ��С����
	TRSF = 04,//����ˮ��
	HKQX = 05,//��������
	SH_NTXQH = 8,//ʪ��ũ��С����
	TRSF_NM = 9,//����ˮ������
	TRSF_XJ=10,//����ˮ���½�
	SH_NTXQH_SZ = 11,//ʪ��ũ��С����ˮ��
	SH_DQFY = 12,//ʪ�ش�����������
	SH_TRSF_QY = 13,//�ǵ�������ˮ������
	SH_TRSF_SQ=14,//ʪ������ˮ������
	SH_TRSF_SW=15//ʪ������ˮ�ֵ���ˮ
};

//���󷵻�ֵ
enum ErrorMSG
{
	SOCKET_INIT_ERROR=10300,//SOCKET��ʼ��ʧ��
	IOCP_INIT_ERROR=10301,//IOCP����ʧ��
	SOCKET_BIND_ERROR=10302,//SOCKET��ʧ��
	SOCKET_LISTEN_ERROR=10303,//SOCKET����ʧ��
	MQ_SEND_ERROR=10304//��Ϣ�м����������ʧ��
};

//��վ����Ϣ
typedef struct
{
	//IP��
	QString IP;
	//�˿ں�
	int Port;
	//socket��
	SOCKET SocketID;
	//��վ��
	QString StationID;
	//�豸��
	QString DeviceID;
	//��������ʱ��
	QDateTime LatestTimeOfHeartBeat;
	//״̬
	bool Online;
	//��¼ʱ��
	QDateTime LoginTime;
} CLIENTINFO, *LPCLIENTINFO;

//UDP��Ϣ
typedef struct
{
	SOCKADDR_IN from;//udp socket��
	int ServiceID;//ҵ���
	QString StationID;//̨վ��
	QString DeviceID;//�豸��
	int Count;//������

} UDPClient,*LPUDPClient;
//�ն�����
enum OPCommand
{
	NONE = -1,
	BASEINFO = 231,
	DATETIME = 232,
	ID = 201,
	LAT = 234,
	LONGITUDE = 235,
	ALT = 236,
	CFSET = 237,
	CAPTIME = 238,
	CAPINTERVAL = 239,
	SNAPSHOT = 2310,
	RESET = 2311,
	UPDATE = 2312,
	DMTD=2313
};

//�ϴ��ļ�����
enum FileType
{
	IMAGE = 1,
	TXT=2,
	XML=3
};
#endif // PARAM_H