#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <QIcon>
#include <QTextStream>





int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile styleFile(":/styles.qss");
    if (styleFile.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream stream(&styleFile);
        a.setStyleSheet(stream.readAll());
        styleFile.close();
    }

    MainWindow w;
    w.setWindowIcon(QIcon(":/icons/app_icon.svg"));
    w.show();
    return a.exec();
}
