#include "functionDisplayView.h"

#include <QtQuick/qsgnode.h>
#include <QtQuick/qsgflatcolormaterial.h>

#include "constants.h"

FunctionDisplayView::FunctionDisplayView(QQuickItem *parent)
    : QQuickItem(parent)
{
    setFlag(ItemHasContents, true);
    m_newColor = m_color;
    m_lineWidth = 10;

#ifdef Q_OS_ANDROID
    m_factor = 10;
#else
    m_factor = 1;
#endif

    m_update = true;
}

FunctionDisplayView::~FunctionDisplayView()
{

}

void FunctionDisplayView::updateView()
{
    if (m_update == false)
        return;

    calcCoords(this->width(), this->height());
    update();
}

void FunctionDisplayView::draw(Points *points,
                               double xMin,
                               double xMax,
                               double yMin,
                               double yMax)
{
    if (m_update == false)
        return;

    m_points = points;
    m_xMin = xMin;
    m_xMax = xMax;
    m_yMin = yMin;
    m_yMax = yMax;

//    if (m_points->size() > 0) {
        calcCoords(this->width(), this->height());
        update();
//    }
}

//void FunctionDisplayView::drawDerivative(FunctionModel *model)
//{
//    m_model = model;
//    if (m_model != nullptr &&  m_model->size() > 0) {
//        calcDerivCoords(this->width(), this->height());
//        update();
//    }
//}

QSGNode *FunctionDisplayView::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *)
{
    QSGGeometryNode *node = nullptr;
    QSGGeometry *geometry = nullptr;

#ifdef Q_OS_ANDROID
    QVector<QSGGeometryNode*> nodeVector;
    QVector<QSGGeometry*> geometryVector;
#endif

    if (!oldNode) {
        node = new QSGGeometryNode;

#ifndef Q_OS_ANDROID
        qDebug() << LINE_POINTS / m_factor;
        geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), LINE_POINTS / m_factor);
#else
        //For android we use only 1 point as main geometry
        //all other points are appended to this point
        geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 1);
#endif

        geometry->setLineWidth(m_lineWidth);
        geometry->setDrawingMode(QSGGeometry::DrawPoints);
        node->setGeometry(geometry);
        node->setFlag(QSGNode::OwnsGeometry);
        QSGFlatColorMaterial *material = new QSGFlatColorMaterial;
        material->setColor(m_color);
        node->setMaterial(material);
        node->setFlag(QSGNode::OwnsMaterial);

#ifdef Q_OS_ANDROID
        for (int i = 0; i < LINE_POINTS / m_factor; i++) {
            QSGGeometryNode *tmpNode = new QSGGeometryNode;
            QSGGeometry *tmpGeometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 16);
            tmpGeometry->setDrawingMode(QSGGeometry::DrawTriangleFan);
            tmpNode->setGeometry(tmpGeometry);
            QSGFlatColorMaterial *tmpMaterial = new QSGFlatColorMaterial;
            tmpMaterial->setColor(m_color);
            tmpNode->setMaterial(tmpMaterial);
            tmpNode->setFlag(QSGNode::OwnsMaterial);
            node->appendChildNode(tmpNode);
        }
#endif

    } else {
        node = static_cast<QSGGeometryNode *>(oldNode);
        geometry = node->geometry();
        geometry->setLineWidth(m_lineWidth);
//        if (m_newColor != m_color) {
            QSGFlatColorMaterial *material = new QSGFlatColorMaterial;
            material->setColor(m_color);
            node->setMaterial(material);
            node->setFlag(QSGNode::OwnsMaterial);
            node->markDirty(QSGNode::DirtyMaterial);
//        }
#ifndef Q_OS_ANDROID
        geometry->allocate(LINE_POINTS / m_factor);
#else
        geometry->allocate(1);
#endif

#ifdef Q_OS_ANDROID
        for (int i = 0; i < LINE_POINTS / m_factor; i++) {
            QSGGeometryNode *tmpNode = static_cast<QSGGeometryNode *>(oldNode->childAtIndex(i));
            nodeVector.append(tmpNode);
            QSGGeometry *tmpGeometry = tmpNode->geometry();
            tmpGeometry->allocate(POINT_SEGMENTS);
            tmpGeometry->setDrawingMode(QSGGeometry::DrawTriangleFan);
            geometryVector.append(tmpGeometry);
        }
#endif
    }

    QSGGeometry::Point2D *lineVertices = geometry->vertexDataAsPoint2D();

