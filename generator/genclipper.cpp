#include "genclipper.h"
#include <math.h>

GenAverageThread::GenAverageThread(GenParameters *params,
                                   unsigned long long first,
                                   unsigned long long last)
{
    m_params = params;
    m_first = first;
    m_last = last;
}

void GenAverageThread::run()
{
    unsigned long long int i;
    double *functionValues = m_params->functionValues();
    double sum = 0.0;
    for (i = m_first; i < m_last; i++)
        sum += abs(functionValues[i]);
    m_sum = sum;
}

double GenAverageThread::sum()
{
    return m_sum;
}

GenClipperThread::GenClipperThread(GenParameters *params,
                                   double avg,
                                   unsigned long long first,
                                   unsigned long long last)
{
    m_params = params;
    m_avg = avg;
    m_first = first;
    m_last = last;
}

void GenClipperThread::run()
{
    unsigned long long int i;
    double *functionValues = m_params->functionValues();
    double factor = m_params->clip();
    for ( i = m_first; i < m_last; i++) {
        if (functionValues[i] > m_avg * factor)
            functionValues[i] = m_avg * factor;
        if (functionValues[i] < -m_avg * factor)
            functionValues[i] = -m_avg * factor;
    }
}

GenClipper::GenClipper(GenParameters *params)
{
    m_params = params;
}

void GenClipper::clip()
{
    unsigned long long int length = m_params->length();
    double average = avg();
    unsigned int numThreads = static_cast<unsigned int>(QThread::idealThreadCount());

    unsigned long long int interval = length / numThreads;

    for (unsigned int i = 0; i < numThreads - 1; i++) {
        m_clipperTmpThread = new GenClipperThread(m_params,
                                                  average,
                                                  i * interval,
                                                  (i+1)* interval);
        m_clipperThreads.push_back(m_clipperTmpThread);
        connect(m_clipperTmpThread, SIGNAL(finished()),
                m_clipperTmpThread, SLOT(deleteLater()));
        m_clipperTmpThread->start();
    }

    m_clipperTmpThread = new GenClipperThread(m_params,
                                              average,
                                              (numThreads - 1) * interval,
                                              length);
    m_clipperThreads.push_back(m_clipperTmpThread);
    connect(m_clipperTmpThread, SIGNAL(finished()),
            m_clipperTmpThread, SLOT(deleteLater()));
    m_clipperTmpThread->start();

    for (unsigned int i = 0; i < numThreads; i++) {
        m_clipperThreads.at(i)->wait();
    }
}

double GenClipper::avg()
{
    unsigned long long int length = m_params->length();
    unsigned int numThreads = static_cast<unsigned int>(QThread::idealThreadCount());

    unsigned long long int interval = length / numThreads;

    for (unsigned int i = 0; i < numThreads - 1; i++) {
        m_avgTmpThread = new GenAverageThread(m_params,
                                           i * interval,
                                           (i+1)* interval);
        m_avgThreads.push_back(m_avgTmpThread);
        connect(m_avgTmpThread, SIGNAL(finished()),
                m_avgTmpThread, SLOT(deleteLater()));
        m_avgTmpThread->start();
    }

    m_avgTmpThread = new GenAverageThread(m_params,
                                       (numThreads - 1) * interval,
                                       length);
    m_avgThreads.push_back(m_avgTmpThread);
    connect(m_avgTmpThread, SIGNAL(finished()),
            m_avgTmpThread, SLOT(deleteLater()));
    m_avgTmpThread->start();

    for (unsigned int i = 0; i < numThreads; i++) {
        m_avgThreads.at(i)->wait();
    }

    double sum = 0.0;
    for (unsigned int i = 0; i < numThreads; i++) {
        sum += m_avgThreads.at(i)->sum();
    }

    return sum / length;
}
