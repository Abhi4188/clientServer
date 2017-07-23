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
    QString userId = ui->userIdTextEdit->toPlainText();
    qDebug() << "userId = " << userId;

    // send server the userID
    // send server the file

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

    socket->connectToHost("192.168.0.111", 1234);

    file.flush();
    file.close();

    /*
    QString filePath = "/home/karuna/project/client_server/resources/user_accounts/" + userId;

    if(!QDir(filePath).exists())
        QDir().mkdir(filePath);
    */
}
