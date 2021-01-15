#include "generator.h"

#include <qendian.h>
#include <qmath.h>

Generator::Generator(QAudioFormat format,
                     QString expression,
                     double start,
                     double end,
                     double minY,
                     double maxY,
                     int seconds,
                     int fmin,
                     int fmax,
                     int mode)
{
    //Initialize generator variables
    pos = 0;
    this->format = format;
    this->seconds = seconds;
    this->fmin = fmin;
    this->fmax = fmax;
    m_expression = expression;
    m_start = start;
    m_end = end;
    m_minY = minY;
    m_maxY = maxY;
    m_mode = mode;

    if (format.isValid())
    {
        //Proceed to data generation
        generateData(format, seconds);
    }
    else
    {

    }
}

Generator::~Generator()
{
    delete[] modulationValues;
    modulationValues = nullptr;
}

void Generator::start()
{
    open(QIODevice::ReadOnly);
}

void Generator::generateData(const QAudioFormat &format, int seconds)
{
    m_channelBytes = format.sampleSize() / 8;
    const int sampleBytes = format.channelCount() * m_channelBytes;

    length = (format.sampleRate() * format.channelCount() * (format.sampleSize() / 8))
            * seconds;

    Q_ASSERT(length % sampleBytes == 0);

    buffer.resize(  static_cast<int>(length) );
    unsigned char *ptr = reinterpret_cast<unsigned char *>(buffer.data());
    int sampleIndex = 0;
    int count = 0;

    computeFunction();
    while (count < (length / m_channelBytes)) {
        qreal waveformValue;
        waveformValue = modulationValues[sampleIndex];
        for (int i=0; i<format.channelCount(); ++i) {
            if (format.sampleSize() == 8 && format.sampleType() == QAudioFormat::UnSignedInt) {
                const quint8 value = static_cast<quint8>((1.0 + waveformValue) / 2 * 255);
                *reinterpret_cast<quint8*>(ptr) = value;
            } else if (format.sampleSize() == 8 && format.sampleType() == QAudioFormat::SignedInt) {
                const qint8 value = static_cast<qint8>(waveformValue * 127);
                *reinterpret_cast<quint8*>(ptr) = static_cast<quint8>(value);
            } else if (format.sampleSize() == 16 && format.sampleType() == QAudioFormat::UnSignedInt) {
                quint16 value = static_cast<quint16>((1.0 + waveformValue) / 2 * 65535);
                if (format.byteOrder() == QAudioFormat::LittleEndian)
                    qToLittleEndian<quint16>(value, ptr);
                else
                    qToBigEndian<quint16>(value, ptr);
            } else if (format.sampleSize() == 16 && format.sampleType() == QAudioFormat::SignedInt) {
                qint16 value = static_cast<qint16>(waveformValue * 32767);
                if (format.byteOrder() == QAudioFormat::LittleEndian)
                    qToLittleEndian<qint16>(value, ptr);
                else
                    qToBigEndian<qint16>(value, ptr);
            }
            ptr += m_channelBytes;
            count++;
        }
        ++sampleIndex;
    }
}

void Generator::computeFunction()
{
    unsigned long long int timeLength = static_cast<unsigned long long int> (length / m_channelBytes);

    modulationValues = new double[timeLength];

    GenModValues *genModValues = new GenModValues(modulationValues,
                                                  m_expression,
                                                  m_start,
                                                  m_end,
                                                  m_minY,
                                                  m_maxY,
                                                  timeLength,
                                                  fmin,
                                                  fmax,
                                                  format.sampleRate(),
                                                  m_mode);
    modulationValues = genModValues->modulationValues();
    delete genModValues;
}

qint64 Generator::readData(char *data, qint64 len)
{
    qint64 total = 0;
    if (!buffer.isEmpty()) {
        while ( (len - total > 0) && (pos < buffer.size()) ) {
            const qint64 chunk = qMin((buffer.size() - pos), len - total);
            memcpy(data + total, buffer.constData() + pos, chunk);
            pos = (pos + chunk);// % buffer.size();
            total += chunk;
        }
    }
    if (pos >= buffer.size())
    {
        ; //emit readComplete();
    }
    return total;
}

qint64 Generator::writeData(const char *data, qint64 len)
{
    Q_UNUSED(data);
    Q_UNUSED(len);

    return 0;
}

qint64 Generator::bytesAvailable() const
{
    return buffer.size() + QIODevice::bytesAvailable();
}

