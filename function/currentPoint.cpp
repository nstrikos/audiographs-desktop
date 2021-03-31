#include "currentPoint.h"

#include "constants.h"

#include <QDebug>

CurrentPoint::CurrentPoint(FunctionModel &model) : m_model(model)
{
    timer.setTimerType(Qt::PreciseTimer);
    timer.setInterval(INTERVAL_MILLISECONDS);

    connect(&timer, &QTimer::timeout, this, &CurrentPoint::timerExpired);

    m_point = 0;
    m_step = 10;

    m_derivMode = 0;
}

void CurrentPoint::startMoving(int duration)
{
    m_duration = duration * 1000;
    //m_X = -100;
    //m_Y = -100;
    m_point = 0;
    m_timeElapsed = 0;
    timer.start();
}

void CurrentPoint::timerExpired()
{
    m_timeElapsed += timer.interval();
    if (m_timeElapsed >= m_duration) {
        timer.stop();
        m_point = 0;
        return;
    }

    double cx = (double) m_timeElapsed / m_duration;
    m_point = round(cx * LINE_POINTS);
    if (m_point >= LINE_POINTS)
        m_point = LINE_POINTS - 1;
    if (m_point < 0)
        m_point = 0;

    if (m_derivMode == 0) {
        m_X = m_model.x(m_point);
        m_Y = m_model.y(m_point);
    } else {
        m_X = m_model.x(m_point);
        m_Y = m_model.derivative(m_point);
    }

    emit newCurrentPoint(m_X, m_Y);
}

int CurrentPoint::step() const
{
    return m_step;
}

void CurrentPoint::setPoint(int point)
{
    //    if (m_width == -1 || m_height == -1)
    //        return;

    //    if (m_model == nullptr)
    //        return;

    //    if (m_model->lineSize() == 0)
    //        return;

    //    int size = m_model->lineSize();
    //    double xStart = m_model->x(0);
    //    double xEnd = m_model->x(size - 1);
    //    double minY = m_model->minY();
    //    double maxY = m_model->maxY();

    //    double x, y;
    //    if (m_mode == 0) {
    //        x =  ( m_width / (xEnd - xStart) * (m_model->x(m_point) - xStart) );
    //        y = ( m_height / (maxY - minY) * (m_model->y(m_point) - minY) );
    //    } else {
    //        x =  ( m_width / (xEnd - xStart) * (m_model->x(m_point) - xStart) );
    //        y = ( m_height / (maxY - minY) * (m_model->derivative(m_point) - minY) );
    //    }

    //    y = m_height - y;

    if (point < 0)
        return;

    if (point >= m_model.size())
        return;

    m_point = point;

    if (m_derivMode == 0) {
        m_X = m_model.x(m_point);
        m_Y = m_model.y(m_point);
    } else {
        m_X = m_model.x(m_point);
        m_Y = m_model.derivative(m_point);
    }

    emit newCurrentPoint(m_X, m_Y);
}

void CurrentPoint::incPoint(int step)
{
    //    if (m_width == -1 || m_height == -1)
    //        return;

    //    if (m_model == nullptr)
    //        return;

    m_point += step;

    if (m_point >= LINE_POINTS)
        m_point = LINE_POINTS - 1;

    setPoint(m_point);
}

void CurrentPoint::decPoint(int step)
{
    //    if (m_width == -1 || m_height == -1)
    //        return;

    //    if (m_model == nullptr)
    //        return;

    m_point -= step;

    if (m_point <= 0)
        m_point = 0;

    setPoint(m_point);
}

void CurrentPoint::endPoint()
{
    timer.stop();

    if (m_model.size() > 0) {
        m_point = m_model.size() - 1;
        setPoint(m_point);
    }
}

void CurrentPoint::setDerivativeMode(int mode)
{
    m_derivMode = mode;
}

void CurrentPoint::stop()
{
    timer.stop();
    //m_point = 0;
    //    if (m_model.size() > 0) {
    //        m_X = m_model.x(0);
    //        m_Y = m_model.y(0);
    //    } else {
    //        m_X = -100;
    //        m_Y = -100;
    //    }
    //emit newCurrentPoint(m_X, m_Y);
}

void CurrentPoint::pause()
{
    timer.stop();
}

void CurrentPoint::reset()
{
    timer.stop();
    setPoint(0);
}

void CurrentPoint::next()
{
    m_point += m_step;
    if (m_point >= LINE_POINTS)
        m_point = LINE_POINTS - 1;

    //m_X = m_model.x(m_point);
    //m_Y = m_model.y(m_point);

    setPoint(m_point);

    emit newCurrentPoint(m_X, m_Y);
}

void CurrentPoint::previous()
{
    m_point -= m_step;
    if (m_point < 0)
        m_point = 0;

    //m_X = m_model.x(m_point);
    //m_Y = m_model.y(m_point);

    setPoint(m_point);

    emit newCurrentPoint(m_X, m_Y);
}

int CurrentPoint::point()
{
    return m_point;
}

void CurrentPoint::decStep()
{
    m_step -= 10;
    m_step = round(m_step);
    if (m_step < 1)
        m_step = 1;
}

void CurrentPoint::incStep()
{
    if (m_step == 1) {
        m_step = 10;
        return;
    }

    m_step += 10;
    m_step = round(m_step);
    if (m_step > 100)
        m_step = 100;
}

double CurrentPoint::X() const
{
    return m_X;
}

double CurrentPoint::Y() const
{
    return m_Y;
}
