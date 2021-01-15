#ifndef FUNCTIONDESCRIPTION_H
#define FUNCTIONDESCRIPTION_H

#include <QString>
#include <QVector>
#include "functionModel.h"

class InterestingPoint
{
public:
    double x;
    double y;
    QString label;
};

class FunctionDescription
{
public:
    FunctionDescription();
    QVector<InterestingPoint> points(FunctionModel *model);

private:
    QVector<InterestingPoint> m_points;
};

#endif // FUNCTIONDESCRIPTION_H
