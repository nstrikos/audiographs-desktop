#ifndef FUNCTIONMODEL_H
#define FUNCTIONMODEL_H

#include <QObject>
#include "point.h"

#ifdef Q_OS_WIN
#include "parsers/fparser/fparser.hh"
#else
#include "parsers/exprtk/exprtk.hpp"
typedef exprtk::symbol_table<double> symbol_table_t;
typedef exprtk::expression<double>     expression_t;
typedef exprtk::parser<double>             parser_t;
#endif

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
    double x(int i) const;
    double y(int i) const;

    double minValue() const;
    double maxValue() const;

    bool isValid(int i) const;

    int size();

    void calculateDerivative();
    void calculateSecondDerivative();
    void refreshDerivative();

    double derivative(int i) const;

    double minDerivValue() const;

    double maxDerivValue() const;

signals:
    void error(QString);
    void newGraph(QVector<Point> *points, double minX, double maxX, double minY, double maxY);
    void updateDerivative(QVector<Point> *points, double minX, double maxX, double minY, double maxY);

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

#ifdef Q_OS_WIN
    FunctionParser m_fparser;
#else
    symbol_table_t symbol_table;
    double m_x;
    expression_t parser_expression;
#endif

    QVector<Point> m_points;
    QVector<Point> m_derivPoints;
};

#endif // FUNCTIONMODEL_H
