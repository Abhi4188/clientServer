#ifndef FORM1_H
#define FORM1_H

#include <QWidget>
#include "mainwindow.h"

namespace Ui {
class Form1;
}

class Form1 : public QWidget
{
    Q_OBJECT

public:
    explicit Form1(QWidget *parent = 0);
    ~Form1();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Form1 *ui;
    MainWindow *mainWindow = new MainWindow;
};

#endif // FORM1_H
