#ifndef FUNCTIONCONNECTOR_H
#define FUNCTIONCONNECTOR_H

#include "mainwindow.h"
#include "function/functionExpression.h"

class FunctionConnector
{
public:
    explicit FunctionConnector();
    void start(MainWindow &window, FunctionExpression &functionExpression);
};

#endif // FUNCTIONCONNECTOR_H
