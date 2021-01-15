#ifndef AUDIONOTES_H
#define AUDIONOTES_H

#include <QObject>
#include <QTimer>
#include "function/functionModel.h"
#include "audiopoints.h"

class AudioNotes : public QObject
{
    Q_OBJECT

public:
    AudioNotes(FunctionModel &model);
    ~AudioNotes();
    Q_INVOKABLE void startNotes(int fmin,
                                int fmax,
                                int duration,
                                int mode,
                                bool useNegativeNotes);
    Q_INVOKABLE void setNoteFromMouse(int mouseX,
                                      int width,
                                      int fmin,
                                      int fmax,
                                      bool useNotes,
                                      int mode);
    Q_INVOKABLE void setNote(int currentPoint,
                             int fmin,
                             int fmax,
                             bool useNotes,
                             int mode,
                             bool useNegativeNotes);
    Q_INVOKABLE void stopNotes();

signals:
    void finished();

private slots:
    void timerExpired();

private:
    FunctionModel &m_model;
    int m_fmin;
    int m_fmax;
    int m_duration;
    QTimer m_timer;
    int m_timeElapsed;
    AudioPoints *m_audioPoints;
    int m_mouseX;
    int m_currentPoint;

    int m_derivMode = 0;
    bool m_useNegativeNotes = false;
};

#endif // AUDIONOTES_H
