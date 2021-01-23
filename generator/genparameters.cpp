#include "genparameters.h"

GenParameters::GenParameters(double *functionValues,
                             bool *validValues,
                             QString expression,
                             unsigned long long length,
                             double start,
                             double minY,
                             double maxY,
                             double step,
                             double clip,
                             int mode,
                             double *cs,
                             double kf,
                             double sampleRate,
                             double *phi,
                             double *modulationValues,
                             double fc)
{
    m_functionValues = functionValues;
    m_validValues = validValues;
    m_expression = expression;
    m_length = length;
    m_start = start;
    m_minY = minY;
    m_maxY = maxY;
    m_step = step;
    m_clip = clip;
    m_mode = mode;
    m_cs = cs;
    m_kf = kf;
    m_sampleRate = sampleRate;
    m_phi = phi;
    m_modulationValues = modulationValues;
    m_fc = fc;
}

double *GenParameters::functionValues()
{
    return m_functionValues;
}

bool *GenParameters::validValues()
{
    return m_validValues;
}

QString GenParameters::expression()
{
    return m_expression;
}

double GenParameters::start()
{
    return m_start;
}

double GenParameters::step()
{
    return m_step;
}

unsigned long long GenParameters::length()
{
    return m_length;
}

double GenParameters::clip()
{
    return m_clip;
}

double *GenParameters::cs()
{
    return m_cs;
}

void GenParameters::setkf(double kf)
{
    m_kf = kf;
}

double GenParameters::kf()
{
    return m_kf;
}

double GenParameters::sampleRate()
{
    return m_sampleRate;
}

double *GenParameters::phi()
{
    return m_phi;
}

double *GenParameters::modulationValues()
{
    return m_modulationValues;
}

void GenParameters::setfc(double fc)
{
    m_fc = fc;
}

double GenParameters::fc()
{
    return m_fc;
}

double GenParameters::minY() const
{
    return m_minY;
}

double GenParameters::maxY() const
{
    return m_maxY;
}

int GenParameters::mode() const
{
    return m_mode;
}
