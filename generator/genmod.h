#ifndef GENMOD_H
#define GENMOD_H


#include <QThread>
#include <generator/genparameters.h>
#include <vector>
using namespace std;

#include <random>

class GenModThread : public QThread
{
public:
    GenModThread(GenParameters *params,
                 unsigned long long int first,
                 unsigned long long int last);
    void run();
private:
    GenParameters *m_params;
    unsigned long long int m_first;
    unsigned long long int m_last;

    const double m_mean = 0.0;
    const double m_stddev = 100;
    std::default_random_engine m_generator;
};


class GenMod : public QObject
{
public:
    GenMod(GenParameters *params);
    void mod();
private:
    GenParameters *m_params;
    vector<GenModThread*> m_threads;
    GenModThread* m_tmpThread = nullptr;
};

#endif // GENMOD_H
