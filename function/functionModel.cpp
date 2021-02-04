#include "functionModel.h"

#include <QtMath>

#include "constants.h"

#include <QDebug>

#ifndef Q_OS_WIN
#include <bits/stdc++.h>
using namespace std;
#endif

FunctionModel::FunctionModel(QObject *parent) : QObject(parent)
{
#ifndef Q_OS_WIN

    symbol_table.add_function(
                "power",
                [](double v0, double v1, double v2) -> double
    {

        int a = (int) v1;
        int b = (int) v2;

        int d = __gcd(a, b);

        a = a / d;
        b = b / d;

        double ratio = (double) a / b;

        int sign;
        if (v0 > 0) sign = 1;
        if (v0 < 0) sign = -1;
        if (v0 == 0) sign = 0;



        if ((int)b % 2 == 0) {
            return pow(v0, ratio);
        } else {
            if ((int)a % 2 == 0) {
                return pow(abs(v0), ratio);
            } else {
                return sign * pow(abs(v0), ratio);
            }
        }
    });

    symbol_table.add_variable("x",m_x);
    symbol_table.add_constant("pi", M_PI);
    symbol_table.add_constant("e", M_E);
    symbol_table.add_constants();
    parser_expression.register_symbol_table(symbol_table);

#endif
}

void FunctionModel::calculate(QString expression, QString minX, QString maxX, QString minY, QString maxY)
{
    m_expression = expression;
    m_minXString = minX;
    m_maxXString = maxX;
    m_minYString = minY;
    m_maxYString = maxY;

    if ( check() ) {
        calculatePoints();
        emit newGraph(&m_points, m_minX, m_maxX, m_minY, m_maxY);
    } else {
        emit error(m_errorString);
    }
}

bool FunctionModel::check()
{
    bool okMin, okMax, okMinY, okMaxY;

    replaceConstants();

    double minDouble = m_minXString.toDouble(&okMin);
    if (okMin) {
        m_minX = minDouble;
    }
    else {
        m_errorString = tr("Minimum is not a real number.");
        return false;
    }

    double maxDouble = m_maxXString.toDouble(&okMax);
    if (okMax) {
        m_maxX = maxDouble;
    }
    else {
        m_errorString = tr("Maximum is not a real number.");
        return false;
    }

    double minYDouble = m_minYString.toDouble(&okMinY);
    if (okMinY) {
        m_minY = minYDouble;
    }
    else {
        m_errorString = tr("Minimum Y is not a real number.");
        return false;
    }

    double maxYDouble = m_maxYString.toDouble(&okMaxY);
    if (okMaxY) {
        m_maxY = maxYDouble;
    }
    else {
        m_errorString = tr("Maximum Y is not a real number.");
        return false;
    }

    if (m_maxX <= m_minX) {
        m_errorString = tr("Maximum must be greater than minimum.");
        return false;
    }

    if (m_maxY <= m_minY) {
        m_errorString = tr("Maximum Y must be greater than minimum Y.");
        return false;
    }

#ifdef Q_OS_WIN

    m_fparser.AddConstant("pi", M_PI);
    m_fparser.AddConstant("e", M_E);
    int res = m_fparser.Parse(m_expression.toStdString(), "x");
    if (res >= 0) {
        const char *s;
        s = m_fparser.ErrorMsg();
        m_errorString = QString::fromUtf8(s);
        return false;
    }

#else

    typedef exprtk::parser<double>::settings_t settings_t;

    std::size_t compile_options = settings_t::e_joiner            +
            settings_t::e_commutative_check +
            settings_t::e_strength_reduction;

    parser_t parser(compile_options);
    parser.compile(m_expression.toStdString(), parser_expression);

    if (!parser.compile(m_expression.toStdString(),parser_expression))
    {
        for (std::size_t i = 0; i < 1; ++i)
        {
            typedef exprtk::parser_error::type error_t;
            error_t error = parser.get_error(i);
            std::string s = error.diagnostic.c_str();
            m_errorString = QString::fromStdString(s);
            int n = m_errorString.indexOf("-");
            m_errorString = m_errorString.right(m_errorString.size() - n - 2);
        }
        return false;
    }

#endif
    return true;
}

void FunctionModel::replaceConstants()
{
    QString piString = QString::number(M_PI);
    QString eString = QString::number(M_E);
    QString ln = "ln";

    m_expression.replace(ln, "log");
}

