#include "renderArea.h"

#include <QPainter>

#include <math.h>

#include <QDebug>
#include <QWheelEvent>

RenderArea::RenderArea(QWidget *parent) : QWidget(parent)
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);

    m_points = nullptr;
    m_derivPoints = nullptr;
    m_parameters = nullptr;

    m_x = -100;
    m_y = -100;

    m_showCurrentPoint = false;

    m_derivMode = 0;
}

RenderArea::~RenderArea()
{

}

void RenderArea::updateGraph(Points *points, double xMin, double xMax, double yMin, double yMax)
{
    if (points == nullptr)
        return;

    m_points = points;
    m_xMin = xMin;
    m_xMax = xMax;
    m_yMin = yMin;
    m_yMax = yMax;

    m_x = -100;
    m_y = -100;

    calcCoordinates();
    update();
}

void RenderArea::updateDerivative(Points *points, double xMin, double xMax, double yMin, double yMax)
{
    if (points == nullptr)
        return;

    m_derivPoints = points;
    m_xMin = xMin;
    m_xMax = xMax;
    m_yMin = yMin;
    m_yMax = yMax;

    calcDerivCoordinates();
    update();
}

void RenderArea::clear()
{
    m_coordPoints.clear();
    m_derivCoordPoints.clear();
    m_xMin = -10;
    m_xMax = 10;
    m_yMin = -10;
    m_yMax = 10;
    update();
}

void RenderArea::setDerivativeMode(int mode)
{
    m_derivMode = mode;

    if (m_derivMode == 0) {
        clearDerivative();
    }
}

void RenderArea::clearDerivative()
{
    m_derivCoordPoints.clear();
    update();
}

void RenderArea::calcCoordinates()
{
    if (m_points == nullptr)
        return;

    m_coordPoints.clear();

    int w = this->width();
    int h = this->height();

    Point tmpPoint;

    for (int i = 0; i < 10000; i++) {
        if (m_points->validAt(i)) {
            int k = static_cast<int>( round(  w / (m_xMax - m_xMin) * (m_points->xAt(i) - m_xMin) ));
            int l = static_cast<int>( round( (h / (m_yMax - m_yMin) * (m_points->yAt(i) - m_yMin) )));
            l = h - l;
            tmpPoint.x = k;
            tmpPoint.y = l;
            m_coordPoints.append(tmpPoint);
        }
    }
}

void RenderArea::calcDerivCoordinates()
{
    if (m_points == nullptr)
        return;

    if (m_derivPoints == nullptr)
        return;

    //if (m_derivPoints->size() == 0)
    //    return;

    m_derivCoordPoints.clear();

    int w = this->width();
    int h = this->height();

    Point tmpPoint;

    for (int i = 0; i < 10000; i++) {
        if (m_points->validAt(i)) {
            int k = static_cast<int>( round(  w / (m_xMax - m_xMin) * (m_derivPoints->xAt(i) - m_xMin) ));
            int l = static_cast<int>( round( (h / (m_yMax - m_yMin) * (m_derivPoints->yAt(i) - m_yMin) ) ));
            l = h - l;
            tmpPoint.x = k;
            tmpPoint.y = l;
            m_derivCoordPoints.append(tmpPoint);
        }
    }
}

void RenderArea::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    if (m_parameters == nullptr)
        return;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QBrush backgoundBrush(m_parameters->backgroundColor());
    painter.fillRect(this->rect(), backgoundBrush);

    QPen linePen(m_parameters->highlightColor(), 3);

    drawGrid(&painter);

    QBrush pointBrush(m_parameters->lineColor());
    painter.setBrush(pointBrush);
    painter.setPen(Qt::NoPen);

    for (int i = 0; i < m_coordPoints.size(); i++) {
        int center_x = m_coordPoints.at(i).x;
        int center_y = m_coordPoints.at(i).y;
        int radius = m_parameters->lineWidth();
        QRectF rectangle(center_x - radius / 2, center_y - radius / 2, radius, radius );
        painter.drawRect(rectangle);
    }

    QBrush derivPointBrush(m_parameters->derivColor());
    painter.setBrush(derivPointBrush);
    painter.setPen(Qt::NoPen);

    for (int i = 0; i < m_derivCoordPoints.size(); i++) {
        int center_x = m_derivCoordPoints.at(i).x;
        int center_y = m_derivCoordPoints.at(i).y;
        int radius = m_parameters->lineWidth();
        QRectF rectangle(center_x - radius / 2, center_y - radius / 2, radius, radius );
        painter.drawRect(rectangle);
    }

    if (m_showCurrentPoint) {
        QBrush brush3(m_parameters->highlightColor());
        painter.setBrush(brush3);
        painter.setPen(Qt::NoPen);
        int radius = m_parameters->highlightSize();
        QRectF rectangle(m_x - radius / 2, m_y - radius / 2, radius, radius );
        if (m_y == m_y) //check for nan (not a number)
            painter.drawEllipse(rectangle);
        painter.setPen(linePen);
        painter.drawLine(m_x, 0, m_x, this->height());
    }
}

void RenderArea::drawGrid(QPainter *painter)
{

    m_xGridCoords.clear();
    m_yGridCoords.clear();
    m_xGridValues.clear();
    m_yGridValues.clear();

    double xStart = m_xMin;
    double xEnd = m_xMax;
    double yStart = m_yMin;
    double yEnd = m_yMax;

    double xInterval = findInterval(xEnd - xStart);
    findVerticalGridLines(xStart, xEnd, xInterval);
    drawVerticalLines(painter);

    double yInterval = findInterval(yEnd - yStart);
    findHorizontalGridLines(yStart, yEnd, yInterval);
    drawHorizontalLines(painter);

    drawAxes(painter);
}

