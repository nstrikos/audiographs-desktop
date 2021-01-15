#ifndef AUDIOENGINE_H
#define AUDIOENGINE_H

#include <QAudioOutput>
#include <QAudio>
#include <QDebug>
#include <QObject>
#include "generator/generator.h"

const int channelCount = 1;
const int sampleSize = 16;
const QString codec = "audio/pcm";

const int minDuration = 8;
const int maxDuration = 120;
const int minimumAllowedFmin = 200;
const int maximumAllowedFmin = 4000;
const int minimumAllowedFmax = 400;
const int maximumAllowedFmax = 8000;

class AudioEngine : public QObject
{
    Q_OBJECT

public:
    AudioEngine(QString expression, double m_start, double m_end, double minY, double maxY, int seconds, int fmin, int fmax, int mode);
    ~AudioEngine();
    Q_INVOKABLE void createAudioOutput();
    Q_INVOKABLE void stop();

    int getFmin() const;
    int getFmax() const;

signals:
    void finished();

private slots:
    void stateChanged(QAudio::State state);

private:
    void resetAudioOutput();
    void resetGenerator();
    void setDevice();
    void setFormat();
    void checkParameters();
    QAudioOutput *audioOutput;
    QAudioDeviceInfo device;
    QAudioFormat format;
    Generator *generator;
    int seconds;
    int fmax;
    int fmin;
    QString m_expression;
    double m_start;
    double m_end;
    double m_minY;
    double m_maxY;
    double m_mode;
};

#endif // AUDIOENGINE_H
