#include "function/functionExpression.h"
#include <constants.h>

FunctionExpression::FunctionExpression(QObject *parent) : QObject(parent)
{
    connect(&functionModel, &FunctionModel::error, this, &FunctionExpression::error);
    connect(&functionModel, &FunctionModel::newGraph, this, &FunctionExpression::newGraph);
    connect(&functionModel, &FunctionModel::updateDerivative, this, &FunctionExpression::updateDerivative);

    m_audio = new Audio();
    connect(m_audio, &Audio::audioFinished, this, &FunctionExpression::audioFinished);

    m_audioNotes = new AudioNotes(functionModel);
    connect(m_audioNotes, &AudioNotes::finished, this, &FunctionExpression::audioFinished);

    m_parameters = &Parameters::getInstance();

    m_currentPoint = new CurrentPoint(functionModel);
    connect(m_currentPoint, &CurrentPoint::newCurrentPoint, this, &FunctionExpression::newCurrentPoint);

    m_textToSpeech = new TextToSpeech();

    m_pointsInterest = new PointsInterest(functionModel, *m_audioNotes, *m_currentPoint, *m_textToSpeech);
    connect(m_pointsInterest, &PointsInterest::finished, this, &FunctionExpression::interestingPointFinished);
    connect(m_pointsInterest, &PointsInterest::updateLabel, this, &FunctionExpression::updateText);

    m_dragHandler = new DragHandler();
    connect(m_dragHandler, &DragHandler::newInputValues, this, &FunctionExpression::newInputValues);

    m_zoomer = new FunctionZoomer();
    connect(m_zoomer, &FunctionZoomer::newInputValues, this, &FunctionExpression::newInputValues);

    m_pinchHandler = new PinchHandler();
    connect(m_pinchHandler, &PinchHandler::newInputValues, this, &FunctionExpression::newInputValues);

    m_derivativeMode = 0;
}

FunctionExpression::~FunctionExpression()
{
    delete m_audio;
    delete m_audioNotes;
    delete m_currentPoint;
    delete m_textToSpeech;
    delete m_pointsInterest;
    delete m_dragHandler;
    delete m_zoomer;
    delete m_pinchHandler;
}

void FunctionExpression::calculate(QString expression, QString minX, QString maxX, QString minY, QString maxY)
{
    m_currentPoint->reset();
    m_pointsInterest->setUpdated(false);

    if (m_derivativeMode == 0) {
        functionModel.calculate(expression, minX, maxX, minY, maxY);
    } else if (m_derivativeMode == 1) {
        functionModel.calculate(expression, minX, maxX, minY, maxY);
        functionModel.calculateDerivative();
    } else if (m_derivativeMode == 2) {
        functionModel.calculate(expression, minX, maxX, minY, maxY);
        functionModel.calculateSecondDerivative();
    }
}

void FunctionExpression::startDrag(int x, int y)
{
    m_currentPoint->reset();
    m_pointsInterest->setUpdated(false);
    m_dragHandler->startDrag(functionModel, x, y);
}

void FunctionExpression::drag(int diffX, int diffY, int width, int height)
{
    m_dragHandler->drag(functionModel, diffX, diffY, width, height, m_derivativeMode);
}

void FunctionExpression::zoom(double delta)
{
    m_currentPoint->reset();
    m_pointsInterest->setUpdated(false);
    m_zoomer->zoom(functionModel, delta, m_derivativeMode);
}

void FunctionExpression::startPinch()
{
    m_currentPoint->reset();
    m_pinchHandler->startPinch(functionModel);
}

void FunctionExpression::pinch(double scale)
{
    m_pinchHandler->pinch(functionModel, scale);
}

void FunctionExpression::audio()
{
    if (m_parameters->useNotes())
        startNotes();
    else
        startAudio();

    m_currentPoint->startMoving(m_parameters->duration());
}

void FunctionExpression::startNotes()
{
    m_audioNotes->startNotes(m_parameters->maxFreq(),
                             m_parameters->minFreq(),
                             m_parameters->duration(),
                             m_derivativeMode,
                             m_parameters->useNegativeNotes());
}

void FunctionExpression::startAudio()
{
    m_audio->start(functionModel.expression(),
                   functionModel.minX(),
                   functionModel.maxX(),
                   functionModel.minY(),
                   functionModel.maxY(),
                   m_parameters->duration(),
                   m_parameters->minFreq(),
                   m_parameters->maxFreq(),
                   m_derivativeMode);
    m_currentPoint->startMoving(m_parameters->duration());
}

void FunctionExpression::stopAudio()
{
    m_audio->stop();
    m_audioNotes->stopNotes();
    m_currentPoint->stop();
    m_pointsInterest->stop();
}

void FunctionExpression::nextPoint()
{
    m_currentPoint->next();
    m_audioNotes->setNote(m_currentPoint->point(),
                          m_parameters->minFreq(),
                          m_parameters->maxFreq(),
                          m_parameters->useNotes(),
                          m_derivativeMode,
                          m_parameters->useNegativeNotes());
}

