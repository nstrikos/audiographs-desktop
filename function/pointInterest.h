#ifndef POINTINTEREST_H
#define POINTINTEREST_H

#include <QObject>
#include <QVector>
#include <QTimer>
#include "function/functionModel.h"
#include "function/functionDescription.h"
#include "audionotes/audionotes.h"
#include "parameters.h"
#include "function/currentPoint.h"
#include "texttospeech.h"
#include "parameters.h"

class PointsInterest : public QObject
{
    Q_OBJECT
public:
    explicit PointsInterest(FunctionModel &functionModel,
                            AudioNotes &audioNotes,
                            CurrentPoint &currentPoint,
                            TextToSpeech &textToSpeech);
    ~PointsInterest();
    void nextPoint();

    void previousPoint();

    void nextPointFast();

    void previousPointFast();

    void stop();

    void setUpdated(bool updated);

    double currentPointX();
    double currentPointY();
    QString currentPointLabel();

    void setDerivativeMode(int mode);

signals:
    void finished();
    void updateLabel(QString text);


private slots:
    void timerExpired();

private:
    int m_pointInterest;
    QTimer m_timer;
    bool m_forward;
    FunctionModel &m_model;
    FunctionDescription *m_funcDescription;
    QVector<InterestingPoint> m_points;
    AudioNotes &m_audioNotes;
    CurrentPoint &m_currentPoint;
    TextToSpeech &m_textToSpeech;
    bool m_isUpdated;
    int getNextPointInterest();
    void start();
    int m_derivMode = 0;

    int m_step = 1;

    int m_timerInterVal = 40;

    void setStep();

    Parameters *m_parameters;
};

#endif // POINTSINTEREST_H
