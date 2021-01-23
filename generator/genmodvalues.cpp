#include "genmodvalues.h"

GenModValues::GenModValues(double *modulationValues,
                           QString expression,
                           double start,
                           double end,
                           double minY,
                           double maxY,
                           unsigned long long int timeLength,
                           int fmin,
                           int fmax,
                           int sampleRate,
                           int mode)
{
    m_modulationValues = modulationValues;
    m_expression = expression;
    m_start = start;
    m_end = end;
    m_minY = minY;
    m_maxY = maxY;
    m_timeLength = timeLength;
    m_fmin = fmin;
    m_fmax = fmax;
    m_sampleRate = sampleRate;
    m_mode = mode;
}

double *GenModValues::modulationValues()
{
    double step = (m_end - m_start) / (m_timeLength);
    double max;

    double *functionValues = new double[m_timeLength];
    bool *validValues = new bool[m_timeLength];
    double *cs = new double[m_timeLength];
    double *phi = new double[m_timeLength];

    int fc = m_fmin;
    int fdev = m_fmax - m_fmin;


    double clip = 10.0;
    double kf = 0.0;

    GenParameters *params = new GenParameters(functionValues,
                                              validValues,
                                              m_expression,
                                              m_timeLength,
                                              m_start,
                                              m_minY,
                                              m_maxY,
                                              step,
                                              clip,
                                              m_mode,
                                              cs,
                                              kf,
                                              m_sampleRate,
                                              phi,
                                              m_modulationValues,
                                              fc);

    GenFunctionCalculator *functionCalculator = new GenFunctionCalculator(params);

    GenClipper *genClipper = new GenClipper(params);
    //genClipper->clip();

    GenMinFinder *minFinder = new GenMinFinder(params);
    minFinder->minOffset();

    GenMaxFinder *maxFinder = new GenMaxFinder(params);
    max = maxFinder->max();

    if (abs(max) < 1e-8) {
        params->setfc((m_fmax + m_fmin) / 2.0);
        params->setkf(0);
    } else {
        params->setkf(fdev / max);
    }

    GenSum *genSum = new GenSum(params);
    genSum->sum();

    GenPhiCalculator *phiCalculator = new GenPhiCalculator(params);

    GenMod *genMod = new GenMod(params);
    genMod->mod();

    delete[] functionValues;
    delete[] validValues;
    delete[] cs;
    delete[] phi;

    functionValues = nullptr;
    validValues = nullptr;
    cs = nullptr;
    phi = nullptr;

    delete params;
    delete functionCalculator;
    delete genClipper;
    delete minFinder;
    delete maxFinder;
    delete genSum;
    delete phiCalculator;
    delete genMod;

    return m_modulationValues;
}