void RenderArea::drawAxes(QPainter *painter)
{
    QBrush brush(m_parameters->axesColor());
    QPen pen(brush, m_parameters->axesSize());
    painter->setBrush(brush);
    painter->setPen(pen);

    double x0 = m_xMin;
    double x1 = m_xMax;
    double y0 = m_yMin;
    double y1 = m_yMax;

    int xAxes = round( ( this->width() / (x1 - x0) * (0 - x0) ) );
    int yAxes = round( (this->height() / (y1 - y0) * (0 - y0) ) );

    painter->drawLine(xAxes, 0, xAxes, this->height());
    painter->drawLine(0, this->height() - yAxes, this->width(), this->height() - yAxes);
}

void RenderArea::findVerticalGridLines(double x0, double x1, double dl)
{
    double point = x0;
    point = point / dl;
    point = floor(point);
    point = point * dl;

    bool done = false;
    while (!done) {
        point += dl;
        int screenPoint = round( ( this->width() / (x1 - x0) * (point - x0) ) );
        m_xGridCoords.append(screenPoint);
        double value = (double) (round(point / dl) * dl);
        m_xGridValues.append(value);

        if (point > x1)
            done = true;
    }
}

void RenderArea::drawVerticalLines(QPainter *painter)
{
    QBrush brush(m_parameters->axesColor());
    QPen pen(brush, 1, Qt::DotLine);
    painter->setBrush(brush);
    painter->setPen(pen);

    QRectF rect;
    int i = 0;
    int x = 0;
    while ( i < m_xGridCoords.size()) {

        if (m_xGridValues.at(i) == 0) {
            i++;
            continue;
        }

        x = m_xGridCoords.at(i);

        if (m_parameters->showAxes())
            painter->drawLine(x, 0, x, this->height());

        QString text = QString::number(m_xGridValues.at(i));
        rect = QRect(x - 50, 0, 100, 100);
        painter->drawText(rect, Qt::AlignHCenter, text);
        i++;
    }
}

void RenderArea::findHorizontalGridLines(double y0, double y1, double dl)
{
    if (y1 > y0) {
        double point = y0;
        point = point / dl;
        point = floor(point);
        point = point * dl;
        m_yGridCoords.append(this->height() - round( (this->height() / (y1 - y0) * (point - y0) ) ));
        double value = round (point / dl) * dl;
        m_yGridValues.append(value);

        bool done = false;
        while (!done) {
            point += dl;
            int screenPoint = round( (this->height() / (y1 - y0) * (point - y0) ) );
            screenPoint = this->height() - screenPoint;
            m_yGridCoords.append(screenPoint);
            value = round (point / dl) * dl;
            m_yGridValues.append(value);

            if (point > y1)
                done = true;
        }
    }
}

void RenderArea::drawHorizontalLines(QPainter *painter)
{
    QBrush brush(m_parameters->axesColor());
    QPen pen(brush, 1, Qt::DotLine);
    painter->setBrush(brush);
    painter->setPen(pen);

    int i = 0;
    int y = 0;
    QRectF rect;
    while ( i < m_yGridCoords.size()) {

        if (m_yGridValues.at(i) == 0) {
            i++;
            continue;
        }

        y = m_yGridCoords.at(i);

        if (m_parameters->showAxes())
            painter->drawLine(0, y, this->width(), y);

        QString text = QString::number(m_yGridValues.at(i));
        rect = QRect(0, y - 16, 100, 100);
        painter->drawText(rect, Qt::AlignLeft, text);
        i++;
    }
}

double RenderArea::findInterval(double diff)
{
    //This function returns a number
    //which represents how many lines we will draw for the grid
    double m;
    double times;
    double interval;
    double power = floor(log10(diff)) - 1;

    interval = 0;

    m = 10 * pow(10, power);
    times = diff / m;
    if (times <= 10)
        interval = m;

    m = 5 * pow(10, power);
    times = diff / m;
    if (times <= 10)
        interval = m;

    m = 4 * pow(10, power);
    times = diff / m;
    if (times <= 10)
        interval = m;

    m = 2 * pow(10, power);
    times = diff / m;
    if (times <= 10)
        interval = m;

    m = 1 * pow(10, power);
    times = diff / m;
    if (times <= 10)
        interval = m;

    return interval;
}



void RenderArea::setParameters(Parameters *parameters)
{
    m_parameters = parameters;
}

void RenderArea::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);

    calcCoordinates();
    calcDerivCoordinates();

    getResizedCoords(m_oldX, m_oldY);

    update();
}

void RenderArea::getResizedCoords(double x, double y)
{
    m_x = ( this->width() / (m_xMax - m_xMin) * (x - m_xMin) );
    m_y = this->height() - ( this->height() / (m_yMax - m_yMin) * (y - m_yMin) );
}

void RenderArea::wheelEvent(QWheelEvent *event)
{
    int delta = event->angleDelta().y();
    emit zoom(delta);
}

void RenderArea::mousePressEvent(QMouseEvent *event)
{
    m_mousePressed = true;
    emit mousePressed(event->pos().x(), event->pos().y());
}

void RenderArea::mouseMoveEvent(QMouseEvent *event)
{
    if (m_mousePressed)
        emit mouseMove(event->pos().x(), event->pos().y());
}

void RenderArea::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    m_mousePressed = false;
    emit mouseReleased();
}

void RenderArea::newCurrentPoint(double x, double y)
{
    m_oldX = x;
    m_oldY = y;

    getResizedCoords(m_oldX, m_oldY);
    update();
}

void RenderArea::enableCurrentPoint()
{
    m_showCurrentPoint = true;
}

void RenderArea::disableCurrentPoint()
{
    m_showCurrentPoint = false;
}
