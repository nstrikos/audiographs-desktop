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
    Q_INVOKABLE void audio();
    Q_INVOKABLE void stopAudio();
    Q_INVOKABLE void nextPoint();
    Q_INVOKABLE void previousPoint();
    Q_INVOKABLE void sayX();
    Q_INVOKABLE void sayY();
    Q_INVOKABLE void getX();
    Q_INVOKABLE void getY();
    Q_INVOKABLE void sayDerivative();
    Q_INVOKABLE void getDerivative();
    Q_INVOKABLE void decStep();
    Q_INVOKABLE void incStep();
    Q_INVOKABLE void previousPointInterest();
    Q_INVOKABLE void nextPointInterest();
    Q_INVOKABLE void previousFast();
    Q_INVOKABLE void nextFast();
    Q_INVOKABLE void firstPoint();
    Q_INVOKABLE void lastPoint();
    Q_INVOKABLE void setDerivativeMode(int mode);

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
    void updateDerivative(Points *points, double minX, double maxX, double minY, double maxY);
    void audioFinished();
    void newCurrentPoint(double x, double y);
    void interestingPointFinished();
    void updateText(QString text);

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
