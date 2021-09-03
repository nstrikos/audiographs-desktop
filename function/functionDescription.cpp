#include "functionDescription.h"

#include <QDebug>

FunctionDescription::FunctionDescription()
{

}

QVector<InterestingPoint> FunctionDescription::points(FunctionModel *model)
{
    InterestingPoint tmp;
    m_points.clear();

    tmp.x = 0;
    tmp.y = model->y(0);
    tmp.label = "starting point";
    m_points.append(tmp);

    if (model == nullptr)
        return m_points;
    else {
        int prev = 0;
        int next = 0;
        for (int i = 0; i < model->size(); i++) {
            if (!model->isValid(i))
                continue;
            prev = i - 1;
            if (prev < 0)
                prev = 0;
            next = i + 1;
            if (next >= model->size())
                next = model->size() - 1;

            //            if (model->isValid(next)) {
            //                if (model->y(i) * model->y(next) <= 0) {
            //                    tmp.x = i;
            //                    tmp.y = model->y(i);
            //                    tmp.label = "zero";
            //                    m_points.append(tmp);
            //                }
            //            }

            //            if (model->isValid(next)) {
            //                if (model->x(i) == 0) {
            //                    tmp.x = i;
            //                    tmp.y = model->y(i);
            //                    tmp.label = "y crossing";
            //                    m_points.append(tmp);
            //                } else if (model->x(i) * model->x(next) < 0 && (model->x(i) < 0)) {
            //                    tmp.x = i;
            //                    tmp.y = model->y(i);
            //                    tmp.label = "y crossing";
            //                    m_points.append(tmp);
            //                }
            //            }

            if (!model->isValid(prev) && !model->isValid(next)) {
                tmp.x = i;
                tmp.y = model->y(i);
                tmp.label = "edge";
                m_points.append(tmp);
            } else if (!model->isValid(prev) && model->isValid(next)) {

                if (!model->validLimit(model->x(prev))) {

                    if (model->y(i) > model->y(next)) {
                        tmp.x = i;
                        tmp.y = model->y(i);
                        tmp.label = "maximum";
                        m_points.append(tmp);
                    }
                }
            } else if (model->isValid(prev) && !model->isValid(next)) {

                if (!model->validLimit(model->x(next))) {

                    if (model->y(i) > model->y(prev)) {
                        tmp.x = i;
                        tmp.y = model->y(i);
                        tmp.label = "maximum";
                        m_points.append(tmp);
                    }
                }
            } else if (model->isValid(prev) && model->isValid(next)) {
                if (model->y(i) > model->y(prev) && model->y(i) > model->y(next)) {
                    tmp.x = i;
                    tmp.y = model->y(i);
                    tmp.label = "local maximum";
                    m_points.append(tmp);
                }
            }

            if (!model->isValid(prev) && model->isValid(next)) {
                if (!model->validLimit(model->x(prev))) {

                    if (model->y(i) < model->y(next)) {
                        tmp.x = i;
                        tmp.y = model->y(i);
                        tmp.label = "minimum";
                        m_points.append(tmp);
                    }
                }
            } else if (model->isValid(prev) && !model->isValid(next)) {
                if (!model->validLimit(model->x(next))) {

                    if (model->y(i) < model->y(prev)) {
                        tmp.x = i;
                        tmp.y = model->y(i);
                        tmp.label = "minimum";
                        m_points.append(tmp);
                    }
                }
            } else if (model->isValid(prev) && model->isValid(next)) {
                if (model->y(i) < model->y(prev) && model->y(i) < model->y(next)) {
                    tmp.x = i;
                    tmp.y = model->y(i);
                    tmp.label = "local minimum";
                    m_points.append(tmp);
                }
            }
        }

        tmp.x = model->size() - 1;
        tmp.y = model->y(tmp.x);
        tmp.label = "ending point";
        m_points.append(tmp);

        return m_points;
    }
}
