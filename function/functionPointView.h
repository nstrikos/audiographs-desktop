#ifndef FUNCTIONPOINTVIEW_H
#define FUNCTIONPOINTVIEW_H


#include <QtQuick/QQuickItem>
#include <QTimer>
#include <QtQuick/qsgflatcolormaterial.h>

#include "function/point.h"

class FunctionPointView : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(QColor color READ color WRITE setColor)
    Q_PROPERTY(int size READ size WRITE setSize)

public:
    FunctionPointView(QQuickItem *parent = 0);
    ~FunctionPointView();

    QColor color() const;
    void setColor(const QColor &color);

    int size() const;
    void setSize(int size);

    Q_INVOKABLE void clear();

public slots:
    void draw(Points *points,
              double xMin,
              double xMax,
              double yMin,
              double yMax);
    void setCurrentPoint(double x, double y);

private:
    QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *);

    Points *m_points;
    double m_xMin;
    double m_xMax;
    double m_yMin;
    double m_yMax;

    double m_x;
    double m_y;
    QTimer m_timer;
    QColor m_color;
    int m_size;
    QSGFlatColorMaterial *m_material;

    int POINT_SEGMENTS = 16;
};

#endif // FUNCTIONPOINTVIEW_H
