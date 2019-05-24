#include "FcltyTableWidget.h"
#include<QPixmap>
#include "itemwidget.h"
#include"QToolTip.h"
#include<QMimeData>
#include"MainWnd.h"
QCToolTip *g_toolTip;
FcltyTableWidget::FcltyTableWidget(QWidget *parent)
	:QListWidget(parent)
{
	setFocusPolicy(Qt::NoFocus);

	ctoolTip = new QCToolTip();
	// 定义全局的ToolTip，方便使用
	g_toolTip = ctoolTip;
	connect(this, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(on_list_itemClicked(QListWidgetItem *)));
	connect(this, SIGNAL(itemClicked(QListWidgetItem *)), this->parent()->parent()->parent()->parent(), SLOT(on_list_itemClicked(QListWidgetItem *)));
}

FcltyTableWidget::~FcltyTableWidget()
{
}

//添加新行
void FcltyTableWidget::AddRow(FACILITYINFO *Item)
{
	//判断是否已存在
	for (int i = 0; i < this->count(); i++)
	{
		QListWidgetItem *item = this->item(i);
		QVariant variant = item->data(Qt::UserRole);
		FACILITYINFO *ftInfo = variant.value<FACILITYINFO*>();
		//已经存在该设备
		if (ftInfo->FUID == Item->FUID)
			return;
	/*	item->setData(Qt::UserRole, QVariant::fromValue(Client));
		ItemWidget *itemWidget = new ItemWidget(this);
		itemWidget->SetClient(Client);
		this->setItemWidget(item, itemWidget);*/
	}
	//未存在则添加
	//第一列
	ItemWidget *itemWidget = new ItemWidget(this);
	itemWidget->SetClient(Item);
	//this,不需要insertItem；不传入this,则需要添加insertItem
	QListWidgetItem *listItem = new QListWidgetItem(this);
	// 此处的size如果不设置，界面被压缩了看不出ItemWidget的效果，高度一定要设置
	listItem->setSizeHint(QSize(100, 40));
	listItem->setData(Qt::UserRole,QVariant::fromValue(Item));
	listItem->setText(Item->ServiceName);
	this->setItemWidget(listItem, itemWidget);
}

//业务列表点击时，所选业务的设备排最前
void FcltyTableWidget::SortbySelected(QString ServiceName)
{
	//将第一个满足业条件的item插入到第一行，删除item
	//查找所有逇item

	//找到item，然后takeitem，最后再insertitem到第一行，设置widget。
	for (int i = 0; i <this->count(); i++)
	{
		QListWidgetItem *item = this->item(i);
		QVariant variant = item->data(Qt::UserRole);
		FACILITYINFO* ftInfo = variant.value<FACILITYINFO*>();
		QString DataName = item->text();
		//查找业务下的设备
		if (DataName == ServiceName)
		{			
			ItemWidget *itemWidget = new ItemWidget(this);
			itemWidget->SetClient(ftInfo);
			this->takeItem(i);
			this->insertItem(0,item);
			this->setItemWidget(item, itemWidget);
		}
	}
}

//单击列表获取Item
void FcltyTableWidget::on_list_itemClicked(QListWidgetItem* Item)
{
	if (Item == nullptr)
		return;
	//查找Item中的data
	QVariant variant = Item->data(Qt::UserRole);
	FACILITYINFO *ftInfo = variant.value<FACILITYINFO*>();
	//找到Socket号
	SetCurrentSelectedSocket(ftInfo->Socket);
}

//设置Socket
void FcltyTableWidget::SetCurrentSelectedSocket(unsigned int Socket)
{
	m_Socket = Socket;
}

//获取Socket
unsigned int FcltyTableWidget::GetSocket()
{
	return m_Socket;	
}

////状态发生改变
//void FcltyTableWidget:: ItemStatusChanged(FACILITYINFO *client)
//{
//	for (int i = 0; i < this->count(); i++)
//	{
//		    QListWidgetItem *item = this->item(i);
//			QVariant variant = item->data(Qt::UserRole);
//			FACILITYINFO ftInfo = variant.value<FACILITYINFO>();
//			if (ftInfo.UID != client->UID)
//				continue;
//			ItemWidget *itemWidget = new ItemWidget(this);
//			itemWidget->SetClient(client);
//			this->setItemWidget(item, itemWidget);
//	}
//}