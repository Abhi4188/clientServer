#include "mainServer.h"

MainServer::MainServer(QObject *parent) : QObject(parent)
{
    server = new QTcpServer(this);
    socket = new QTcpSocket(this);

    connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readData()));

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

    if(!server->listen(ipAddress, 1234))
    {
        qDebug() << "Unable to start server " << server->errorString();
        return;
    }

    if(ipAddress.isNull())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();

    qDebug() << "The server is running on IP: " << ipAddress << "\nPort: " << server->serverPort();

    /*
    if(!server->listen(ipAddress, 1234))
    {
        qDebug() << "Server could not start";
    }

    else
    {
        qDebug() << "Server started";
    }
    */
}

void MainServer::newConnection()
{
    QTcpSocket *socket = server->nextPendingConnection();

    socket->write("hello client\r\nSend me the file\r\n");
    socket->flush();

    socket->waitForBytesWritten(3000);
    qDebug() << "client connected";
}

void MainServer::readData()
{
    QByteArray incoming = socket->readAll();
    QString fileName = "/home/karuna/project/client_server/resources/receivedFile.txt";
    QFile target;
    target.setFileName(fileName);

    if(!target.open(QFile::WriteOnly | QFile::Append))
    {
        qDebug() << "Can't open file for writting";
        return;
    }

    target.write(incoming);
    target.flush();
    target.close();

    qDebug() << "file size: " << target.size();
}
