#include "genminfinder.h"

GenMinThread::GenMinThread(GenParameters *params, unsigned long long first, unsigned long long last)
{
    m_params = params;
    m_functionValues = m_params->functionValues();
    m_validValues = m_params->validValues();
    m_first = first;
    m_last = last;
}

void GenMinThread::run()
{
    unsigned long long int i;

    m_min = std::numeric_limits<double>::max();//m_functionValues[m_first];
    m_tmin = m_params->start() + m_first * m_params->step();

    for (i = m_first; i < m_last; i++) {
        if (!m_validValues[i])
            continue;
        if (m_functionValues[i] < m_min) {
            m_min = m_functionValues[i];
            m_tmin = m_params->start() + i * m_params->step();
        }
    }
}

double GenMinThread::min()
{
    return m_min;
}

double GenMinThread::tmin()
{
    return m_tmin;
}

GenMinOffsetThread::GenMinOffsetThread(GenParameters *params,
                                       double min,
                                       unsigned long long first,
                                       unsigned long long last)
{
    m_params = params;
    m_min = min;
    m_first = first;
    m_last = last;
}

void GenMinOffsetThread::run()
{
    unsigned long long int i;
    double *functionValues = m_params->functionValues();

    for(i = m_first; i < m_last; i++) {
        functionValues[i] = functionValues[i] - m_min;
    }
}

GenMinFinder::GenMinFinder(GenParameters *params)
{
    m_params = params;
}

void GenMinFinder::minOffset()
{
    m_min = min();

    unsigned long long int length = m_params->length();
    unsigned int numThreads = static_cast<unsigned int>(QThread::idealThreadCount());

    unsigned long long int interval = length / numThreads;

    for (unsigned int i = 0; i < numThreads - 1; i++) {
        m_offsetTmpThread = new GenMinOffsetThread(m_params,
                                                   m_min,
                                                   i * interval,
                                                   (i+1)* interval);
        m_offsetThreads.push_back(m_offsetTmpThread);
        connect(m_offsetTmpThread, SIGNAL(finished()),
                m_offsetTmpThread, SLOT(deleteLater()));
        m_offsetTmpThread->start();
    }

    m_offsetTmpThread = new GenMinOffsetThread(m_params,
                                               m_min,
                                               (numThreads - 1) * interval,
                                               length);
    m_offsetThreads.push_back(m_offsetTmpThread);
    connect(m_offsetTmpThread, SIGNAL(finished()),
            m_offsetTmpThread, SLOT(deleteLater()));
    m_offsetTmpThread->start();

    for (unsigned int i = 0; i < numThreads; i++) {
        m_offsetThreads.at(i)->wait();
    }
}

double GenMinFinder::min()
{
    unsigned int numThreads = static_cast<unsigned int>(QThread::idealThreadCount());

    unsigned long long int length = m_params->length();

    unsigned long long int interval = length / numThreads;

    for (unsigned int i = 0; i < numThreads - 1; i++) {
        m_minTmpThread = new GenMinThread(m_params,
                                          i * interval,
                                          (i+1)* interval);
        m_minThreads.push_back(m_minTmpThread);
        connect(m_minTmpThread, SIGNAL(finished()),
                m_minTmpThread, SLOT(deleteLater()));
        m_minTmpThread->start();
    }

    m_minTmpThread = new GenMinThread(m_params,
                                      (numThreads - 1) * interval,
                                      length);
    m_minThreads.push_back(m_minTmpThread);
    connect(m_minTmpThread, SIGNAL(finished()),
            m_minTmpThread, SLOT(deleteLater()));
    m_minTmpThread->start();

    for (unsigned int i = 0; i < numThreads; i++) {
        m_minThreads.at(i)->wait();
    }

    double min = m_minThreads.at(0)->min();
//    double tmin = m_minThreads.at(0)->tmin();
    for (unsigned int i = 1; i < numThreads; i++) {
        if (min > m_minThreads.at(i)->min()) {
            min = m_minThreads.at(i)->min();
//            tmin = m_minThreads.at(i)->tmin();
        }
    }

    return min;
}
