#include "form1.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Form1 form1;
    form1.show();

    return a.exec();
}
