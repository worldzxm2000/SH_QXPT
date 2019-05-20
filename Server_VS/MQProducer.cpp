
#include "MQProducer.h"
#include"LogWrite.h"
MQProducer::MQProducer(QObject *parent)
	: QObject(parent)
{
	 m_isRun = true;
	 connection = nullptr;
	 session = nullptr;
	 destination = nullptr;
	 producer = nullptr;
}
MQProducer::~MQProducer()
{
	close();
}

void MQProducer::close()
{
	cleanup();
}


void MQProducer::onException(const CMSException& ex AMQCPP_UNUSED)
{
}


bool MQProducer::start()
{
	try {
		// Create a ConnectionFactory                                         /////////////////////
		//ActiveMQConnectionFactory *connectionFactory = new ActiveMQConnectionFactory(brokerURI, UserName, Password);
		auto_ptr<ConnectionFactory> connectionFactory(ConnectionFactory::createCMSConnectionFactory(brokerURI));
		// Create a Connection
		try
		{
			connection = connectionFactory->createConnection();
			connection->start();
		
		}
		catch (CMSException& e)
		{
			e.printStackTrace();
			throw e;
			return false;
		}

		// Create a Session
		session = connection->createSession(Session::AUTO_ACKNOWLEDGE);
	

		// Create the destination (Topic or Queue)

		destination = session->createQueue(destURI);
	

		// Create a MessageProducer from the Session to the Topic or Queue
		producer = session->createProducer(destination);
		producer->setDeliveryMode(DeliveryMode::PERSISTENT);
		return true;
	}
	catch (CMSException& e) {
		e.printStackTrace();
		return false;
	}
}

LRESULT MQProducer::send(const char* Message)
{
	try
	{
		if (session == NULL)
		{
			m_isRun = false;
			return 0;
		}
		std::string str(Message);
		std::auto_ptr<TextMessage> message(session->createTextMessage(str));
		producer->send(message.get());
		if (m_isRun==false)
		{
			LogWrite::WriteLog(QString("消息中间件已重连"));
		}
		m_isRun = true;
		return 1;
	}
	catch (CMSException& e)
	{
		//状态由true改变成false时候，MQ离线通知，需要重连
		if (m_isRun)
		{
			m_isRun = false;
			LogWrite::WriteLog(QString("消息中间件失去连接"));
			return 0;
		}
		return -1;
	
	}
}

void MQProducer::cleanup()
{
	// Destroy resources.
	try {
		if (destination != NULL) delete destination;
	}
	catch (CMSException& e) { e.printStackTrace(); }
	destination = NULL;

	try {
		if (producer != NULL) delete producer;
	}
	catch (CMSException& e) { e.printStackTrace(); }
	producer = NULL;

	// Close open resources.
	try {
		if (session != NULL) session->close();
		if (connection != NULL) connection->close();
	}
	catch (CMSException& e) { e.printStackTrace(); }

	try {
		if (session != NULL) delete session;
	}
	catch (CMSException& e) { e.printStackTrace(); }
	session = NULL;

	try {
		if (connection != NULL) delete connection;
	}
	catch (CMSException& e) { e.printStackTrace(); }
	connection = NULL;
}