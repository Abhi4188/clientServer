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
    void readData();

private:
    QTcpServer *server;
    QTcpSocket *socket;
};

#endif // MAINSERVER_H
