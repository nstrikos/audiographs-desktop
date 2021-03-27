#ifndef PINCHHANDLER_H
#define PINCHHANDLER_H

#include <QObject>

class FunctionModel;

class PinchHandler : public QObject
{
    Q_OBJECT
public:
    explicit PinchHandler(QObject *parent = nullptr);
    void startPinch(FunctionModel &model);
    void pinch(FunctionModel &model, double scale);

signals:
    void newInputValues(double minX, double maxX, double minY, double maxY);

private:
    double m_minX;
    double m_maxX;
    double m_minY;
    double m_maxY;

};

#endif // PINCHHANDLER_H
