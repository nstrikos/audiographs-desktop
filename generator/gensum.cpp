#include "gensum.h"

GenSum::GenSum(GenParameters *params)
{
    m_params = params;
}

void GenSum::sum()
{
    double *functionValues = m_params->functionValues();
    double *cs = m_params->cs();
    double kf = m_params->kf();
    double sampleRate = m_params->sampleRate();

    cs[0] = 0.0;

    for (unsigned long long int i = 1; i < m_params->length(); i++) {
        cs[i] = cs[i-1] + kf * functionValues[i] * 1 / sampleRate;
    }
}
