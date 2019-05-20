#pragma once

#include <QObject>
#include<QListWidget>
#include"Global.h"
#include"Global_Var.h"
class FcltyTableWidget : public QListWidget
{
	Q_OBJECT

public:
	FcltyTableWidget(QWidget *parent);
	~FcltyTableWidget();
	//添加新行
	void AddRow(FACILITYINFO *Client);
	//排序按业务
	void SortbySelected(QString ServiceName);
	//获取当前选择的Socket号
	uint GetSocket();
	////状态发生改变
	//void ItemStatusChanged(FACILITYINFO *client);
private:
	//显示
	QCToolTip *ctoolTip;
	//设备信息集合
	QList<FACILITYINFO> Clients;
	//socket号
	unsigned int m_Socket;
   //设置当前选择的Socket号
	void SetCurrentSelectedSocket(unsigned int Socket);
private slots:
	void on_list_itemClicked(QListWidgetItem* Item);
};
