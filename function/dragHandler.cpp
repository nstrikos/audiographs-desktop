#include "dragHandler.h"
#include "functionModel.h"

DragHandler::DragHandler()
{

}

void DragHandler::startDrag(FunctionModel &model, int x, int y)
{
    if (!model.validExpression())
        return;

    m_dragX = x;
    m_dragY = y;
    m_minX = model.minX();
    m_maxX = model.maxX();
    m_minY = model.minY();
    m_maxY = model.maxY();
}

void DragHandler::drag(FunctionModel &model, int diffX, int diffY, int width, int height, int derivMode)
{
    if (!model.validExpression())
        return;

    //The level of precision in rounding depends on the distance between the values
    double distanceX = m_maxX - m_minX;

    int powerX = -floor(log10(distanceX)) + 2;

    //variable precisionX holds the level of precision
    double precisionX = pow(10, powerX);

    double distanceY = m_maxY - m_minY;

    int powerY = -floor(log10(distanceY)) + 2;
    double precisionY = pow(10, powerY);

    int newDiffX = diffX - m_dragX;
    int newDiffY = diffY - m_dragY;

    double diffXDouble = (double)((m_maxX - m_minX)) / (double)width * newDiffX;
    double diffYDouble = (double)((m_maxY - m_minY)) / (double)height * newDiffY;

    //newMinX, newMaxX, newMinY, newMaxY are the new values
    double newMinX, newMaxX, newMinY, newMaxY;

    if (powerX > 0) {
        newMinX = round( (m_minX - diffXDouble) * precisionX) / precisionX;
        newMaxX = round( (m_maxX - diffXDouble) * precisionY) / precisionY;
    } else {
        newMinX = round(m_minX - diffXDouble);
        newMaxX = round(m_maxX - diffXDouble);
    }

    if (powerY > 0) {
        newMinY = round( (m_minY + diffYDouble) * precisionY) / precisionY;
        newMaxY = round( (m_maxY + diffYDouble) * precisionY) / precisionY;
    } else {
        newMinY = round(m_minY + diffYDouble);
        newMaxY = round(m_maxY + diffYDouble);
    }


    //    //we update with the rounded values
    model.calculate(model.expression(),
                    QString::number(newMinX),
                    QString::number(newMaxX),
                    QString::number(newMinY),
                    QString::number(newMaxY));

    if (derivMode == 1)
        model.calculateDerivative();
    else if (derivMode == 2)
        model.calculateSecondDerivative();
    emit newInputValues(newMinX, newMaxX, newMinY, newMaxY);
}
