#include "functionConnector.h"

#include <QObject>

FunctionConnector::FunctionConnector()
{

}

void FunctionConnector::start(MainWindow &window, FunctionExpression &functionExpression)
{
    QObject::connect(&window, &MainWindow::calculate, &functionExpression, &FunctionExpression::calculate);
    QObject::connect(&functionExpression, &FunctionExpression::newGraph, &window, &MainWindow::updateGraph);
    QObject::connect(&functionExpression, &FunctionExpression::newInputValues, &window, &MainWindow::newInputValues);
    QObject::connect(&window, &MainWindow::startDrag, &functionExpression, &FunctionExpression::startDrag);
    QObject::connect(&window, &MainWindow::drag, &functionExpression, &FunctionExpression::drag);
    QObject::connect(&window, &MainWindow::zoom, &functionExpression, &FunctionExpression::zoom);
    QObject::connect(&functionExpression, &FunctionExpression::updateDerivative, &window, &MainWindow::updateDerivative);
    QObject::connect(&functionExpression, &FunctionExpression::error, &window, &MainWindow::error);
    QObject::connect(&window, &MainWindow::playSound, &functionExpression, &FunctionExpression::audio);
    QObject::connect(&window, &MainWindow::stopSound, &functionExpression, &FunctionExpression::stopAudio);
    QObject::connect(&functionExpression, &FunctionExpression::audioFinished, &window, &MainWindow::audioFinished);
    QObject::connect(&functionExpression, &FunctionExpression::newCurrentPoint, &window, &MainWindow::newCurrentPoint);
    QObject::connect(&window, &MainWindow::nextPoint, &functionExpression, &FunctionExpression::nextPoint);
    QObject::connect(&window, &MainWindow::previousPoint, &functionExpression, &FunctionExpression::previousPoint);
    QObject::connect(&window, &MainWindow::sayX, &functionExpression, &FunctionExpression::sayX);
    QObject::connect(&window, &MainWindow::sayY, &functionExpression, &FunctionExpression::sayY);
    QObject::connect(&window, &MainWindow::getX, &functionExpression, &FunctionExpression::getX);
    QObject::connect(&window, &MainWindow::getY, &functionExpression, &FunctionExpression::getY);
    QObject::connect(&functionExpression, &FunctionExpression::updateText, &window, &MainWindow::updateLabelText);
    QObject::connect(&window, &MainWindow::sayDerivative, &functionExpression, &FunctionExpression::sayDerivative);
    QObject::connect(&window, &MainWindow::getDerivative, &functionExpression, &FunctionExpression::getDerivative);
    QObject::connect(&window, &MainWindow::decStep, &functionExpression, &FunctionExpression::decStep);
    QObject::connect(&window, &MainWindow::incStep, &functionExpression, &FunctionExpression::incStep);
    QObject::connect(&window, &MainWindow::externalPreviousPointInterest, &functionExpression, &FunctionExpression::previousPointInterest);
    QObject::connect(&window, &MainWindow::externalNextPointInterest, &functionExpression, &FunctionExpression::nextPointInterest);
    QObject::connect(&functionExpression, &FunctionExpression::interestingPointFinished, &window, &MainWindow::interestingPointFinished);
    QObject::connect(&window, &MainWindow::externalPreviousFast, &functionExpression, &FunctionExpression::previousFast);
    QObject::connect(&window, &MainWindow::externalNextFast, &functionExpression, &FunctionExpression::nextFast);
    QObject::connect(&window, &MainWindow::firstPoint, &functionExpression, &FunctionExpression::firstPoint);
    QObject::connect(&window, &MainWindow::lastPoint, &functionExpression, &FunctionExpression::lastPoint);
    QObject::connect(&window, &MainWindow::derivativeMode, &functionExpression, &FunctionExpression::setDerivativeMode);
}
