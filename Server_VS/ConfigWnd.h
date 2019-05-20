#pragma once

#include <QDialog>
#include "ui_ConfigWnd.h"
#include <QCloseEvent> 
class ConfigWnd : public QDialog
{
	Q_OBJECT

public:
	ConfigWnd(QWidget *parent = Q_NULLPTR);
	~ConfigWnd();
private:
	Ui::ConfigWnd ui;
	//获取本地IP
	void GetLocalIP();
public:
	//设置端口号
	int m_Port;
	//设置ip号
	QString m_IP;
	//描述
	QString m_Attribute;
	//窗体打开模式
	bool DialogMode;
	/*
	* @brief 设置监听端口
	* @param Lib_Path 参数1 Lib库类地址
	* @param isLoad 参数2 是否为加载过解析库
	true: 第一次加载；
	false: 已加载过；
	* @return 返回说明
	1：成功加载解析库
	0：取消加载解析库
	-1: 非业务解析库；
	-2: 业务监听端口被占用
	*/
	void SetServicePort(int Port);
	int exec();
private slots:
    void on_SetBtn_clicked();
};
