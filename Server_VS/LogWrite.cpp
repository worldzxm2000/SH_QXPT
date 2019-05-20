﻿#include "LogWrite.h"
#include"qdir.h"
QMutex mutex;//日志代码互斥锁 
LogWrite::LogWrite(QObject *parent)
	: QObject(parent)
{
}

LogWrite::LogWrite()
{

}
LogWrite::~LogWrite()
{
}


void LogWrite::WriteLog(QString MSG)
{
	mutex.lock();
	QDateTime current_date_time = QDateTime::currentDateTime();
	QString current_date = current_date_time.toString("yyyy.MM.dd hh:mm:ss");
	QString fileName = QCoreApplication::applicationDirPath() + "\\Log";
	QDir dir(fileName);
	if (!dir.exists())
		dir.mkpath(fileName);//创建多级目录
	fileName += "\\SYSLog.txt";
	QFile file(fileName);
	QTextStream in(&file);
	file.open(QIODevice::ReadWrite| QIODevice::Append);
	in << current_date << ":" << MSG<<"\r\n";
	file.close();
	mutex.unlock();
}
