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
    ui->userIdButton->setEnabled(true);

 //   form1->show();
}

void MainWindow::on_userIdButton_clicked()
{
    ui->userIdButton->setEnabled(false);
    QByteArray userId = ui->userIdTextEdit->toPlainText().toUtf8();

    qDebug() << userId;

    // read connection message and send server the userID
    socket->connectToHost("192.168.0.111", 1234);

    socket->waitForReadyRead();

    QByteArray serverResponse = socket->readAll();
    qDebug() << "incoming message from server " << serverResponse;
    ui->serverMsgTextBrowser->setText(serverResponse);


    // send USER_ID token to server
    socket->write("USER_ID");
    socket->flush();
    socket->waitForBytesWritten(3000);

    // send userID to server
    socket->write(userId);
    socket->flush();
    socket->waitForBytesWritten(3000);
    qDebug() << "userID sent to server";

    // wait for server to acknowledge that it is ready to receive the file
    socket->waitForReadyRead();
    serverResponse = socket->readAll();
    qDebug() << "serever response = " << serverResponse;

    if(serverResponse != "SEND_FILE")
    {
        qDebug() << "No server ack received to send file";
        return;
    }

    QString fileName = "/home/karuna/project/client_server/resources/testFile.txt";
    QFile file(fileName);

    if(!file.open(QFile::ReadOnly))
    {
        qDebug() << "Could not open file";
        ui->fileContentsTextBrowser->setText("Could not open file");
    }

    QTextStream in(&file);
    QByteArray text = in.readAll().toUtf8();

    ui->fileContentsTextBrowser->setText(text);

    // send FILE token to server
    socket->write("FILE");
    socket->flush();
    socket->waitForBytesWritten(3000);

    // send actual file to server
    socket->write(text);
    socket->flush();
    socket->waitForBytesWritten(3000);
    qDebug() << "File sent to server...\n";

    file.flush();
    file.close();

    ui->closeButton->setEnabled(true);
}
