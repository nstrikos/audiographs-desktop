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

#include "dragHandler.h"
#include "functionZoomer.h"
#include "pinchHandler.h"

class FunctionExpression : public QObject
{
    Q_OBJECT
public:
    explicit FunctionExpression(QObject *parent = nullptr);
    ~FunctionExpression();

    Q_INVOKABLE void calculate(QString expression, QString minX, QString maxX, QString minY, QString maxY); 
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

public slots:
    Q_INVOKABLE void startDrag(int x, int y);
    Q_INVOKABLE void drag(int diffX, int diffY, int width, int height);
    Q_INVOKABLE void zoom(double delta);
    Q_INVOKABLE void startPinch();
    Q_INVOKABLE void pinch(double scale);

signals:
    void error(QString errorString);
    void newGraph(Points *points, double minX, double maxX, double minY, double maxY);
    void newInputValues(double minX, double maxX, double minY, double maxY);
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
    DragHandler *m_dragHandler;
    FunctionZoomer *m_zoomer;
    PinchHandler *m_pinchHandler;

    int m_derivativeMode;

    void startAudio();
    void startNotes();
};

#endif // FUNCTIONEXPRESSION_H
