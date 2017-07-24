#ifndef MAINSERVER_H
#define MAINSERVER_H

#include <QObject>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QTcpServer>
#include <QTcpSocket>
#include <QNetworkInterface>

class MainServer : public QObject
{
    Q_OBJECT
public:
    explicit MainServer(QObject *parent = 0);

signals:

public slots:
    void newConnection();
    void readData();

private:
    QTcpServer *server;
    QTcpSocket *socket;

    QFile m_target;

    qint16 m_connectionCount = 0;
};

#endif // MAINSERVER_H