#ifndef Q_OS_ANDROID
    if (m_points != nullptr) { // && m_points->size() > 0) {
        for (int i = 0; i < LINE_POINTS / m_factor; i++) {
            lineVertices[i].set(m_coordPoints[i * m_factor].x, m_coordPoints[i * m_factor].y);
        }
    } else {
        for (int i = 0; i < LINE_POINTS / m_factor; i++) {
            lineVertices[i].set(-10, -10);
        }
    }
#else
    lineVertices[0].set(-10, -10);
#endif

#ifdef Q_OS_ANDROID
    if (m_points != nullptr) {
        if (geometryVector.size() > 0) {
            if (m_coordPoints.size() > 0) {
                for (int i = 0; i < LINE_POINTS  / m_factor; i++) {
                    QSGGeometryNode *tmpNode = nodeVector.at(i);
                    QSGGeometry::Point2D *vertices = geometryVector.at(i)->vertexDataAsPoint2D();
//                    if (m_newColor != m_color) {
                        QSGFlatColorMaterial *material = new QSGFlatColorMaterial;
                        material->setColor(m_color);
                        tmpNode->setMaterial(material);
                        tmpNode->setFlag(QSGNode::OwnsMaterial);
                        tmpNode->markDirty(QSGNode::DirtyMaterial);
//                    }


                    int cx;
                    int cy;
                    cx = m_coordPoints[i * m_factor].x;
                    cy = m_coordPoints[i * m_factor].y;

                    int r = m_lineWidth;
                    for(int ii = 0; ii < POINT_SEGMENTS; ii++) {
                        float theta = 2.0f * 3.1415926f * float(ii) / float(POINT_SEGMENTS);//get the current angle
                        qDebug() << theta;
                        float x = r * cos(theta);
                        float y = r * sin(theta);

                        vertices[ii].set(x + cx, y + cy);//output vertex
                    }
                    tmpNode->markDirty(QSGNode::DirtyGeometry);
                }
            }
        }
    } else if (nodeVector.size() > 0) {
        for (int i = 0; i < LINE_POINTS / m_factor; i++) {
            QSGGeometryNode *tmpNode = nodeVector.at(i);
            QSGGeometry::Point2D *vertices = geometryVector.at(i)->vertexDataAsPoint2D();
//                    if (m_newColor != m_color) {
                QSGFlatColorMaterial *material = new QSGFlatColorMaterial;
                material->setColor(m_color);
                tmpNode->setMaterial(material);
                tmpNode->setFlag(QSGNode::OwnsMaterial);
                tmpNode->markDirty(QSGNode::DirtyMaterial);
//                    }


            int cx;
            int cy;
            cx = -10;//m_points[i].x;
            cy = -10;//m_points[i].y;

            int r = m_lineWidth;
//            for(int ii = 0; ii < POINT_SEGMENTS; ii++) {
//                float theta = 2.0f * 3.1415926f * float(ii) / float(POINT_SEGMENTS);//get the current angle

//                float x = r * cos(theta);
//                float y = r * sin(theta);

//                qDebug() << cos(theta) << sin(theta);

//                vertices[ii].set(x + cx, y + cy);//output vertex
//            }

            vertices[0].set(cx + r, cy);
            vertices[1].set(cx, cy + r);
            vertices[2].set(cx - r, cy);
            vertices[3].set(cx, cy - r);

            tmpNode->markDirty(QSGNode::DirtyGeometry);
        }
    }
#endif

    node->markDirty(QSGNode::DirtyGeometry);
    m_newColor = m_color;
    return node;
}

void FunctionDisplayView::setUpdate(bool update)
{
    m_update = update;
}

int FunctionDisplayView::lineWidth() const
{
    return m_lineWidth;
}

void FunctionDisplayView::setLineWidth(int lineWidth)
{
    m_lineWidth = lineWidth;
    update();
}

void FunctionDisplayView::clear()
{
    for (int i = 0; i < m_coordPoints.size(); i++) {
        m_coordPoints[i].x = -10;
        m_coordPoints[i].y = -10;
    }

    update();
}

QColor FunctionDisplayView::color() const
{
    return m_color;
}

void FunctionDisplayView::setColor(const QColor &color)
{
    m_color = color;
    update();
}
