#ifndef AUDIO_H
#define AUDIO_H

#include <QObject>
#include "audioengine.h"

class Audio : public QObject
{
    Q_OBJECT
public:
    Audio();
    ~Audio();
    Q_INVOKABLE void start(QString expression,
                           double start,
                           double end,
                           double minY,
                           double maxY,
                           int seconds,
                           double fmin,
                           double fmax,
                           int mode);
    Q_INVOKABLE void stop();

signals:
    void audioFinished();

private:
    AudioEngine *m_audioEngine;
    void reset();
};

#endif // AUDIO_H
