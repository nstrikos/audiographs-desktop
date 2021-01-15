#ifndef GENPHICALCULATOR_H
#define GENPHICALCULATOR_H


#include <QThread>
#include <generator/genparameters.h>
#include <vector>
using namespace std;



class GenPhiThread : public QThread
{
public:
    GenPhiThread(GenParameters *params,
                 unsigned long long int first,
                 unsigned long long int last);
    void run();
private:
    GenParameters *m_params;
    unsigned long long int m_first;
    unsigned long long int m_last;
};


class GenPhiCalculator : public QObject
{
public:
    GenPhiCalculator(GenParameters *params);
private:
    GenParameters *m_params;
    vector<GenPhiThread*> m_threads;
    GenPhiThread* m_tmpThread = nullptr;
};

#endif // GENPHICALCULATOR_H
