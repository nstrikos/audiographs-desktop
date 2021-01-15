#include "mainwindow.h"

#include <QApplication>

#include "function/functionExpression.h"
#include "function/functionConnector.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.showMaximized();

    FunctionExpression functionExpression;

    FunctionConnector functionConnector;

    functionConnector.start(w, functionExpression);

    return a.exec();
}
