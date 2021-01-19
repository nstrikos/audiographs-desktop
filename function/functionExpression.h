#ifndef FUNCTIONEXPRESSION_H
#define FUNCTIONEXPRESSION_H

#include <QObject>

#include "function/functionModel.h"
#include "generator/audio.h"
#include "audionotes/audionotes.h"
#include "parameters.h"
#include "currentPoint.h"
#include "texttospeech.h"
#include "pointInterest.h"

class FunctionExpression : public QObject
{
    Q_OBJECT
public:
    explicit FunctionExpression(QObject *parent = nullptr);
    ~FunctionExpression();

    void calculate(QString expression, QString minX, QString maxX, QString minY, QString maxY);
    void audio();
    void stopAudio();
    void nextPoint();
    void previousPoint();
    void sayX();
    void sayY();
    void sayDerivative();
    void decStep();
    void incStep();
    void previousPointInterest();
    void nextPointInterest();
    void previousFast();
    void nextFast();
    void firstPoint();
    void lastPoint();
    void setDerivativeMode(int mode);

signals:
    void error(QString errorString);
    void newGraph(QVector<Point> *points, double minX, double maxX, double minY, double maxY);
    void updateDerivative(QVector<Point> *points, double minX, double maxX, double minY, double maxY);
    void audioFinished();
    void newCurrentPoint(double x, double y);
    void interestingPointFinished();

private:
    FunctionModel functionModel;
    Audio *m_audio;
    AudioNotes *m_audioNotes;
    Parameters *m_parameters;
    CurrentPoint *m_currentPoint;
    TextToSpeech *m_textToSpeech;
    PointsInterest *m_pointsInterest;

    int m_derivativeMode;

    void startAudio();
    void startNotes();
};

#endif // FUNCTIONEXPRESSION_H
