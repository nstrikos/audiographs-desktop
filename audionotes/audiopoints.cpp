#include "audiopoints.h"
#include <qmath.h>
#include <random>

//#include <QDebug>

AudioPoints::AudioPoints()
{
    timer = nullptr;
    audioOutput = nullptr;
    m_isPlaying = false;
}

AudioPoints::~AudioPoints()
{
    if (timer != nullptr)
        delete timer;
    if (audioOutput != nullptr)
        delete audioOutput;
}

void AudioPoints::startAudio()
{
    instrument++;
    if (instrument > 3)
        instrument = 0;
    audioPlaying = true;
    initializeAudio();
    writeMoreData();
}

void AudioPoints::stopAudio()
{
    if (audioOutput != nullptr) {
        audioOutput->stop();
        delete audioOutput;
        audioOutput = nullptr;
        timer->stop();
    }
    audioPlaying = false;
    //    setFreq(0);
}

void AudioPoints::setFreq(double freq, bool useNotes, bool n, double ratio)
{
    xx = freq;
    m_n = n;
    //m_n = false;
    m_ratio = ratio;
    m_isPlaying = true;

    xx = xx / 2;


    if (useNotes) {
        if ( xx == 0)
            xx = 0;
        else if ( xx < 110.0)
            xx = 110.0;
        else if ( xx >= 110.0 && xx <  116.54) // A2
            xx = 110;
        else if ( xx >= 116.54 && xx < 123.47) //A#2
            xx = 116.54;
        else if ( xx >= 123.47 && xx < 130.81) //B2
            xx = 123.47;
        else if ( xx >= 130.81 && xx < 138.59) //C3
            xx = 130.81;
        else if ( xx >= 138.59 && xx < 146.83) //C#3
            xx = 138.59;
        else if ( xx >= 146.83 && xx < 155.56) //D3
            xx = 146.83;
        else if ( xx >= 155.56 && xx < 164.81) //D#3
            xx = 155.56;
        else if ( xx >= 164.81 && xx < 174.61) //E3
            xx = 164.81;
        else if ( xx >= 174.61 && xx < 185.00) //F3
            xx = 174.61;
        else if ( xx >= 185.00 && xx < 196.00) //F#3
            xx = 185.00;
        else if ( xx >= 196.00 && xx < 207.65) //G3
            xx = 196.00;
        else if ( xx >= 207.65 && xx < 220.00) //G#3
            xx = 207.65;
        else if ( xx >= 220.0 && xx <  233.08) // A3
            xx = 220.0;
        else if ( xx >= 233.08 && xx < 246.94) //A#3
            xx = 233.08;
        else if ( xx >= 246.94 && xx < 261.63) //B3
            xx = 246.94;
        else if ( xx >= 261.63 && xx < 277.18) //C4
            xx = 261.63;
        else if ( xx >= 277.18 && xx < 293.66) //C#4
            xx = 277.18;
        else if ( xx >= 293.66 && xx < 311.13) //D4
            xx = 293.66;
        else if ( xx >= 311.13 && xx < 329.63) //D#4
            xx = 311.13;
        else if ( xx >= 329.63 && xx < 349.23) //E4
            xx = 329.63;
        else if ( xx >= 349.23 && xx < 369.99) //F4
            xx = 349.23;
        else if ( xx >= 369.99 && xx < 392.00) //F#4
            xx = 369.99;
        else if ( xx >= 392.00 && xx < 415.30) //G4
            xx = 392.00;
        else if ( xx >= 415.30 && xx < 440.00) //G#4
            xx = 415.30;
        else if ( xx >= 440.00 && xx < 466.16) //A4
            xx = 440.0;
        else if ( xx >= 466.16 && xx < 493.88) //A#4
            xx = 466.16;
        else if ( xx >= 493.88 && xx < 523.25) //B4
            xx = 493.88;
        else if ( xx >= 523.25 && xx < 554.37) //C5
            xx = 523.25;
        else if ( xx >= 554.37 && xx < 587.33) //C#5
            xx = 554.37;
        else if ( xx >= 587.33 && xx < 622.25) //D5
            xx = 587.33;
        else if ( xx >= 622.25 && xx < 659.25) //D#5
            xx = 622.25;
        else if ( xx >= 659.25 && xx < 698.46) //E5
            xx = 659.25;
        else if ( xx >= 698.46 && xx < 739.99) //F5
            xx = 698.46;
        else if ( xx >= 739.99 && xx < 783.99) //F#5
            xx = 739.99;
        else if ( xx >= 783.99 && xx < 830.61) //G5
            xx = 783.99;
        else if ( xx >= 830.61 && xx < 880.00) //G#5
            xx = 830.61;
        else if ( xx >= 880.00 && xx < 932.33) //A5
            xx = 880.00;
        else if ( xx >= 932.33 && xx < 987.77) //A#5
            xx = 932.33;
        else if ( xx >= 987.77 && xx < 1046.50) //B5
            xx = 987.77;
        else if ( xx >= 1046.50 && xx < 1108.73) //C6
            xx = 1046.50;
        else if ( xx >= 1108.73 && xx < 1174.66) //C#6
            xx =  1108.73;
        else if ( xx >= 1174.66 && xx < 1244.51) //D6
            xx = 1174.66;
        else if ( xx >= 1244.51 && xx < 1318.51) //D#6
            xx = 1244.51;
        else if ( xx >= 1318.51 && xx < 1396.91) //E6
            xx = 1318.51;
        else if ( xx >= 1396.91 && xx < 1479.98) //F6
            xx = 1396.91;
        else if ( xx >= 1479.98 && xx <  1567.98) //F#6
            xx = 1479.98;
        else if ( xx >= 1567.98 && xx < 1661.22) //G6
            xx = 1567.98;
        else if ( xx >= 1661.22 && xx < 1760.00) //G#6
            xx = 1661.22;
        else if ( xx >= 1760.00 && xx < 1864.66) //A6
            xx = 1760.00;
        else if ( xx >= 1864.66 && xx < 1975.53) //A#6
            xx = 1864.66;
        else if ( xx >= 1975.53 && xx < 2093.00) //B6
            xx = 1975.53;
        else if ( xx >= 2093.00 && xx < 2217.46) //C7
            xx = 2093.00;
        else if ( xx >= 2217.46 && xx < 2349.32) //C#7
            xx = 2217.46;
        else if ( xx >= 2349.32 && xx < 2489.02) //D7
            xx = 2349.32;
        else if ( xx >= 2489.02 && xx < 2637.02) //D#7
            xx = 2489.02;
        else if ( xx >= 2637.02 && xx < 2793.83) //E7
            xx = 2637.02;
        else if ( xx >= 2793.83 && xx < 2959.96) //F7
            xx = 2793.83;
        else if ( xx >= 2959.96)// && xx < 3135.96) //F#7
            xx = 2959.96;
        //        else if ( xx >= 3135.96 && xx < 3322.44) //G7
        //            xx = 3135.96;
        //        else if ( xx >= 3322.44)// && xx <= 3520.00) //A7
        //            xx = 3322.44;
    }

    m_time = 0;
    if (audioPlaying == false)
        startAudio();
}

