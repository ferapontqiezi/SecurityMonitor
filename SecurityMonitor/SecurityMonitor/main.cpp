#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile qss(":/icons/icons/myStyle.qss");
    if (qss.open(QFile::ReadOnly))
    {
        qDebug("成功打开!");
        a.setStyleSheet(QLatin1String(qss.readAll()));
        qss.close();
    }
    else
    {
        qDebug("打开失败!");
    }
    MainWindow w;
    w.show();
    return a.exec();
}
