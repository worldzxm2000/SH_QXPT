#pragma once

#include <QObject>
#include<QTableWidget>
#include<QPushButton>
class SrvTableWidget : public QTableWidget
{
	Q_OBJECT

public:
	SrvTableWidget(QWidget *parent);
	~SrvTableWidget();
public:
	//添加行数据
	void  AddRow(QString header);
 signals:
	bool NoticfyServerRun(int ServerIndex);
	bool NoticfyServerStop(int ServerIndex);
private:
	bool sortby;//表头排序
private slots:
	void On_Run_Btn(bool Checked);
    void record_sortbyclounm(int colum);//表头排序
};
