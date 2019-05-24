#include "QCToolTip.h"
#include "ui_QCToolTip.h"
#include <QApplication>
#include <QDesktopWidget>
QCToolTip::QCToolTip(QWidget *parent) :
	QWidget(parent)
{
	ui = new Ui::QCToolTip();
	ui->setupUi(this);
	this->setWindowFlags(Qt::Tool | Qt::WindowStaysOnTopHint | Qt::X11BypassWindowManagerHint|Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);

}

QCToolTip::~QCToolTip()
{
	delete ui;
}

// 显示ToolTip消息
void QCToolTip::showMessage(QPoint point, FACILITYINFO *client) {

	ui->ServerNameLabel->setText(geteElidedText(ui->ServerNameLabel->font(), client->ServiceName, 60));
	ui->StationLabel->setText(geteElidedText(ui->StationLabel->font(),client->StationID,60));
	ui->DeviceLabel->setText(client->DeviceID);
	client->Online == true ? ui->OnlineLabel->setText(QString::fromLocal8Bit("在线")) : ui->OnlineLabel->setText(QString::fromLocal8Bit("离线"));
	ui->IPLabel->setText(client->IP);
	ui->PortLabel->setText(QString::number(client->Port));
	ui->LoginTimeLabel->setText(client->LoginTime.toString("yyyy-MM-dd hh:mm:ss"));
	ui->LastDataTimeLabel->setText(client->LatestTimeOfHeartBeat.toString("yyyy-MM-dd hh:mm:ss"));
	// QWidget::hide();
	// 重新定义QCToolTip的坐标
	int rectX;
	int rectY;
	if (point.rx() < 200) {
		rectX = point.rx() + 10;
	}
	else {
		rectX = point.rx() - 160;
	}
	rectY = point.ry();
	move(QPoint(rectX, rectY));
	x0 = this->x();
	y0 = this->y();
	x1 = x0 + this->width() + 10;
	y1 = y0 + this->height() + 10;
	y0 -= 100;
	QWidget::show();
	WindowVisable = true;
}

QString QCToolTip::geteElidedText(QFont font, QString str, int MaxWidth)
{
	QFontMetrics fontWidth(font);
	int width = fontWidth.width(str);  //计算字符串宽度
	if (width >= MaxWidth)  //当字符串宽度大于最大宽度时进行转换
	{
		str = fontWidth.elidedText(str, Qt::ElideRight, MaxWidth);  //右部显示省略号
	}
	return str;   //返回处理后的字符串
}

//tooltip进入隐藏
void QCToolTip::hide()
{
	if (WindowVisable)
	{
		QWidget::hide();
		WindowVisable = false;
	}
}

// 鼠标悬停的时候，显示当前用户简要信息
bool QCToolTip::event(QEvent *e) {
	if (e->type() == QEvent::Enter)
	{
		MouseEnter = true;
		WindowVisable = true;
	}
	if (e->type() == QEvent::Leave) {
		MouseEnter = false;
		hide();
	}
	return QWidget::event(e);
}
