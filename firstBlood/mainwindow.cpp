#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QTcpSocket();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString fileName = "/home/karuna/project/client_server/resources/testFile.txt";
    QFile file(fileName);

    if(!file.open(QFile::ReadOnly))
    {
        qDebug() << "Could not open file";
        ui->textBrowser->setText("Could not open file");
    }

    QTextStream in(&file);
 //   QString text = in.readAll();

//   ui->textBrowser->setText(text);

    socket->connectToHost("192.168.0.111", 1234);
    socket->waitForConnected();
    if(!socket->open(QIODevice::ReadWrite))
        qDebug() << "Could not connect to server";

    else
    {
        socket->waitForBytesWritten(4000);
        QByteArray in = socket->readAll();
        qDebug() << "server response: " << in;
    }

    QByteArray q = file.readAll();

    file.flush();
    file.close();

    socket->write(q);

//    for(int i = 0; i < q.size();)
//    {
//        i += socket->write(q);
//    }
}
