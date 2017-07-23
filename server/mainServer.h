#ifndef MAINSERVER_H
#define MAINSERVER_H

#include <QObject>
#include <QDebug>
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
    void readyRead();

private:
    QTcpServer *server;
    QTcpSocket *socket;

    qint16 connectionCount = 0;
};

#endif // MAINSERVER_H
