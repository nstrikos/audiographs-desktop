#ifndef GENMAXFINDER_H
#define GENMAXFINDER_H

#include <QObject>
#include <QThread>
#include <generator/genparameters.h>
#include <vector>
using namespace std;

class GenMaxThread : public QThread
{
public:
    GenMaxThread(GenParameters *params,
                     unsigned long long int first,
                     unsigned long long int last);
    void run();
    double max();
    double tmax();
private:
    GenParameters *m_params;
    unsigned long long int m_first;
    unsigned long long int m_last;
    double m_max;
    double m_tmax;
};

class GenMaxFinder : public QObject
{
public:
    GenMaxFinder(GenParameters *params);
    double max();
private:
    GenParameters *m_params;
    //double m_max;
    vector<GenMaxThread*> m_maxThreads;
    GenMaxThread* m_maxTmpThread = nullptr;
};

#endif // GENMAXFINDER_H