void FunctionModel::calculatePoints()
{
    Point tmpPoint;

    m_points.clear();
    m_derivPoints.clear();

    double step;

#ifdef Q_OS_WIN

    double x;
    double result;


    double vals[] = { 0 };
    int res;

    step = (m_maxX - m_minX) / LINE_POINTS;
    for (int i = 0; i < LINE_POINTS; i++) {
        x = m_minX + i * step;
        vals[0] = x;
        result = m_fparser.Eval(vals);
        res = m_fparser.EvalError();
        tmpPoint.x = x;
        tmpPoint.y = result;
        if (result != result)
            tmpPoint.isValid = false;
        else if (res > 0)
            tmpPoint.isValid = false;
        else if (res == 0)
            tmpPoint.isValid = true;

        m_points.append(tmpPoint);
    }

#else

    typedef exprtk::parser<double>::settings_t settings_t;

    std::size_t compile_options = settings_t::e_joiner            +
            settings_t::e_commutative_check +
            settings_t::e_strength_reduction;

    parser_t parser(compile_options);
    parser.compile(m_expression.toStdString(), parser_expression);

    step = (m_maxX - m_minX) / LINE_POINTS;
    double y;
    for (int i = 0; i < LINE_POINTS; i++) {
        m_x = m_minX + i * step;
        y = parser_expression.value();
        tmpPoint.x = m_x;
        tmpPoint.y = y;
        if (std::isfinite(y)) {
            tmpPoint.isValid = true;
        }
        else {
            tmpPoint.isValid = false;
        }
        m_points.append(tmpPoint);
    }

#endif

    m_minValue = std::numeric_limits<double>::max();//m_linePoints[0].y;
    m_maxValue = std::numeric_limits<double>::min();//m_linePoints[0].y;

    for (int i = 1; i < LINE_POINTS; i++) {
        if (!m_points[i].isValid)
            continue;
        if (m_points[i].y < m_minValue)
            m_minValue = m_points[i].y;
        if (m_points[i].y > m_maxValue)
            m_maxValue = m_points[i].y;
    }
}

double FunctionModel::maxDerivValue() const
{
    return m_maxDerivValue;
}

double FunctionModel::minDerivValue() const
{
    return m_minDerivValue;
}

double FunctionModel::minValue() const
{
    return m_minValue;
}

double FunctionModel::maxValue() const
{
    return m_maxValue;
}

double FunctionModel::maxY() const
{
    return m_maxY;
}

double FunctionModel::minY() const
{
    return m_minY;
}

double FunctionModel::maxX() const
{
    return m_maxX;
}

double FunctionModel::minX() const
{
    return m_minX;
}

QString FunctionModel::expression() const
{
    return m_expression;
}

double FunctionModel::x(int i) const
{
    return m_points[i].x;
}

double FunctionModel::y(int i) const
{
    return m_points[i].y;
}

bool FunctionModel::isValid(int i) const
{
    return m_points[i].isValid;
}

int FunctionModel::size()
{
    return m_points.size();
}

void FunctionModel::calculateDerivative()
{
    if (m_points.size() <= 0)
        return;

    Point tmpPoint;

    m_derivPoints.clear();

#ifdef Q_OS_WIN
    double vals[] = { 0 };
    const double h = 0.00000001;
    const double h2 = 2 * h;
    double x_init;
    double x;
    double result;

    for (int i = 0; i < LINE_POINTS; i++) {
        x_init = m_points[i].x;
        x = x_init + h2;
        vals[0] = x;
        double y0 = m_fparser.Eval(vals);
        x = x_init + h;
        vals[0] = x;
        double y1 = m_fparser.Eval(vals);
        x = x_init - h;
        vals[0] = x;
        double y2 = m_fparser.Eval(vals);
        x = x_init - h2;
        vals[0] = x;
        double y3 = m_fparser.Eval(vals);

        tmpPoint.x = x_init;
        result = (-y0 + 8 * (y1 - y2) + y3) / (12 * h);

        tmpPoint.y = result;

        if (result != result)
            tmpPoint.isValid = false;
        else
            tmpPoint.isValid = true;

        m_derivPoints.append(tmpPoint);
    }
#else



    for (int i = 0; i < LINE_POINTS; i++) {
        m_x = m_points[i].x;
        double y = exprtk::derivative(parser_expression, m_x);
        tmpPoint.x = m_x;
        tmpPoint.y = y;
        if (std::isfinite(y)) {
            tmpPoint.isValid = true;
        }
        else {
            tmpPoint.isValid = false;
        }
        m_derivPoints.append(tmpPoint);
    }

#endif

    m_minDerivValue = std::numeric_limits<double>::max();//m_linePoints[0].y;
    m_maxDerivValue = std::numeric_limits<double>::min();//m_linePoints[0].y;

    for (int i = 1; i < LINE_POINTS; i++) {
        if (!m_derivPoints[i].isValid)
            continue;
        if (m_derivPoints[i].y < m_minDerivValue)
            m_minDerivValue = m_derivPoints[i].y;
        if (m_derivPoints[i].y > m_maxDerivValue)
            m_maxDerivValue = m_derivPoints[i].y;
    }

    emit updateDerivative(&m_derivPoints, m_minX, m_maxX, m_minY, m_maxY);
}

