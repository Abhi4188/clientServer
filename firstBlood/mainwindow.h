#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUrl>
#include <QtWebKit/QtWebKit>
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QTcpSocket>
//#include <form1.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_closeButton_clicked();

    void on_userIdButton_clicked();

private:
    Ui::MainWindow *ui;
    QTcpSocket *socket;
//    Form1 *form1;
};

#endif // MAINWINDOW_H
