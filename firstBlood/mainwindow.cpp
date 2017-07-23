#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QTcpSocket();
    ui->pushButton_2->setEnabled(false);
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
    QByteArray text = in.readAll().toUtf8();

    ui->textBrowser->setText(text);

    auto handleIncoming = [this, text](){
        ui->pushButton->setEnabled(false);
        ui->pushButton_2->setEnabled(true);

        QByteArray incoming = socket->readAll();
        qDebug() << "lambda:: incoming message from server " << incoming;
        ui->textBrowser_2->setText(incoming);

        auto bytesWritten = socket->write(text);
        socket->flush();

        qDebug() << "bytes written to server: " << bytesWritten;

        socket->waitForBytesWritten(3000);
    };

    connect(socket, &QTcpSocket::readyRead, handleIncoming);

    socket->connectToHost("192.168.0.111", 1234);

    file.flush();
    file.close();
}

void MainWindow::on_pushButton_2_clicked()
{
    socket->close();
    socket->disconnect();
    ui->pushButton->setEnabled(true);
    ui->pushButton_2->setEnabled(false);
}

void MainWindow::on_pushButton_3_clicked()
{
    QString userName = ui->textEdit->toPlainText();
    qDebug() << userName;
}
