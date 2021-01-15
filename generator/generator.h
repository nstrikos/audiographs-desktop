#include <QIODevice>
#include <QAudioFormat>
#include <generator/genmodvalues.h>

const int ToneSampleRateHz = 500;
const int DataSampleRateHz = 44100;
//const int BufferSize = 32768;
const int oneMillion = 1000000;


class Generator : public QIODevice
{
    Q_OBJECT

public:
    Generator(QAudioFormat format,
              QString expression,
              double start,
              double end,
              double minY,
              double maxY,
              int seconds,
              int fmin,
              int fmax,
              int mode);
    ~Generator();
    void start();

private:
    qint64 readData(char *data, qint64 maxlen);
    qint64 writeData(const char *data, qint64 len);
    qint64 bytesAvailable() const;
    void generateData(const QAudioFormat &format, int seconds);

private:
    QAudioFormat format;
    int seconds;
    int fmin;
    int fmax;
    qint64 pos;
    QByteArray buffer;
    void computeFunction();
    double* modulationValues;

    qint64 length;
    int m_channelBytes;
    QString m_expression;
    double m_start;
    double m_end;
    double m_minY;
    double m_maxY;
    int m_mode = 0;
};
