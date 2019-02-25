#include "WebCommServer.h"
#include<QJsonObject>
#include<QJsonDocument>
#include<qDebug>
WebCommServer::WebCommServer()
{
}


WebCommServer::~WebCommServer()
{
}


void WebCommServer::onMessage(const Message* message)
{
	try {
		
		const TextMessage* textMessage = dynamic_cast<const TextMessage*> (message);
		string text = "";

		if (textMessage != NULL) {
			text = textMessage->getText();
			QString qTxt = QString::fromStdString(text);
			QJsonObject json;
			QJsonDocument doc = QJsonDocument::fromJson(qTxt.toLocal8Bit().data());
			if (!doc.isNull())
			{
				if (doc.isObject())
				{
					json = doc.object();
					int ServiceTypeID = json.find("ServiceTypeID").value().toInt();
					QString StationID = json.find("StationID").value().toString();
					QString DeviceID = json.find("DeviceID").value().toString();
					int CommandID = json.find("Command").value().toInt();
					QJsonObject Params = json.find("Parameter").value().toObject();
					int ParamsCount = Params.find("Count").value().toInt();
					QStringList commLst;
					for (int i = 0; i < ParamsCount; i++)
					{
						QString paramter= Params.find("Params"+QString::number(i+1)).value().toString();
						if(paramter!=NULL)
							commLst.append(paramter);
					}
					emit NoticfyServerFacilityID(ServiceTypeID, StationID, DeviceID, CommandID,commLst);
				}
			}
			else
			{
				qDebug() << "===> please check the string " << qTxt.toLocal8Bit().data();

			}
			
		}
	}
	catch (CMSException& e) {
		e.printStackTrace();
	}

}

bool WebCommServer::start()
{
	return initialize();
}

bool WebCommServer::initialize()
{
	try {
	// Create a ConnectionFactory
	auto_ptr<ConnectionFactory> connectionFactory(
		ConnectionFactory::createCMSConnectionFactory(brokerURI));

	// Create a Connection
	connection = connectionFactory->createConnection();
	connection->start();
	connection->setExceptionListener(this);

	// Create a Session
	session = connection->createSession(Session::AUTO_ACKNOWLEDGE);
	

	// Create the destination (Topic or Queue)

		destination = session->createQueue(destURI);
		

	// Create a MessageConsumer from the Session to the Topic or Queue
	consumer = session->createConsumer(destination);

	consumer->setMessageListener(this);
	return true;
	}
	catch (CMSException& e) {
		e.printStackTrace();
		return false;
	}
}

void WebCommServer::close()
{
	cleanup();
}
void WebCommServer::cleanup()
{

	if (connection != NULL) {
		try {
			connection->close();
		}
		catch (cms::CMSException& ex) {
			ex.printStackTrace();
		}
	}

	// Destroy resources.
	try {
		delete destination;
		destination = NULL;
		delete consumer;
		consumer = NULL;
		delete session;
		session = NULL;
		delete connection;
		connection = NULL;
	}
	catch (CMSException& e) {
		e.printStackTrace();
	}
}

void WebCommServer::onException(const CMSException& ex AMQCPP_UNUSED)
{
	

}