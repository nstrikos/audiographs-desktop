#include "pointInterest.h"

#include <QDebug>

#include "math.h"

PointsInterest::PointsInterest(FunctionModel &functionModel,
                               AudioNotes &audioNotes,
                               CurrentPoint &currentPoint,
                               TextToSpeech &textToSpeech):
    m_model(functionModel),
    m_audioNotes(audioNotes),
    m_currentPoint(currentPoint),
    m_textToSpeech(textToSpeech)
{
    m_funcDescription = nullptr;
    m_pointInterest = 0;
    //    m_audioNotes = nullptr;
    m_forward = true;
    m_isUpdated = false;
    m_timer.setTimerType(Qt::PreciseTimer);
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(timerExpired()));

    m_parameters = &Parameters::getInstance();
}

PointsInterest::~PointsInterest()
{
    if (m_funcDescription != nullptr)
        delete m_funcDescription;
}

void PointsInterest::nextPoint()
{
    if (m_model.size() == 0)
        return;

    m_forward = true;
    start();
}

void PointsInterest::previousPoint()
{
    if (m_model.size() == 0)
        return;

    m_forward = false;
    start();
}

void PointsInterest::nextPointFast()
{
    if (m_model.size() == 0)
        return;

    if (m_funcDescription == nullptr)
        m_funcDescription = new FunctionDescription;


    if (m_isUpdated == false) {
        m_points.clear();
        m_points = m_funcDescription->points(&m_model);
        m_isUpdated = true;
    }

    m_forward = true;
    m_pointInterest = getNextPointInterest();
    m_currentPoint.setPoint(m_points[m_pointInterest].x);
    QString label = currentPointLabel();
    if (m_parameters->selfVoice())
        m_textToSpeech.speak(label);
    emit updateLabel(label);
}

void PointsInterest::previousPointFast()
{

    if (m_model.size() == 0)
        return;
    if (m_funcDescription == nullptr)
        m_funcDescription = new FunctionDescription;


    if (m_isUpdated == false) {
        m_points.clear();
        m_points = m_funcDescription->points(&m_model);
        m_isUpdated = true;
    }

    m_forward = false;
    m_pointInterest = getNextPointInterest();
    m_currentPoint.setPoint(m_points[m_pointInterest].x);
    QString label = currentPointLabel();
    if (m_parameters->selfVoice())
        m_textToSpeech.speak(label);
    emit updateLabel(label);
}

void PointsInterest::start()
{
    if (m_funcDescription == nullptr)
        m_funcDescription = new FunctionDescription;


    if (m_isUpdated == false) {
        m_points.clear();
        m_points = m_funcDescription->points(&m_model);
        m_isUpdated = true;
    }

    //    m_audioNotes = audioNotes;
    //    m_currentPoint = currentPoint;
    //    m_pointView = pointView;

    m_pointInterest = getNextPointInterest();

    setStep();

    m_timer.setInterval(m_timerInterVal);
    m_timer.start();
}

void PointsInterest::setStep()
{
    long long int i = m_parameters->duration() * 1000;

    long int diff;

    long int d;

    //qDebug() << i;

    long int min;
    int step;

    int n = 1;

    int size = m_model.size();
    d = size / n * m_timerInterVal;
    diff = abs(i - d);
    min = diff;
    step = n;

    //qDebug() << n << diff;

    n = 2;

    d = size / n * m_timerInterVal;
    diff = abs(i-d);

    if (diff < min) {
        min = diff;
        step = n;
    }
    //qDebug() << n << diff;


    n = 4;

    d = size / n * m_timerInterVal;
    diff = abs(i-d);

    if (diff < min) {
        min = diff;
        step = n;
    }
    //qDebug() << n << diff;


    n = 5;
    d = size / n * m_timerInterVal;
    diff = abs(i-d);

    if (diff < min) {
        min = diff;
        step = n;
    }
    //qDebug() << n << diff;


    n = 10;

    d = size / n * m_timerInterVal;
    diff = abs(i-d);

    if (diff < min) {
        min = diff;
        step = n;
    }
    //qDebug() << n << diff;


    n = 20;

    d = size / n * m_timerInterVal;
    diff = abs(i-d);

    if (diff < min) {
        min = diff;
        step = n;
    }
    //qDebug() << n << diff;


    n = 25;

    d = size / n * m_timerInterVal;
    diff = abs(i-d);

    if (diff < min) {
        min = diff;
        step = n;
    }
    //qDebug() << n << diff;


    //qDebug() << min << step;

    m_step = step;
}

void PointsInterest::setDerivativeMode(int mode)
{
    m_derivMode = mode;
}

int PointsInterest::getNextPointInterest()
{
    int point = 0;
    if (m_forward == true) {
        for (int i = 0; i < m_points.size(); i++) {
            if (m_points.at(i).x < m_currentPoint.point()) {
                continue;
            } else if ((m_points.at(i).x == m_currentPoint.point())) {
                point = i + 1;
                break;
            }
            else {
                point = i;
                break;
            }
        }
    } else {
        for (int i = m_points.size() - 1; i >= 0; i--) {
            if (m_points.at(i).x > m_currentPoint.point()) {
                continue;
            } else if (m_points.at(i).x == m_currentPoint.point()) {
                point = i - 1;
                break;
            }
            else {
                point = i;
                break;
            }
        }
    }

    if (point >= m_points.size())
        point = m_points.size() - 1;

    if (point < 0)
        point = 0;

    return point;
}

void PointsInterest::stop()
{
    m_timer.stop();
    //    if (m_audioNotes != nullptr)
    m_audioNotes.stopNotes();
    //m_isUpdated = false;
    //        qDebug() << "stop";
}

void PointsInterest::setUpdated(bool updated)
{
    m_isUpdated = updated;
}

void PointsInterest::timerExpired()
{
    //    if (m_pointView == nullptr)
    //        return;
    //    if (m_audioNotes == nullptr)
    //        return;
    //    if (m_model == nullptr)
    //        return;

    Parameters *parameters = &Parameters::getInstance();

    if (m_forward) {
        m_currentPoint.incPoint(m_step);
        if (m_currentPoint.point() >= m_points[m_pointInterest].x) {
            m_currentPoint.setPoint(m_points[m_pointInterest].x);
            m_timer.stop();
            QString label = currentPointLabel();
            if (m_parameters->selfVoice())
                m_textToSpeech.speak(label);
            emit updateLabel(label);
            emit finished();
        } else {
            m_audioNotes.setNote(m_currentPoint.point(), parameters->minFreq(), parameters->maxFreq(), parameters->useNotes(), m_derivMode, m_parameters->useNegativeNotes());
        }
    } else {
        m_currentPoint.decPoint(m_step);
        if (m_currentPoint.point() <= m_points[m_pointInterest].x) {
            m_currentPoint.setPoint(m_points[m_pointInterest].x);
            m_timer.stop();
            QString label = currentPointLabel();
            if (m_parameters->selfVoice())
                m_textToSpeech.speak(label);
            emit updateLabel(label);
            emit finished();
        } else {
            m_audioNotes.setNote(m_currentPoint.point(), parameters->minFreq(), parameters->maxFreq(), parameters->useNotes(), m_derivMode, m_parameters->useNegativeNotes());
        }
    }
}

double PointsInterest::currentPointX()
{
    return m_model.x(m_points[m_pointInterest].x);
}

double PointsInterest::currentPointY()
{
    return m_points[m_pointInterest].y;
}

QString PointsInterest::currentPointLabel()
{
    return m_points[m_pointInterest].label;
}
