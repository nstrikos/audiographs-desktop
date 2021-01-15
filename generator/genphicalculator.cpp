#include "genphicalculator.h"
#include <math.h>

#include <QtMath>

GenPhiCalculator::GenPhiCalculator(GenParameters *params)
{
    m_params = params;
    unsigned long long int length = m_params->length();

    unsigned int numThreads = static_cast<unsigned int>(QThread::idealThreadCount());

    unsigned long long int interval = length / numThreads;


    for (unsigned int i = 0; i < numThreads - 1; i++) {
        m_tmpThread = new GenPhiThread(m_params,
                                       i * interval,
                                       (i+1)* interval);
        m_threads.push_back(m_tmpThread);
        connect(m_tmpThread, SIGNAL(finished()),
                m_tmpThread, SLOT(deleteLater()));
        m_tmpThread->start();
    }

    m_tmpThread = new GenPhiThread(m_params,
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

GenPhiThread::GenPhiThread(GenParameters *params,
                           unsigned long long first,
                           unsigned long long last)
{
    m_params = params;
    m_first = first;
    m_last = last;

}

void GenPhiThread::run()
{
    unsigned long long int i = 0;
    double *phi = m_params->phi();
    double *cs = m_params->cs();
    for (i = m_first; i < m_last; i++) {
        phi[i] = 2 * M_PI * cs[i];
    }
}
