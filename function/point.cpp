#include "point.h"

Point::Point()
{

}

Points::Points()
{

}

void Points::setPoint(int i, Point point)
{
    m_points[i] = point;
}

double Points::xAt(int i)
{
    return m_points.at(i).x;
}

double Points::yAt(int i)
{
    return m_points.at(i).y;
}

bool Points::validAt(int i)
{
    return m_points.at(i).isValid;
}

