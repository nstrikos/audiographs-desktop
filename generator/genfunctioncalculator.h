#ifndef GENFUNCTIONCALCULATOR_H
#define GENFUNCTIONCALCULATOR_H

#include <QThread>
#include <generator/genparameters.h>
#include <vector>
using namespace std;

#ifdef Q_OS_WIN
#include "parsers/fparser/fparser.hh"
#else
#include "parsers/exprtk/exprtk.hpp"
#endif

class GenFunctionCalculatorThread : public QThread
{
public:
    GenFunctionCalculatorThread(GenParameters *params,
                                unsigned long long int first,
                                unsigned long long int last);
    void run();
private:
    GenParameters *m_params;
    unsigned long long int m_first;
    unsigned long long int m_last;
    bool is_positive_infinite( const double &value );
    bool is_negative_infinite( const double &value );
    bool is_nan( const double &value );
    bool is_valid( const double &value );

#ifdef Q_OS_WIN
    FunctionParser m_fparser;
#else
    typedef exprtk::symbol_table<double> symbol_table_t;
    typedef exprtk::expression<double>     expression_t;
    typedef exprtk::parser<double>             parser_t;

    symbol_table_t symbol_table;
    expression_t parser_expression;
#endif
    double m_x;
};


class GenFunctionCalculator : public QObject
{
public:
    GenFunctionCalculator(GenParameters *params);
private:
    GenParameters *m_params;
    vector<GenFunctionCalculatorThread*> m_threads;
    GenFunctionCalculatorThread* m_tmpThread = nullptr;
};

#endif // GENFUNCTIONCALCULATOR_H
