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
    void parser();

private:
    QTcpServer *m_server;
    QTcpSocket *m_socket;
    QFile m_target;
    qint16 m_connectionCount = 0;
    QHash<QString, std::function<void (void)>> m_dataHandlers;

    /*!
     * \brief handleUserID Receive userID and update the target file location \ref m_targer to receive file into.
     */
    void handleUserID();

    /*!
     * \brief handleFile Receive the data file into the targer file location
     */
    void handleFile();
};

#endif // MAINSERVER_H
