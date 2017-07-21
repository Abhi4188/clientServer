#include <QCoreApplication>
#include <mainServer.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MainServer mServer;

    return a.exec();
}

