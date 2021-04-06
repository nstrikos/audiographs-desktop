#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include "function/point.h"
#include "parameters.h"

#include<array>
using namespace std;

class RenderArea : public QWidget
{
    Q_OBJECT

public:

    RenderArea(QWidget *parent = nullptr);
    ~RenderArea() override;
    void updateGraph(Points *points,
                     double xMin,
                     double xMax,
                     double yMin,
                     double yMax);

    void updateDerivative(Points *points,
                          double xMin,
                          double xMax,
                          double yMin,
                          double yMax);

    void clear();
    void setDerivativeMode(int mode);

    void setParameters(Parameters *parameters);
    void newCurrentPoint(double x, double y);
    void enableCurrentPoint();
    void disableCurrentPoint();

signals:
    void zoom(int delta);
    void mousePressed(int x, int y);
    void mouseMove(int diffX, int diffY);
    void mouseReleased();

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
private:
    void calcCoordinates();
    void calcDerivCoordinates();
    void drawGrid(QPainter *painter);
    void drawAxes(QPainter *painter);
    void findVerticalGridLines(double x0, double x1, double dl);
    void drawVerticalLines(QPainter *painter);
    void findHorizontalGridLines(double y0, double y1, double dl);
    void drawHorizontalLines(QPainter *painter);
    double findInterval(double diff);

    void getResizedCoords(double x, double y);

    void clearDerivative();

    Points *m_points;
    QVector<Point> m_coordPoints;

    Points *m_derivPoints;
    QVector<Point> m_derivCoordPoints;

    QVector<int> m_xGridCoords;
    QVector<int> m_yGridCoords;
    QVector<double> m_xGridValues;
    QVector<double> m_yGridValues;

    double m_xMin;
    double m_xMax;
    double m_yMin;
    double m_yMax;

    bool m_mousePressed = false;

    Parameters *m_parameters;

    double m_x, m_y;

    bool m_showCurrentPoint;

    double m_oldX, m_oldY;

    int m_derivMode = 0;
};

#endif // RENDERAREA_H
