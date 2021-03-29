#include "functionPointView.h"

#include <QtQuick/qsgnode.h>
#include <cmath>
#include "constants.h"

FunctionPointView::FunctionPointView(QQuickItem *parent)
    : QQuickItem(parent)
{
    setFlag(ItemHasContents, true);

    m_points = nullptr;

    m_timer.setInterval(50);
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(update()));
    m_timer.start();
}

FunctionPointView::~FunctionPointView()
{

}

void FunctionPointView::draw(Points *points, double xMin, double xMax, double yMin, double yMax)
{
    m_points = points;
    m_xMin = xMin;
    m_xMax = xMax;
    m_yMin = yMin;
    m_yMax = yMax;
}

void FunctionPointView::setCurrentPoint(double x, double y)
{
    m_x = ( this->width() / (m_xMax - m_xMin) * (x - m_xMin) );
    m_y = this->height() - ( this->height() / (m_yMax - m_yMin) * (y - m_yMin) );
}

QSGNode *FunctionPointView::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *)
{
    QSGGeometryNode *node = nullptr;
    QSGGeometry *geometry = nullptr;

    if (!oldNode) {
        node = new QSGGeometryNode;

        geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), POINT_SEGMENTS);
        geometry->setDrawingMode(QSGGeometry::DrawTriangleFan);
        node->setGeometry(geometry);
        node->setFlag(QSGNode::OwnsGeometry);
        m_material = new QSGFlatColorMaterial;
        m_material->setColor(m_color);
        node->setMaterial(m_material);
        node->setFlag(QSGNode::OwnsMaterial);
    } else {
        node = static_cast<QSGGeometryNode *>(oldNode);
        geometry = node->geometry();
        geometry->allocate(POINT_SEGMENTS);
        m_material->setColor(m_color);
        node->setMaterial(m_material);
        node->setFlag(QSGNode::OwnsMaterial);
    }

    QSGGeometry::Point2D *lineVertices = geometry->vertexDataAsPoint2D();

    int r = m_size;
    for(int ii = 0; ii < POINT_SEGMENTS; ii++) {
        float theta = 2.0f * 3.1415926f * float(ii) / float(POINT_SEGMENTS);//get the current angle

        float x = r * cos(theta);
        float y = r * sin(theta);

        if (m_points != nullptr)
            lineVertices[ii].set(x + m_x, y + m_y);//output vertex
        else
            lineVertices[ii].set(-20, -20);
    }

    node->markDirty(QSGNode::DirtyGeometry);
    node->markDirty(QSGNode::DirtyMaterial);
    return node;
}

int FunctionPointView::size() const
{
    return m_size;
}

void FunctionPointView::setSize(int size)
{
    m_size = size;
}

void FunctionPointView::clear()
{
    m_x = -40;
    m_y = -40;
    update();
}

QColor FunctionPointView::color() const
{
    return m_color;
}

void FunctionPointView::setColor(const QColor &color)
{
    m_color = color;
}
