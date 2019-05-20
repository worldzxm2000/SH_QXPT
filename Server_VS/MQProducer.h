
#include <decaf/util/concurrent/CountDownLatch.h>
#include <decaf/lang/Long.h>
#include <decaf/util/Date.h>
#include <activemq/core/ActiveMQConnectionFactory.h>
#include <activemq/util/Config.h>
#include <activemq/library/ActiveMQCPP.h>
#include <cms/Connection.h>
#include <cms/Session.h>
#include <cms/TextMessage.h>
#include <cms/BytesMessage.h>
#include <cms/MapMessage.h>
#include <cms/ExceptionListener.h>
#include <cms/MessageListener.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <memory>
#include <QObject>
#include<QTimer>
using namespace activemq;
using namespace activemq::core;
using namespace decaf;
using namespace decaf::lang;
using namespace decaf::util;
using namespace decaf::util::concurrent;
using namespace cms;
using namespace std;

class MQProducer:public QObject
{
	Q_OBJECT
public:
	MQProducer(QObject *parent=nullptr);
	virtual ~MQProducer();
	//消息中间件配置参数
	string brokerURI;
	string destURI;
	string UserName;
	string Password;
	unsigned int numMessages = 2000;
	bool start();
	//bool start(const std::string& UserName, const std::string& Password, const std::string& brokerURI, unsigned int numMessages, const std::string& destURI, bool useTopic, bool clientAck);
	//1:发送正常
	//0:离线通知
	//-1:无法连接
	LRESULT send(const char* Message);
	//关闭连接
	void close();
private:
	//连接
	Connection* connection;
	//会话
	Session* session;
	Destination* destination;
	MessageProducer* producer;
	//运行状态
	bool m_isRun;
	//清除资源
	void cleanup();
	virtual void onException(const CMSException& ex AMQCPP_UNUSED);
};
