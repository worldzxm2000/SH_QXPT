#ifndef GLOBAL_H
#define GLOBAL_H
#define WIN32_LEAN_AND_MEAN
#include<WinSock2.h>
#include<Windows.h>
//#include"MQProducer.h"
//#include"WebCommServer.h"
//#include"CToolTip.h"
#include<QDateTime> 
typedef LRESULT(*Char2Json)(QString &buff,QJsonObject &json);//�������ݺ���
typedef int(*GetServiceTypeID_Lib)();//��ȡҵ������
typedef QString(*GetServiceTypeName_Lib)();//��ȡҵ������
typedef int(*GetPort_Lib)();//��ȡ�˿�
typedef QString(*GetVersionNo_Lib)();//��ȡ�汾��
typedef void(*GetControlWidget_Lib)(QString StationID, uint Socket, QWidget* parent);//��ȡ���Դ���
typedef void(*SetTime_Lib)(QString StationID, uint Socket);//��ʱ����
typedef void(*SetCommand_Lib)(uint Socket, int CommandType,QStringList CommList);//�ն�����
typedef void(*SetValueToControlWidget_Lib)(QStringList ValueList);//����ֵ
typedef void(*GetFacilityInfo)(uint Socket);//��ȡ̨վ��Ϣ
typedef void(*CloseControlWindow)();//�رտ��ƴ���
//extern 	MQProducer g_MQProducer_Data-> g_MQProducer_MDB->g_MQProducer_WebSrv->
//extern WebCommServer g_WebCommServer->;
//extern CToolTip *g_toolTip;
const int DataBuffSize = 4 * 1024;
typedef void* HLIB;		//��̬����
/**
* �ṹ�����ƣ�PER_IO_DATA
* �ṹ�幦�ܣ��ص�I/O��Ҫ�õ��Ľṹ�壬��ʱ��¼IO����
**/
typedef struct
{
	OVERLAPPED overlapped;
	WSABUF databuff;//���ν����ֽ�
	char buffer[DataBuffSize]; //�ܽ����ֽ�
	int BufferLen;  //���ν����ֽڴ�С
	int operationType; // ��¼�ص�IO�������� accp��recv
	

} *LPPER_IO_DATA, PER_IO_DATA;

/**
* �ṹ�����ƣ�PER_HANDLE_DATA
* �ṹ��洢����¼�����׽��ֵ����ݣ��������׽��ֵı������׽��ֵĶ�Ӧ�Ŀͻ��˵ĵ�ַ��
* �ṹ�����ã��������������Ͽͻ���ʱ����Ϣ�洢���ýṹ���У�֪���ͻ��˵ĵ�ַ�Ա��ڻطá�
**/
typedef struct
{
	int FUID;//�豸UID
	SOCKET Socket;  //�ͻ���socekt
	QString IP;//�ͻ���IP
	int Port;//�ͻ��˶˿�
	QString Frame;//һ֡����
	QString StationID;//̨վ��
	QString DeviceID;//�豸��
	int Timer;//��ʱʱ�ӱ�ʶ
	bool Available;//�豸Ϊ����
}PER_HANDLE_DATA , *LPPER_HANDLE_DATA;

Q_DECLARE_METATYPE(LPPER_HANDLE_DATA)
Q_DECLARE_METATYPE(PER_HANDLE_DATA)
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
	SH_TRSF_SW=15,//ʪ������ˮ�ֵ���ˮ
	SN=19,//��ũ
	NXSQ=23//��������
};

//̨վ����Ϣ
//����Ψһ��UID
 struct FACILITYINFO:QObjectUserData
{
	 //�豸UID
	 int FUID;
	//ҵ������
	QString ServiceName;
	//IP��
	QString IP;
	//�˿ں�
	int Port;
	//socket��
	SOCKET Socket;
	//��վ��
	QString StationID;
	//�豸��
	QString DeviceID;
	//���¸���ʱ��
	QDateTime LatestTimeOfHeartBeat;
	//״̬
	bool Online;
	//��¼ʱ��
	QDateTime LoginTime;
};
Q_DECLARE_METATYPE(FACILITYINFO*)
Q_DECLARE_METATYPE(FACILITYINFO)
//WebRequest��Ϣ
typedef struct
{
	QString UID;//�û�ID
	int FUID;//�豸UID
	int Count;//������

} WebSrvClient,*LPWebSrvClient;

//�ϴ��ļ�����
enum FileType
{
	IMAGE = 1,
	TXT=2,
	XML=3
};
#endif // GLOBAL_H
