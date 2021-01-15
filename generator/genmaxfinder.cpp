#include "genmaxfinder.h"

GenMaxThread::GenMaxThread(GenParameters *params, unsigned long long first, unsigned long long last)
{
    m_params = params;
    m_first = first;
    m_last = last;
}

void GenMaxThread::run()
{
    unsigned long long int i;
    double *functionValues = m_params->functionValues();
    bool *validValues = m_params->validValues();
    m_max = std::numeric_limits<double>::min();//functionValues[m_first];
    m_tmax = m_params->start() + m_first * m_params->step();

    for (i = m_first; i < m_last; i++) {
        if (!validValues[i])
            continue;
        if (functionValues[i] > m_max ) {
            m_max = functionValues[i];
            m_tmax = m_params->start() + i * m_params->step();
        }
    }
}

double GenMaxThread::max()
{
    return m_max;
}

double GenMaxThread::tmax()
{
    return m_tmax;
}

GenMaxFinder::GenMaxFinder(GenParameters *params)
{
    m_params = params;
}

double GenMaxFinder::max()
{
    unsigned int numThreads = static_cast<unsigned int>(QThread::idealThreadCount());

    unsigned long long int length = m_params->length();

    unsigned long long int interval = length / numThreads;

    for (unsigned int i = 0; i < numThreads - 1; i++) {
        m_maxTmpThread = new GenMaxThread(m_params,
                                          i * interval,
                                          (i+1)* interval);
        m_maxThreads.push_back(m_maxTmpThread);
        connect(m_maxTmpThread, SIGNAL(finished()),
                m_maxTmpThread, SLOT(deleteLater()));
        m_maxTmpThread->start();
    }

    m_maxTmpThread = new GenMaxThread(m_params,
                                      (numThreads - 1) * interval,
                                      length);
    m_maxThreads.push_back(m_maxTmpThread);
    connect(m_maxTmpThread, SIGNAL(finished()),
            m_maxTmpThread, SLOT(deleteLater()));
    m_maxTmpThread->start();

    for (unsigned int i = 0; i < numThreads; i++) {
        m_maxThreads.at(i)->wait();
    }

    double max = m_maxThreads.at(0)->max();
//    double tmax = m_maxThreads.at(0)->tmax();
    for (unsigned int i = 1; i < numThreads; i++) {
        if (max < m_maxThreads.at(i)->max()) {
            max = m_maxThreads.at(i)->max();
//            tmax = m_maxThreads.at(i)->tmax();
        }
    }

    return max;
}
