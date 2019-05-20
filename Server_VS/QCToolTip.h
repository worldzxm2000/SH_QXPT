#pragma once

#include <QWidget>
#include"QDateTime"
#include"Global.h"
#include<QLabel>
#include<QGroupBox>
#include<QHBoxLayout>
#include<QVBoxLayout>
namespace Ui { class QCToolTip; };

class QCToolTip : public QWidget
{
	Q_OBJECT

public:
	explicit QCToolTip(QWidget *parent = Q_NULLPTR);
	~QCToolTip();
	void showMessage(QPoint point, FACILITYINFO *client);
	void hide();
	bool WindowVisable;
	bool MouseEnter;
	int x0, y0, x1, y1;
private:
	Ui::QCToolTip *ui;
	bool event(QEvent *e);
};

