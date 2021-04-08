#ifndef POINT_H
#define POINT_H

#include<array>
using namespace std;

#include <QObject>


class Point
{
public:
    Point();
    double x;
    double y;
    bool isValid;
};

class Points : public QObject
{
        Q_OBJECT
public:
    Points();

    void setPoint(int i, Point point);
    double xAt(int i);
    double yAt(int i);
    bool validAt(int i);

private:
    array<Point, 10000> m_points;
};

#endif // POINT_H
