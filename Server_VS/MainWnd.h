#ifndef MAINWND_H
#define MAINWND_H
#if _MSC_VER >= 1600  
#pragma execution_character_set("utf-8")  
#endif 
#include <QtWidgets/QMainWindow>
#include "ui_MainWnd.h"
#include<QMessageBox>
#include<QThreadPool>
#include"LogWrite.h"
#include<QJsonObject>
#include"EHTPool.h"
#include<QLibrary>
#include <QTimer>
#include<QMenu>
#include <QMouseEvent>
#include<QListView>
#include<QStringListModel>
#include<assert.h>
#include"Global.h"
#include"Global_Var.h"

class MainWnd : public QMainWindow
{
	Q_OBJECT

public:
	MainWnd(QWidget *parent = 0);
	~MainWnd();
private:
	Ui::Server_VSClass ui;
	//状态值
	QString strStatus;
	//业务管理
	EHTPool EHTPool;
	//业务列表右键菜单
	QMenu pop_Menu_Service;
	//属性
	QAction action_Attributes;
	//打开备份文档
	QAction action_TxtFile;
	//SQL数据队列
	MQProducer *g_MQProducer_Data;
	//MangoBD数据队列
	MQProducer *g_MQProducer_MDB;
	//WebSrv响应队列
	MQProducer *g_MQProducer_WebSrv;
	//WebSrv请求队列
	WebCommServer *g_WebCommServer;
	//判断鼠标左键是否按下
	bool m_Drag;
	//鼠标移动坐标点
	QPoint m_DragPosition;
	//业务ListCtrl选中行
	int iSelectedRowOfServiceListCtrl;
	/*
	* @brief 设置状态栏状态
	* @param Status 参数1 系统运行状态
	* @return 返回说明
	无
	*/
	void SetStatusLabel(QString Status);
	/*
	* @brief 读取MQ配置文件
	* @param 无
	* @return 返回说明
	无
	*/
	void LoadMQConfigFile();
	/*
	* @brief 添加解析类库
	* @param 无
	* @return 返回说明
	1：成功加载解析库
	0：取消加载解析库
	-1: 非业务解析库；
	-2: 业务监听端口被占用
	* @Other 通过手动选择加载解析类库
	*/
	LRESULT AddDLL();
	/*
	* @brief 添加解析类库
	* @param Path 参数1 库类路径
	* @param IP 参数2 监听IP
	* @param Port 参数3 监听端口
	* @return 返回说明
	1：成功加载解析库
	0：取消加载解析库
	-1: 非业务解析库；
	-2: 业务监听端口被占用
	* @Other 读取配置文件加载解析库类
	*/
	LRESULT AddDLL(QString Path, QString IP,int Port);
	/*
	* @brief 读取解析库类配置文件
	* @param 无
	* @return 返回说明
	无
	*/
	void IniDLL();
	/*
	* @brief 业务列表右键菜单
	* @param 无
	* @return 返回说明
	无
	*/
	void CreateServerListActions();
	/*
	* @brief 初始化消息中间件
	* @param 无
	* @return 返回说明
	true：已连接消息中间件
	false：连接消息中间件失败
	*/
	bool InitMQ();
	//窗体移动
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
private slots:
	/*
	* @brief 最小化窗体
	* @param 无
	* @return 返回说明
	true：已连接消息中间件
	false：连接消息中间件失败
	*/
    void slot_minWindow();
	/*
	* @brief 刷新设备ListCtrl控件信息
	* @param Var 参数1 设备信息结构体
	* @return 返回说明
      无
	*/
	void RefreshListCtrl(QVariant Var);
	//错误提示
	void GetErrorMSG(int error);
	/*
	* @brief 添加解析库Button_clicked
	* @param 无
	* @return 返回说明
	无
	*/
	void on_AddBtn_clicked();
	/*
	* @brief 移除解析库Button_clicked
	* @param 无
	* @return 返回说明
	无
	*/
	void on_RemoveBtn_clicked();
	/*
	* @brief  查看日志Button_clicked
	* @param 无
	* @return 返回说明
	无
	*/
	void on_LogBtn_clicked();
	/*
	* @brief  参数设置Button_clicked
	* @param 无
	* @return 返回说明
	无
	*/
	void on_SettingBtn_clicked();
	/*
	* @brief 发送TxtButton_clicked
	* @param 无
	* @return 返回说明
	无
	*/
	void on_SndTxtBtn_clicked();
	/*
	* @brief 清空接收TXT显示Button_clicked
	* @param 无
	* @return 返回说明
	无
	*/
	void on_ClearTxtBtn_clicked();
	/*
	* @brief 业务列表右键事件
	* @param 无
	* @return 返回说明
	无
	*/
	void on_ServerList_customContextMenuRequested(const QPoint &pos);
	/*
	* @brief 启动监听业务数据
	* @param RowIndex 参数1 业务选择行号
	* @return 返回说明
	true：启动成功
	false：启动失败
	*/
	bool Lib_Run(int RowIndex);
	/*
	* @brief 停止监听业务数据
	* @param RowIndex 参数1 业务选择行号
	* @return 返回说明
	true：停止成功
	false：停止失败
	*/
	bool Lib_Stop(int RowIndex);
	/*
	* @brief 右键查看业务属性
	* @param 无
	* @return 返回说明
	*/
	void Lib_Attri();
	/*
	* @brief 右键打开备份文件
	* @param 无
	* @return 返回说明
	*/
	void OpenTxtFile();
	/*
	* @brief 业务列表单击点击
	* @param Row 参数1 行号
	* @param Column 参数1 列号
	* @return 返回说明
	*/
	void on_ServerList_cellClicked(int Row, int Column);
	/*
	* @brief 获取在线设备个数
	* @param SelectedRowOfServiceListCtrl 参数1 业务列表当前选择行号
	* @return 返回说明
	无
	* @Other 单击业务列表中业务，显示该业务的在线设备，并且使其下设备信息在设备列表置顶
	*/
	void GetServiceInfo(int SelectedRowOfServiceListCtrl);
	/*
	* @brief 业务列表LIST发生改变
	* @param currentRow 参数1 业务列表当前选择行号
	* @param currentColumn 参数2 业务列表当前选择行号
	* @param previousRow 参数3 业务列表上个选择行号
	* @param previousColumn 参数4 业务列表上个选择行号
	* @return 返回说明
	无
	* @Other 业务列表LIST发生改变，显示该业务的在线设备
	*/
	void on_ServerList_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);
	/*
	* @brief 新连接通知
	* @param Status 参数1 连接信息
	* @return 返回说明
	无
	*/
	void NewConnectionSlot(QString Status);
	/*
	* @brief 更新系统运行状态
	* @param Status 参数1 系统运行状态
	* @return 返回说明
	无
	*/
	void RefreshStatus(QString Status);
	///*
	//* @brief 显示接收Txt开关
	//* @param checked 参数1 Check状态
	//* @return 返回说明
	//无
	//* @Other 开启或者关闭接收Txt显示，开启或关闭信号槽
	//*/
	//void on_ShowTxtSwitchBtn_clicked(bool checked);
	/*
	* @brief 选中设备列表某项
	* @param Item 参数1 Check状态
	* @return 返回说明
	无
	*/
	void on_list_itemClicked(QListWidgetItem* Item);

public slots:
	/*
	* @brief Txt在UI显示
	* @param Txt 参数1 数据txt信息
	* @param PerHandleData 参数2 连接信息
	* @return 返回说明
	无
	*/
	void ShowTxtToUI(QString Txt, QVariant PerHandleData);
	/*
	* @brief 关闭窗体,记录日志
	* @return 返回说明
	无
	*/
	void close();
};

#endif // MAINWND_H
