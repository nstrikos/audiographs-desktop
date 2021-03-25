#ifndef CURRENTPOINT_H
#define CURRENTPOINT_H

#include "functionModel.h"
#include <QObject>
#include <QTimer>

class CurrentPoint : public QObject
{
    Q_OBJECT
public:
    CurrentPoint(FunctionModel &model);
    void startMoving(int duration);
    void stop();
    void pause();
    void reset();
    void next();
    void previous();
    int point();
    void decStep();
    void incStep();

    int step() const;
    void setPoint(int point);

    void incPoint(int step);
    void decPoint(int step);

    void endPoint();

    void setDerivativeMode(int mode);

    double X() const;
    double Y() const;

signals:
    void newCurrentPoint(double x, double y);

private slots:
    void timerExpired();

private:
    FunctionModel &m_model;

    int m_duration;
    int m_timeElapsed;
    QTimer timer;

    double m_X;
    double m_Y;
    int m_point;
    int m_step;

    int m_derivMode = 0;
};

#endif // CURRENTPOINT_H
