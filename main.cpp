#include "mainwindow.h"
#include "Class.h"
#include <QApplication>

Citys cities;

int main(int argc, char *argv[])
{
    ifstream fin("data.txt");
    if(fin.is_open()) {
        fin>>cities;
    }
    fin.close();
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("交通咨询系统");
    w.show();
    return a.exec();
}
