#ifndef GENPARAMETERS_H
#define GENPARAMETERS_H

#include <QString>

class GenParameters
{
public:
    GenParameters(double *functionValues,
                  bool *validValues,
                  QString expression,
                  unsigned long long int length,
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
                  double fc);

    double *functionValues();
    bool *validValues();
    QString expression();
    double start();
    double step();
    unsigned long long length();
    double clip();
    double *cs();
    void setkf(double kf);
    double kf();
    double sampleRate();
    double *phi();
    double *modulationValues();
    void setfc(double fc);
    double fc();

    double minY() const;
    double maxY() const;

    int mode() const;

private:
    double *m_functionValues;
    bool *m_validValues;
    QString m_expression;
    double m_start;
    double m_step;
    double m_minY;
    double m_maxY;
    unsigned long long int m_length;
    double m_clip;
    int m_mode;
    double *m_cs;
    double m_kf;
    double m_sampleRate;
    double *m_phi;
    double *m_modulationValues;
    double m_fc;
};

#endif // GENPARAMETERS_H