void AudioPoints::initializeAudio()
{
    deviceinfo = QAudioDeviceInfo::defaultOutputDevice();
    audioOutput = nullptr;

    format.setSampleRate(DataFrequencyHz);
    format.setChannelCount(ChannelCount);
    format.setSampleSize(SampleSize);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::SignedInt);

    QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
    if (!info.isFormatSupported(format)) {
        format = info.nearestFormat(format);
    }
    audioOutput = new QAudioOutput(deviceinfo, format, this);
    audioOutput->setBufferSize(BufferSize);
    timer = new QTimer;
    timer->setTimerType(Qt::PreciseTimer);
    connect(timer, SIGNAL(timeout()), this, SLOT(writeMoreData()));
    m_time = 0;
    timer->start(TimerMSeconds);
    m_sum = 0;
    m_sum2 = 0;
    m_phi = 0;
    m_phi2 = 0;
    auIObuffer = audioOutput->start();
#ifdef Q_OS_WIN
    //    auIObuffer = audioOutput->start(); //In windows calling audioOutput->start
    //for second time gives better results
#endif
}

void AudioPoints::writeMoreData()
{
    if (m_isPlaying == false)
        return;
    m_time += 5;
    if (m_time > duration) {
        m_isPlaying = false;
        emit finished();
        return;
    }
    int emptyBytes = audioOutput->bytesFree();
    //if (emptyBytes > BufferSize) emptyBytes = BufferSize;// Check how many empty bytes are in the device buffer
    int periodSize = audioOutput->periodSize(); // Check the ideal chunk size, in bytes

    int chunks = emptyBytes/periodSize;

    while (chunks){

        for (int sample=0; sample<periodSize/2; sample += 2) {
            if (xx != xx)
                xx = 0;

            m_sum += xx/DataFrequencyHz;
            m_sum2 += xx2/DataFrequencyHz;
            m_phi = m_sum * 2 * M_PI;
            m_phi2 = m_sum2 * 2 * M_PI;

            //            m++;
            //            m_2++;
            //            if (m > DataFrequencyHz / 4)
            //                m = 0;
            //            float time = (float) m/DataFrequencyHz ;

            //            if (m_2 > DataFrequencyHz / 4)
            //                m_2 = 0;
            //            float time2 = (float)m_2/DataFrequencyHz;

            double x;


            if (m_n) {
                m_f0 = 1;
                x = m_f0 * qCos(m_phi);
            } else {
                m_f0 = 10;
                m_f1 = 35;
                m_f2 = 5;
                m_f3 = 5;
                m_f4 = 5;
                m_f10 = 0;

                x = 1/(m_f0 + m_f1 + m_f2 + m_f3 + m_f4 + m_f5 + m_f6 + m_f7 + m_f8 + m_f9 + m_f10) *
                        (m_f0 * qSin(m_phi) +
                         m_f1 * qSin(2 * m_phi) +
                         m_f2 * qSin(3 * m_phi) +
                         m_f3 * qSin(4 * m_phi) +
                         m_f4 * qSin(5 * m_phi) +
                         m_f5 * qSin(6 * m_phi) +
                         m_f6 * qSin(7 * m_phi) +
                         m_f7 * qSin(8 * m_phi) +
                         m_f8 * qSin(9 * m_phi) +
                         m_f9 * qSin(10 * m_phi) +
                         m_f10 * qSin(11 * m_phi));
            }
            //            x = x / 4;

            //            if (time > 0.05)
            //                time = 0;

            //            if (time2 > 0.1)
            //                time2 = 0;

            //            float x2 = qSin(2 * M_PI * 4000 * time);
            //            float x3 = qSin(2 * M_PI * 200 * time2);

            //            float x_x = 1.0 * x + 0.0 * x2 + 0.0 * x3;

            if (xx == 0) {
                std::normal_distribution<double> dist(m_mean, m_stddev);
                x = 0.0002 * dist(m_generator);
            }

            signed short value = static_cast<signed short>(x * 32767);

            aubuffer[sample] = value;
            aubuffer[sample + 1] = value;

            //            if (xx == 0) {
            //                std::normal_distribution<double> dist(m_mean, m_stddev);
            //                value = 0.001 * dist(m_generator);
            //                aubuffer[sample] = value;
            //                aubuffer[sample + 1] = value;
            //            } else {
            //                aubuffer[sample] = value;
            //                aubuffer[sample + 1] = value;
            //                //                if (m_ratio < 0.5) {
            //                //                    aubuffer[sample] = value * m_ratio * 2;
            //                //                    aubuffer[sample + 1] = 0;
            //                //                } else {
            //                //                    aubuffer[sample] = 0;
            //                //                    aubuffer[sample + 1] = (-2 * m_ratio + 2) * value ;
            //                //                }
            //            }
        }

        auIObuffer->write((const char*) &aubuffer[0], periodSize);
        --chunks;
    }
}

