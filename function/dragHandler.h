#ifndef DRAGHANDLER_H
#define DRAGHANDLER_H

#include <QObject>

class FunctionModel;

class DragHandler : public QObject
{
    Q_OBJECT
public:
    DragHandler();
    void startDrag(FunctionModel &model, int x, int y);
    void drag(FunctionModel &model, int diffX, int diffY, int width, int height);

signals:
    void newInputValues(double minX, double maxX, double minY, double maxY);

private:
    int m_dragX;
    int m_dragY;

    double m_minX;
    double m_maxX;
    double m_minY;
    double m_maxY;
};

#endif // DRAGHANDLER_H
