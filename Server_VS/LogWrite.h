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
	* @brief д��ϵͳ������־
	* @param MSG ����1 ������Ϣ
	* @return ����˵��
	��
	*/
   static void WriteLog(QString MSG);
   /*
   * @brief д��ϵͳ������־
   * @param MSG ����1 ������Ϣ
   * @return ����˵��
   ��
   */

};