void FunctionModel::calculateSecondDerivative()
{
    if (m_points.size() <= 0)
        return;

    Point tmpPoint;

    m_derivPoints.clear();

#ifdef Q_OS_WIN
    double vals[] = { 0 };
    const double h = 0.00001;
    const double h2 = 2 * h;
    double x_init;
    double x;
    double result;

    for (int i = 0; i < LINE_POINTS; i++) {
        x_init = m_points[i].x;
        x = x_init;
        vals[0] = x;
        double y = m_fparser.Eval(vals);
        x = x_init + h2;
        vals[0] = x;
        double y0 = m_fparser.Eval(vals);
        x = x_init + h;
        vals[0] = x;
        double y1 = m_fparser.Eval(vals);
        x = x_init - h;
        vals[0] = x;
        double y2 = m_fparser.Eval(vals);
        x = x_init - h2;
        vals[0] = x;
        double y3 = m_fparser.Eval(vals);

        tmpPoint.x = x_init;
        result = (-y0 + 16 * (y1 + y2) - 30 * y - y3) / (12 * h * h);

        double Pow = pow(10.0, 2);
        result = round (y * Pow) / Pow;

        tmpPoint.y = result;

        if (result != result)
            tmpPoint.isValid = true;
        else
            tmpPoint.isValid = false;

        m_derivPoints.append(tmpPoint);
    }
#else
    for (int i = 0; i < LINE_POINTS; i++) {
        m_x = m_points[i].x;
        double y = exprtk::second_derivative(parser_expression, m_x);

        double Pow = pow(10.0, 2);
        y = round (y * Pow) / Pow;

        tmpPoint.x = m_x;
        tmpPoint.y = y;

        if (std::isfinite(y)) {
            tmpPoint.isValid = true;
        }
        else {
            tmpPoint.isValid = false;
        }
        m_derivPoints.append(tmpPoint);
    }

#endif

    m_minDerivValue = std::numeric_limits<double>::max();//m_linePoints[0].y;
    m_maxDerivValue = std::numeric_limits<double>::min();//m_linePoints[0].y;

    for (int i = 1; i < LINE_POINTS; i++) {
        if (!m_derivPoints[i].isValid)
            continue;
        if (m_derivPoints[i].y < m_minDerivValue)
            m_minDerivValue = m_derivPoints[i].y;
        if (m_derivPoints[i].y > m_maxDerivValue)
            m_maxDerivValue = m_derivPoints[i].y;
    }

    emit updateDerivative(&m_derivPoints, m_minX, m_maxX, m_minY, m_maxY);
}

void FunctionModel::refreshDerivative()
{
    if (m_points.size() <= 0)
        return;

    Point tmpPoint;

    m_derivPoints.clear();

#ifdef Q_OS_WIN
    double vals[] = { 0 };
    const double h = 0.00000001;
    const double h2 = 2 * h;
    double x_init;
    double x;
    double result;

    for (int i = 0; i < LINE_POINTS; i++) {
        x_init = m_points[i].x;
        x = x_init + h2;
        vals[0] = x;
        double y0 = m_fparser.Eval(vals);
        x = x_init + h;
        vals[0] = x;
        double y1 = m_fparser.Eval(vals);
        x = x_init - h;
        vals[0] = x;
        double y2 = m_fparser.Eval(vals);
        x = x_init - h2;
        vals[0] = x;
        double y3 = m_fparser.Eval(vals);

        tmpPoint.x = x_init;
        result = (-y0 + 8 * (y1 - y2) + y3) / (12 * h);

        tmpPoint.y = result;

        if (result != result)
            tmpPoint.isValid = false;
        else
            tmpPoint.isValid = true;

        m_derivPoints.append(tmpPoint);
    }
#else



    for (int i = 0; i < LINE_POINTS; i++) {
        m_x = m_points[i].x;
        double y = exprtk::derivative(parser_expression, m_x);
        tmpPoint.x = m_x;
        tmpPoint.y = y;
        if (std::isfinite(y)) {
            tmpPoint.isValid = true;
        }
        else {
            tmpPoint.isValid = false;
        }
        m_derivPoints.append(tmpPoint);
    }

#endif

    m_minDerivValue = std::numeric_limits<double>::max();//m_linePoints[0].y;
    m_maxDerivValue = std::numeric_limits<double>::min();//m_linePoints[0].y;

    for (int i = 1; i < LINE_POINTS; i++) {
        if (!m_derivPoints[i].isValid)
            continue;
        if (m_derivPoints[i].y < m_minDerivValue)
            m_minDerivValue = m_derivPoints[i].y;
        if (m_derivPoints[i].y > m_maxDerivValue)
            m_maxDerivValue = m_derivPoints[i].y;
    }
}

double FunctionModel::derivative(int i) const
{
    return m_derivPoints[i].y;
}
