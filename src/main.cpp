#include "mainwindow.hpp"

#include <QApplication>

#include <iostream>

using namespace mg32;
using namespace std;

int main(int argc,char* argv[])
{
    QApplication app(argc, argv);

    MainWindow window;
    window.show();

    return app.exec();
}
