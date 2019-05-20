#include "itemwidget.h"
#include<qDebug>
#include <QEvent>
#include <QCursor>

ItemWidget::ItemWidget(QWidget *parent) :
	QWidget(parent)
{

	labelName = new QLabel(this);
	labelName->setStyleSheet("font:20pt");
	horLayout = new QHBoxLayout(this);
	horLayout->setContentsMargins(150, 2, 2, 2);
	horLayout->addWidget(labelName);
}

ItemWidget::~ItemWidget()
{

}
void ItemWidget::SetClient(FACILITYINFO *client)
{
	m_client = client;
	QString StationID;
	client->StationID.toUpper() == "NULL" ? StationID = client->DeviceID : StationID = client->StationID;
	labelName->setText(StationID);
}

FACILITYINFO* ItemWidget::GetClient()
{
	return m_client;
}

// 鼠标悬停的时候，显示当前用户简要信息
bool ItemWidget::event(QEvent *e) {
	
	if (e->type() == QEvent::ToolTip) {
		QString Name = labelName->text();
		g_toolTip->showMessage(QCursor::pos(), m_client);
	}
	else if (e->type() == QEvent::Leave) {

		QPoint p = QCursor::pos();
		if (g_toolTip->isVisible())
		{
			if (!(p.rx()>g_toolTip->x0&&p.rx()<g_toolTip->x1&&p.ry()>g_toolTip->y0&&p.ry()<g_toolTip->y1))
				g_toolTip->hide();
		}
	}

	return QWidget::event(e);
}