void FunctionExpression::previousPoint()
{
    m_currentPoint->previous();
    m_audioNotes->setNote(m_currentPoint->point(),
                          m_parameters->minFreq(),
                          m_parameters->maxFreq(),
                          m_parameters->useNotes(),
                          m_derivativeMode,
                          m_parameters->useNegativeNotes());
}

void FunctionExpression::sayX()
{
    double x = functionModel.x(m_currentPoint->point());

    double Pow = pow(10.0, m_parameters->precisionDigits());
    x = round (x * Pow) / Pow;

    char c = 'f';
    QString value = QString::number(x, c, m_parameters->precisionDigits());
    m_textToSpeech->speak(value);
}

void FunctionExpression::sayY()
{
    if (functionModel.isValid(m_currentPoint->point())) {
        double y = functionModel.y(m_currentPoint->point());

        double Pow = pow(10.0, m_parameters->precisionDigits());
        y = round (y * Pow) / Pow;

        char c = 'f';
        QString value = QString::number(y, c, m_parameters->precisionDigits());
        m_textToSpeech->speak(value);
    } else {
        m_textToSpeech->speak(tr("Not defined"));
    }
}

void FunctionExpression::getX()
{
    double x = functionModel.x(m_currentPoint->point());

    double Pow = pow(10.0, m_parameters->precisionDigits());
    x = round (x * Pow) / Pow;

    char c = 'f';
    QString value = QString::number(x, c, m_parameters->precisionDigits());
    //m_textToSpeech->speak(value);
    updateText(value);
}

void FunctionExpression::getY()
{
    if (functionModel.isValid(m_currentPoint->point())) {
        double y = functionModel.y(m_currentPoint->point());

        double Pow = pow(10.0, m_parameters->precisionDigits());
        y = round (y * Pow) / Pow;

        char c = 'f';
        QString value = QString::number(y, c, m_parameters->precisionDigits());
        updateText(value);
    } else {
        updateText(tr("Not defined"));
    }
}

void FunctionExpression::sayDerivative()
{
    if (functionModel.isValid(m_currentPoint->point())) {

        if (m_derivativeMode == 0)
            functionModel.refreshDerivative();

        double y = functionModel.derivative(m_currentPoint->point());

        double Pow = pow(10.0, m_parameters->precisionDigits());
        y = round (y * Pow) / Pow;

        char c = 'f';
        QString value = QString::number(y, c, m_parameters->precisionDigits());
        m_textToSpeech->speak(value);
    } else {
        m_textToSpeech->speak(tr("Not defined"));
    }
}

void FunctionExpression::getDerivative()
{
    if (functionModel.isValid(m_currentPoint->point())) {

        if (m_derivativeMode == 0)
            functionModel.refreshDerivative();

        double y = functionModel.derivative(m_currentPoint->point());

        double Pow = pow(10.0, m_parameters->precisionDigits());
        y = round (y * Pow) / Pow;

        char c = 'f';
        QString value = QString::number(y, c, m_parameters->precisionDigits());
        updateText(value);
    } else {
        updateText(tr("Not defined"));
    }
}

void FunctionExpression::decStep()
{
    m_currentPoint->decStep();

    double realStep = (double) m_currentPoint->step() / functionModel.size() * (functionModel.maxX() - functionModel.minX());
    QString text = tr("Step is ") + QString::number(realStep);
    if (m_parameters->selfVoice())
        m_textToSpeech->speak(text);
    updateText(text);
}

void FunctionExpression::incStep()
{
    m_currentPoint->incStep();

    double realStep = (double) m_currentPoint->step() / functionModel.size() * (functionModel.maxX() - functionModel.minX());
    QString text = tr("Step is ") + QString::number(realStep);
    if (m_parameters->selfVoice())
        m_textToSpeech->speak(text);
    updateText(text);
}

void FunctionExpression::previousPointInterest()
{
    m_pointsInterest->previousPoint();
}

void FunctionExpression::nextPointInterest()
{
    m_pointsInterest->nextPoint();
}

void FunctionExpression::previousFast()
{
    m_pointsInterest->previousPointFast();
}

void FunctionExpression::nextFast()
{
    m_pointsInterest->nextPointFast();
}

void FunctionExpression::firstPoint()
{
    stopAudio();
    m_currentPoint->reset();
    if (m_parameters->selfVoice())
        m_textToSpeech->speak(tr("starting point"));
}

void FunctionExpression::lastPoint()
{
    stopAudio();
    m_currentPoint->endPoint();
    if (m_parameters->selfVoice())
        m_textToSpeech->speak(tr("ending point"));
}

void FunctionExpression::setDerivativeMode(int mode)
{
    m_derivativeMode = mode;
    if (m_derivativeMode == 0) {

    } else if (m_derivativeMode == 1) {
        functionModel.calculateDerivative();
    } else if (m_derivativeMode == 2) {
        functionModel.calculateSecondDerivative();
    }

    m_currentPoint->setDerivativeMode(m_derivativeMode);
    m_pointsInterest->setDerivativeMode(m_derivativeMode);
}
