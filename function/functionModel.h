#ifndef FUNCTIONMODEL_H
#define FUNCTIONMODEL_H

#include <QObject>

#include "point.h"

#if defined(Q_OS_LINUX) && !defined(Q_OS_ANDROID)
#include "parsers/exprtk/exprtk.hpp"
typedef exprtk::symbol_table<double> symbol_table_t;
typedef exprtk::expression<double>     expression_t;
typedef exprtk::parser<double>             parser_t;
#else
#include "parsers/fparser/fparser.hh"
double powerint(const double* p);
#endif

int mygcd(int a, int b);

class FunctionModel : public QObject
{
    Q_OBJECT
public:
    explicit FunctionModel(QObject *parent = nullptr);
    void calculate(QString expression, QString minX, QString maxX, QString minY, QString maxY);

    QString expression() const;
    double minX() const;
    double maxX() const;
    double minY() const;
    double maxY() const;
    double x(int i);
    double y(int i);

    double minValue() const;
    double maxValue() const;

    bool isValid(int i);

    bool validLimit(double x);

    int size();

    void calculateDerivative();
    void calculateSecondDerivative();
    void refreshDerivative();

    double derivative(int i);

    double minDerivValue() const;

    double maxDerivValue() const;

    bool validExpression() const;

signals:
    void error(QString);
    void newGraph(Points *points, double minX, double maxX, double minY, double maxY);
    void updateDerivative(Points *points, double minX, double maxX, double minY, double maxY);

private:
    void replaceConstants();
    bool check();

    void calculatePoints();

    QString m_expression;
    QString m_minXString;
    QString m_maxXString;
    QString m_minYString;
    QString m_maxYString;
    QString m_pointsString;

    QString m_errorString;

    double m_minX;
    double m_maxX;
    double m_minY;
    double m_maxY;
    double m_minValue;
    double m_maxValue;
    double m_minDerivValue;
    double m_maxDerivValue;
    bool m_validExpression;

#if defined(Q_OS_LINUX) && !defined(Q_OS_ANDROID)
    symbol_table_t symbol_table;
    double m_x;
    expression_t parser_expression;
#else
    FunctionParser m_fparser;
#endif

    //QVector<Point> m_points;
    //array<Point,10000>m_points;
    Points m_points;
    Points m_derivPoints;
};

#endif // FUNCTIONMODEL_H
