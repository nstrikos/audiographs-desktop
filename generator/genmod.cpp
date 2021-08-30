#include "genmod.h"
#include <qmath.h>

GenMod::GenMod(GenParameters *params)
{
    m_params = params;
}

void GenMod::mod()
{
    unsigned int numThreads = static_cast<unsigned int>(QThread::idealThreadCount());

    unsigned long long int length = m_params->length();

    unsigned long long int interval = length / numThreads;


    for (unsigned int i = 0; i < numThreads - 1; i++) {
        m_tmpThread = new GenModThread(m_params,
                                       i * interval,
                                       (i+1)* interval);
        m_threads.push_back(m_tmpThread);
        connect(m_tmpThread, SIGNAL(finished()),
                m_tmpThread, SLOT(deleteLater()));
        m_tmpThread->start();
    }

    m_tmpThread = new GenModThread(m_params,
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

GenModThread::GenModThread(GenParameters *params,
                           unsigned long long first,
                           unsigned long long last)
{
    m_params = params;
    m_first = first;
    m_last = last;
}

void GenModThread::run()
{
    qreal ph;
    unsigned long long int i = 0;
    double fc = m_params->fc();
    double sampleRate = m_params->sampleRate();
    double *phi = m_params->phi();
    double *modulationValues = m_params->modulationValues();

    bool *validValues = m_params->validValues();

    for (i = m_first; i < m_last; i++) {
        ph = 2 * M_PI * fc * i / sampleRate + phi[i];
        modulationValues[i] = qSin(ph);

        if (validValues[i] == false) {
            std::normal_distribution<double> dist(m_mean, m_stddev);
            modulationValues[i] = 0.0002 * dist(m_generator);
        }
    }
}
