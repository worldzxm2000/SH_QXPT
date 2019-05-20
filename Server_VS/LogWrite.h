#pragma once

#include <QObject>
#include<qmutex.h>
#include <QFile>  
#include <QApplication>  
#include <iostream>  
#include <cstdlib>  
#include <QString>  
#include <QTextStream>  
#include <QDateTime>  

class LogWrite : public QObject
{
	Q_OBJECT

public:
	LogWrite(QObject *parent);
	LogWrite();
	~LogWrite();

	/*
	* @brief 写入系统运行日志
	* @param MSG 参数1 运行信息
	* @return 返回说明
	无
	*/
   static void WriteLog(QString MSG);
   /*
   * @brief 写入系统报警日志
   * @param MSG 参数1 运行信息
   * @return 返回说明
   无
   */

};
