#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QTcpSocket();
    ui->closeButton->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    qDebug()  << "no longer active";
}

void MainWindow::on_closeButton_clicked()
{
    socket->close();
    socket->disconnect();
    ui->pushButton->setEnabled(true);
    ui->closeButton->setEnabled(false);

 //   form1->show();
}

void MainWindow::on_userIdButton_clicked()
{
    QByteArray userId = "userID:";
    userId.append(ui->userIdTextEdit->toPlainText());

    qDebug() << userId;

    // send server the userID
    socket->connectToHost("192.168.0.111", 1234);

    socket->waitForReadyRead();

    QByteArray serverResponse = socket->readAll();
    qDebug() << "incoming message from server " << serverResponse;
    ui->serverMsgTextBrowser->setText(serverResponse);


    socket->write(userId);
    socket->flush();
    socket->waitForBytesWritten(3000);
    qDebug() << "userID sent to server";

    socket->waitForReadyRead();

    serverResponse = socket->readAll();
    qDebug() << "serever response = " << serverResponse;

    if(serverResponse != "SEND_FILE")
    {
        qDebug() << "No server ack received to send file";
        return;
    }

    // send server the file
    QString fileName = "/home/karuna/project/client_server/resources/testFile.txt";
    QFile file(fileName);

    if(!file.open(QFile::ReadOnly))
    {
        qDebug() << "Could not open file";
        ui->fileContentsTextBrowser->setText("Could not open file");
    }

    QTextStream in(&file);
    QByteArray text = "Sending file to server...\n";
    text.append(in.readAll().toUtf8());

    ui->fileContentsTextBrowser->setText(text);

    auto handleIncoming = [this, text](){
        ui->pushButton->setEnabled(false);
        ui->closeButton->setEnabled(true);

        QByteArray incoming = socket->readAll();
        qDebug() << "lambda:: incoming message from server " << incoming;
        ui->serverMsgTextBrowser->setText(incoming);

        auto bytesWritten = socket->write(text);
        socket->flush();

        qDebug() << "bytes written to server: " << bytesWritten;

        socket->waitForBytesWritten(3000);
    };

    connect(socket, &QTcpSocket::readyRead, handleIncoming);

    file.flush();
    file.close();

    /*
    QString filePath = "/home/karuna/project/client_server/resources/user_accounts/" + userId;

    if(!QDir(filePath).exists())
        QDir().mkdir(filePath);
    */
}
