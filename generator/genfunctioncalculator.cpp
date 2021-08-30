#include "genfunctioncalculator.h"
#include <limits>
#include <QElapsedTimer>
#include <QVector>

#include <QtMath>

GenFunctionCalculator::GenFunctionCalculator(GenParameters *params)
{
    m_params = params;
    unsigned long long int length = params->length();

    unsigned int numThreads = static_cast<unsigned int>(QThread::idealThreadCount());

    unsigned long long int interval = length / numThreads;


    for (unsigned int i = 0; i < numThreads - 1; i++) {
        m_tmpThread = new GenFunctionCalculatorThread(m_params,
                                                      i * interval,
                                                      (i+1)* interval);
        m_threads.push_back(m_tmpThread);
        connect(m_tmpThread, SIGNAL(finished()),
                m_tmpThread, SLOT(deleteLater()));
        m_tmpThread->start();
    }

    m_tmpThread = new GenFunctionCalculatorThread(m_params,
                                                  (numThreads - 1) * interval,
                                                  length);
    m_threads.push_back(m_tmpThread);
    connect(m_tmpThread, SIGNAL(finished()),
            m_tmpThread, SLOT(deleteLater()));
    m_tmpThread->start();

    for (unsigned int i = 0; i < numThreads; i++) {
        m_threads.at(i)->wait();
    }
}

GenFunctionCalculatorThread::GenFunctionCalculatorThread(GenParameters *params,
                                                         unsigned long long first,
                                                         unsigned long long last)
{
    m_params = params;
    m_first = first;
    m_last = last;



#if defined(Q_OS_LINUX) && !defined(Q_OS_ANDROID)

    symbol_table.add_function(
                "powerint",
                [](double v0, double v1, double v2) -> double
    {

        int a = (int) v1;
        int b = (int) v2;

        int d = __gcd(a, b);

        a = a / d;
        b = b / d;

        double ratio = (double) a / b;

        int sign = 1;
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

    symbol_table.add_function(
                "power",
                [](double v0, double v1) -> double
    {

        QString n = QString::number(v1);
        int position = n.indexOf(".");
        int count;

        if (position == -1)
            return pow(v0, v1);
        else
            n = n.right(n.length() - position - 1);

        count = n.size();
        int b = pow(10, count);

        int a = (int) (v1 * b);

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

    symbol_table.add_variable("x", m_x);
    symbol_table.add_constant("pi", M_PI);
    symbol_table.add_constant("e", M_E);
    symbol_table.add_constants();

    parser_expression.register_symbol_table(symbol_table);
#else
    m_fparser.AddFunction("powerint", powerint, 3);
#endif
}

void GenFunctionCalculatorThread::run()
{
    double start = m_params->start();
    double step = m_params->step();
    double *functionValues = m_params->functionValues();
    bool *validValues = m_params->validValues();
    double result = 0;
    unsigned long long int i = 0;

#if defined(Q_OS_LINUX) && !defined(Q_OS_ANDROID)

    QString expression = m_params->expression();
    std::string exp = expression.toStdString();

    typedef exprtk::parser<double>::settings_t settings_t;

    std::size_t compile_options = settings_t::e_joiner            +
            settings_t::e_commutative_check +
            settings_t::e_strength_reduction;

    parser_t parser(compile_options);
    parser.compile(exp, parser_expression);


    for (i = m_first; i < m_last; i++) {
        m_x = start + i * step;

        if (m_params->mode() == 0)
            result = parser_expression.value();
        else if (m_params->mode() == 1)
            result = exprtk::derivative(parser_expression, m_x);
        else if (m_params->mode() == 2) {
            result = exprtk::second_derivative(parser_expression, m_x);
            double Pow = pow(10.0, 2);
            result = round (result * Pow) / Pow;
        }

        if (std::isfinite(result)) {
            validValues[i] = true;

            if (result > 1 * m_params->maxY())
                result = m_params->maxY();
            if (result < 1 * m_params->minY())
                result = m_params->minY();

            functionValues[i] = result;
        }
        else {
            validValues[i] = false;
            functionValues[i] = 0;
        }
    }


#else
    QString expression = m_params->expression();
    std::string exp = expression.toStdString();
    m_fparser.AddConstant("pi", M_PI);
    m_fparser.AddConstant("e", M_E);
    m_fparser.Parse(exp, "x");

    double vals[] = { 0 };
    int res = 0;

    for (i = m_first; i < m_last; i++) {
        m_x = start + i * step;

        vals[0] = m_x;

        if (m_params->mode() == 0) {
            result = m_fparser.Eval(vals);
            res = m_fparser.EvalError();
        } else if (m_params->mode() == 1) {

            const double h = 0.00000001;
            const double h2 = 2 * h;

            double y0 = m_fparser.Eval(vals);
            res = m_fparser.EvalError();
            double x = m_x + h;
            vals[0] = x;
            double y1 = m_fparser.Eval(vals);
            x = m_x - h;
            vals[0] = x;
            double y2 = m_fparser.Eval(vals);
            x = m_x - h2;
            vals[0] = x;
            double y3 = m_fparser.Eval(vals);

            result = (-y0 + 8 * (y1 - y2) + y3) / (12 * h);
        } else if (m_params->mode() == 2) {

            const double h = 0.00001;
            const double h2 = 2 * h;

            vals[0] = m_x;
            double y = m_fparser.Eval(vals);
            res = m_fparser.EvalError();

            double x = m_x + h2;
            vals[0] = x;
            double y0 = m_fparser.Eval(vals);
            x = m_x + h;
            vals[0] = x;
            double  y1 = m_fparser.Eval(vals);
            x = m_x - h;
            vals[0] = x;
            double y2 = m_fparser.Eval(vals);
            x = m_x - h2;
            vals[0] = x;
            double y3 = m_fparser.Eval(vals);

            result = (-y0 + 16 * (y1 + y2) - 30 * y - y3) / (12 * h * h);

            double Pow = pow(10.0, 2);
            result = round (result * Pow) / Pow;
        }

        if ( (result != result) || ( res > 0) ) {
            validValues[i] = false;
            functionValues[i] = 0;
        }
        else if (res == 0) {
            validValues[i] = true;

            if (result > m_params->maxY())
                result = m_params->maxY();
            if (result < m_params->minY())
                result = m_params->minY();

            functionValues[i] = result;
        }
    }

#endif
}

bool GenFunctionCalculatorThread::is_positive_infinite(const double &value)
{
    double max_value = std::numeric_limits<double>::max();

    return ! ( value <= max_value );
}

bool GenFunctionCalculatorThread::is_negative_infinite(const double &value)
{
    double min_value = - std::numeric_limits<double>::max();

    return ! ( min_value <= value  );
}

bool GenFunctionCalculatorThread::is_nan(const double &value)
{
    // True if NAN
    return value != value;
}

bool GenFunctionCalculatorThread::is_valid(const double &value)
{
    return ! is_positive_infinite(value) && is_negative_infinite(value) && ! is_nan(value);
}
