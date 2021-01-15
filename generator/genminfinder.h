#ifndef GENMINFINDER_H
#define GENMINFINDER_H

#include <QObject>
#include <QThread>
#include <generator/genparameters.h>
#include <vector>
using namespace std;

class GenMinThread : public QThread
{
public:
    GenMinThread(GenParameters *params,
                     unsigned long long int first,
                     unsigned long long int last);
    void run();
    double min();
    double tmin();
private:
    GenParameters *m_params;
    double* m_functionValues;
    bool* m_validValues;
    unsigned long long int m_first;
    unsigned long long int m_last;
    double m_min;
    double m_tmin;
};

class GenMinOffsetThread : public QThread
{
public:
    GenMinOffsetThread(GenParameters *params,
                     double min,
                     unsigned long long int first,
                     unsigned long long int last);
    void run();
private:
    GenParameters *m_params;
    double m_min;
    unsigned long long int m_first;
    unsigned long long int m_last;
};


class GenMinFinder : public QObject
{
public:
    GenMinFinder(GenParameters *params);
    void minOffset();
private:
    GenParameters *m_params;
    double m_min;
    vector<GenMinThread*> m_minThreads;
    GenMinThread* m_minTmpThread = nullptr;
    vector<GenMinOffsetThread*> m_offsetThreads;
    GenMinOffsetThread* m_offsetTmpThread = nullptr;
    double min();
};

#endif // GENMINFINDER_H
