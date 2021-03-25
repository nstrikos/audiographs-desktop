#ifndef FUNCTIONDISPLAYVIEWINTERFACE_H
#define FUNCTIONDISPLAYVIEWINTERFACE_H

#include <QVector>
#include "function/point.h"

class FunctionDisplayViewInterface
{
public:
    FunctionDisplayViewInterface();
    ~FunctionDisplayViewInterface();

protected:
    Points *m_points;

    double m_xMin;
    double m_xMax;
    double m_yMin;
    double m_yMax;

    QVector<Point> m_coordPoints;
    void calcCoords(int width, int height);
    void calcDerivCoords(int width, int height);
};

#endif // FUNCTIONDISPLAYVIEWINTERFACE_H
