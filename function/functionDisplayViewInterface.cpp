#include "functionDisplayViewInterface.h"

#include <math.h>

FunctionDisplayViewInterface::FunctionDisplayViewInterface()
{
    m_points = nullptr;
}

FunctionDisplayViewInterface::~FunctionDisplayViewInterface()
{

}

void FunctionDisplayViewInterface::calcCoords(int width, int height)
{
    if (m_points == nullptr)
        return;

    m_coordPoints.clear();

    Point tmpPoint;

    for (int i = 0; i < 10000; i++) {
        if (m_points->validAt(i)) {
            int k = static_cast<int>( round(  width / (m_xMax - m_xMin) * (m_points->xAt(i) - m_xMin) ));
            int l = static_cast<int>( round( (height / (m_yMax - m_yMin) * (m_points->yAt(i) - m_yMin))));
            l = height - l;
            tmpPoint.x = k;
            tmpPoint.y = l;
            m_coordPoints.append(tmpPoint);
        } else {
            tmpPoint.x = -10;
            tmpPoint.y = -10;
            m_coordPoints.append(tmpPoint);
        }
    }
}

void FunctionDisplayViewInterface::calcDerivCoords(int width, int height)
{
//    if (m_model != nullptr && m_model->size() > 0) {

//        m_coordPoints.clear();
//        Point tmpPoint;

//        int size = m_model->size();

//        if (size == 0)
//            return;

//        double xStart = m_model->x(0);
//        double xEnd = m_model->x(size - 1);

//        for (int i = 0; i < size; i++) {
//            if (m_model->isValid(i)) {
//                double minY = m_model->minY();
//                double maxY = m_model->maxY();

//                double x =  ( width / (xEnd - xStart) * (m_model->x(i) - xStart) );
//                double y = ( height / (maxY - minY) * (m_model->derivative(i) - minY) );

//                y = height - y;
//                tmpPoint.x = x;
//                tmpPoint.y = y;
//            } else {
//                tmpPoint.x = -30;
//                tmpPoint.y = -30;
//            }
//            m_coordPoints.append(tmpPoint);
//        }
//    }
}
