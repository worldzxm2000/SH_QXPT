#pragma once

#ifndef ITEMWIDGET_H
#define ITEMWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include "Global.h"
#include"Global_Var.h"
//class CLabel;

class ItemWidget : public QWidget
{
	Q_OBJECT
public:
	explicit ItemWidget(QWidget *parent = 0);
	~ItemWidget();
	void SetClient(FACILITYINFO *client);
	FACILITYINFO *GetClient();
signals:

	public slots :
private:
	QLabel *labelName;
	QHBoxLayout *horLayout;
	FACILITYINFO *m_client;
protected:
	bool event(QEvent *e);
};

#endif // ITEMWIDGET_H
