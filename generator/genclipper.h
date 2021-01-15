#ifndef GENAVERAGE_H
#define GENAVERAGE_H

#include <QObject>
#include <QThread>
#include <generator/genparameters.h>
#include <vector>
using namespace std;

class GenAverageThread : public QThread
{
public:
    GenAverageThread(GenParameters *params,
                     unsigned long long int first,
                     unsigned long long int last);
    void run();
    double sum();
private:
    GenParameters *m_params;
    unsigned long long int m_first;
    unsigned long long int m_last;
    double m_sum;
};

class GenClipperThread : public QThread
{
public:
    GenClipperThread(GenParameters *params,
                     double avg,
                     unsigned long long int first,
                     unsigned long long int last);
    void run();
private:
    GenParameters *m_params;
    double m_avg;
    unsigned long long int m_first;
    unsigned long long int m_last;
};


class GenClipper : public QObject
{
public:
    GenClipper(GenParameters *params);
    void clip();
private:
    GenParameters *m_params;
    vector<GenAverageThread*> m_avgThreads;
    GenAverageThread* m_avgTmpThread = nullptr;
    vector<GenClipperThread*> m_clipperThreads;
    GenClipperThread* m_clipperTmpThread = nullptr;
    double avg();
};

#endif // GENAVERAGE_H
