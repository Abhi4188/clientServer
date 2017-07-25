#include "mainServer.h"

#define ADD(TOKEN, FUNCTOR) {TOKEN, std::bind(FUNCTOR, this)}

MainServer::MainServer(QObject *parent) :
    QObject{parent},
    m_dataHandlers
    {
        ADD("USER_ID", &MainServer::handleUserID),
        ADD("FILE", &MainServer::handleFile)
    }
{
    m_server = new QTcpServer(this);
    m_socket = new QTcpSocket(this);

    connect(m_server, SIGNAL(newConnection()), this, SLOT(newConnection()));

    QHostAddress ipAddress;
    QList<QHostAddress> ipAddressList = QNetworkInterface::allAddresses();

    for(int i = 0; i < ipAddressList.size(); ++i)
    {
        if(ipAddressList.at(i) != QHostAddress::LocalHost &&
            ipAddressList.at(i).toIPv4Address()) {
                ipAddress = ipAddressList.at(i);
                break;
        }
    }

    if(!m_server->listen(ipAddress, 1234))
    {
        qDebug() << "Unable to start server " << m_server->errorString();
        return;
    }

    if(ipAddress.isNull())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();

    qDebug() << "The server is running on IP: " << ipAddress << "\nPort: " << m_server->serverPort();
}

void MainServer::newConnection()
{
    m_socket = m_server->nextPendingConnection();
    m_connectionCount++;
    QByteArray welcomeMessage = QByteArray("hello client\r\nSend me the userID\nConnection count = ").append(QString::number(m_connectionCount)).append("\r\n");
    m_socket->write(welcomeMessage);
    m_socket->flush();

    m_socket->waitForBytesWritten(3000);
    qDebug() << "client connected";

    auto handleIncoming = [this](){

        qDebug() << "incoming from client";
        this->parser();
    };

    connect(m_socket, &QTcpSocket::readyRead, handleIncoming);
}

void MainServer::parser()
{
    QByteArray incoming = m_socket->readAll();

    if (m_dataHandlers.contains(incoming))
        m_dataHandlers[incoming]();
}

void MainServer::handleUserID()
{
    // wait to receive userID
    m_socket->waitForReadyRead();
    QByteArray userId = m_socket->readAll();

    // update the target file location based on the received userID
    const QString fileName = "/receivedFile.txt";
    QString filePath = "/home/karuna/project/client_server/resources/user_accounts/" + userId;

    if(!QDir(filePath).exists())
        QDir().mkdir(filePath);

    m_target.setFileName(filePath + fileName);

    m_socket->write("SEND_FILE");
    m_socket->waitForBytesWritten(3000);
}

void MainServer::handleFile()
{
    // wait to receive file
    m_socket->waitForReadyRead();
    QByteArray fileData = m_socket->readAll();

    if(!m_target.open(QFile::WriteOnly | QFile::Append))
    {
        qDebug() << "Can't open file for writting";
        return;
    }

    m_target.write(fileData);
    m_target.flush();
    m_target.close();

    qDebug() << "file size: " << m_target.size();
}
