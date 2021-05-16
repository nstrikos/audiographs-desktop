#ifndef CONSTANTS_H
#define CONSTANTS_H

#endif // CONSTANTS_H

#include <QColor>

#ifndef Q_OS_ANDROID
const int LINE_POINTS = 10000;
#else
const int LINE_POINTS = 10000;
#endif

const int INTERVAL_MILLISECONDS = 40;
const int POINT_SEGMENTS = 4;

/*
const int LINE_WIDTH = 10;

#ifndef Q_OS_ANDROID
const int POINT_SEGMENTS = 64;
#else
const int POINT_SEGMENTS = 16;
#endif

const QColor DEFAULT_LINE_COLOR = QColor(255, 0, 0);
const QColor DEFAULT_POINT_COLOR = QColor(0, 0, 255);

const int MIN_POINTS = 1;
const int MAX_POINTS = 10000;
*/