double AudioPoints::f10() const
{
    return m_f10;
}

void AudioPoints::setF10(double f10)
{
    m_f10 = f10;
}

double AudioPoints::f9() const
{
    return m_f9;
}

void AudioPoints::setF9(double f9)
{
    m_f9 = f9;
}

double AudioPoints::f8() const
{
    return m_f8;
}

void AudioPoints::setF8(double f8)
{
    m_f8 = f8;
}

double AudioPoints::f7() const
{
    return m_f7;
}

void AudioPoints::setF7(double f7)
{
    m_f7 = f7;
}

double AudioPoints::f6() const
{
    return m_f6;
}

void AudioPoints::setF6(double f6)
{
    m_f6 = f6;
}

double AudioPoints::f5() const
{
    return m_f5;
}

void AudioPoints::setF5(double f5)
{
    m_f5 = f5;
}

double AudioPoints::f4() const
{
    return m_f4;
}

void AudioPoints::setF4(double f4)
{
    m_f4 = f4;
}

double AudioPoints::f3() const
{
    return m_f3;
}

void AudioPoints::setF3(double f3)
{
    m_f3 = f3;
}

double AudioPoints::f2() const
{
    return m_f2;
}

void AudioPoints::setF2(double f2)
{
    m_f2 = f2;
}

double AudioPoints::f1() const
{
    return m_f1;
}

void AudioPoints::setF1(double f1)
{
    m_f1 = f1;
}

double AudioPoints::f0() const
{
    return m_f0;
}

void AudioPoints::setF0(double f0)
{
    m_f0 = f0;
}
