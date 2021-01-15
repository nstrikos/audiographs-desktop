#ifndef AUDIOPOINTS_H
#define AUDIOPOINTS_H

#include <QObject>
#include <QAudioDeviceInfo>
#include <QAudioOutput>
#include <qmath.h>
#include <QTimer>
#include <qendian.h>

#include <random>

const int DataFrequencyHz = 48000;
#ifdef Q_OS_WIN
const int BufferSize   = 32000;
#else
const int BufferSize = 32000;
#endif
const int ChannelCount = 2;
const int SampleSize = 16;
const int TimerMSeconds = 5;
const int duration = 1000;

class AudioPoints : public QObject
{
    Q_OBJECT
public:
    AudioPoints();
    ~AudioPoints();

public:
    void startAudio();
    Q_INVOKABLE void stopAudio();
    Q_INVOKABLE void setFreq(double freq, bool useNotes, bool n, double ratio);

    Q_PROPERTY(double f0 READ f0 WRITE setF0 NOTIFY f0Changed)
    Q_PROPERTY(double f1 READ f1 WRITE setF1 NOTIFY f1Changed)
    Q_PROPERTY(double f2 READ f2 WRITE setF2 NOTIFY f2Changed)
    Q_PROPERTY(double f3 READ f3 WRITE setF3 NOTIFY f3Changed)
    Q_PROPERTY(double f4 READ f4 WRITE setF4 NOTIFY f4Changed)
    Q_PROPERTY(double f5 READ f5 WRITE setF5 NOTIFY f5Changed)
    Q_PROPERTY(double f6 READ f6 WRITE setF6 NOTIFY f6Changed)
    Q_PROPERTY(double f7 READ f7 WRITE setF7 NOTIFY f7Changed)
    Q_PROPERTY(double f8 READ f8 WRITE setF8 NOTIFY f8Changed)
    Q_PROPERTY(double f9 READ f9 WRITE setF9 NOTIFY f9Changed)
    Q_PROPERTY(double f10 READ f10 WRITE setF10 NOTIFY f10Changed)

    double f0() const;
    void setF0(double f0);

    double f1() const;
    void setF1(double f1);

    double f2() const;
    void setF2(double f2);

    double f3() const;
    void setF3(double f3);

    double f4() const;
    void setF4(double f4);

    double f5() const;
    void setF5(double f5);

    double f6() const;
    void setF6(double f6);

    double f7() const;
    void setF7(double f7);

    double f8() const;
    void setF8(double f8);

    double f9() const;
    void setF9(double f9);

    double f10() const;
    void setF10(double f10);

private slots:
    void writeMoreData();
private:
    void initializeAudio();

    QAudioDeviceInfo deviceinfo;
    QAudioOutput* audioOutput;
    QAudioFormat format;
    QIODevice* auIObuffer;
    bool audioPlaying = false;
    signed short aubuffer[BufferSize];
    double xx;
    double xx2;
    double m_sum;
    double m_sum2;
    double m_phi;
    double m_phi2;
    int instrument = 0;
    QTimer *timer;
    int k = 0;
    int m = 0;
    int m_2 = 0;

    double m_f0 = 1.0;
    double m_f1 = 0.0;
    double m_f2 = 0.0;
    double m_f3 = 0.0;
    double m_f4 = 0.0;
    double m_f5 = 0.0;
    double m_f6 = 0.0;
    double m_f7 = 0.0;
    double m_f8 = 0.0;
    double m_f9 = 0.0;
    double m_f10 = 0.0;

    bool m_n;
    int m_time;
    double m_ratio;
    bool m_isPlaying;

    const double m_mean = 0.0;
    const double m_stddev = 100;
    std::default_random_engine m_generator;

signals:
    void f0Changed();
    void f1Changed();
    void f2Changed();
    void f3Changed();
    void f4Changed();
    void f5Changed();
    void f6Changed();
    void f7Changed();
    void f8Changed();
    void f9Changed();
    void f10Changed();
    void finished();
};

#endif // AUDIOPOINTS_H
