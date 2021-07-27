#include "parameters.h"

Parameters::~Parameters()
{
    write();
}

bool Parameters::showPoints() const
{
    return m_showPoints;
}

void Parameters::setShowPoints(bool showPoints)
{
    m_showPoints = showPoints;
    write();
}

bool Parameters::showLine() const
{
    return m_showLine;
}

void Parameters::setShowLine(bool showLine)
{
    m_showLine = showLine;
    write();
}

QColor Parameters::pointColor() const
{
    return m_pointColor;
}

void Parameters::setPointColor(const QColor &pointColor)
{
    m_pointColor = pointColor;
    write();
}

int Parameters::pointSize() const
{
    return m_pointSize;
}

void Parameters::setPointSize(int pointSize)
{
    m_pointSize = pointSize;
    write();
}

QColor Parameters::lineColor() const
{
    return m_lineColor;
}

void Parameters::setLineColor(const QColor &lineColor)
{
    m_lineColor = lineColor;
    write();
}

int Parameters::lineWidth() const
{
    return m_lineWidth;
}

void Parameters::setLineWidth(int lineWidth)
{
    m_lineWidth = lineWidth;
    write();
}

QColor Parameters::backgroundColor() const
{
    return m_backgroundColor;
}

void Parameters::setBackgroundColor(const QColor &backgroundColor)
{
    m_backgroundColor = backgroundColor;
    write();
}

QColor Parameters::highlightColor() const
{
    return m_highlightColor;
}

void Parameters::setHighlightColor(const QColor &highlightColor)
{
    m_highlightColor = highlightColor;
    write();
}

int Parameters::highlightSize() const
{
    return m_highlightSize;
}

void Parameters::setHighlightSize(int highlightSize)
{
    m_highlightSize = highlightSize;
    write();
}

void Parameters::read()
{
    QSettings settings("audiographs", "audiographs");

    QColor pointColor = settings.value(POINTCOLOR, "").value<QColor>();
    if (!pointColor.isValid())
        pointColor = Qt::blue;

    int pointSize = settings.value("pointSize", 5).toInt();

    QColor lineColor = settings.value("lineColor", "").value<QColor>();
    if (!lineColor.isValid())
        lineColor = Qt::red;

    int lineWidth = settings.value("lineWidth", 4).toInt();

    QColor backgroundColor = settings.value("backgroundColor", "").value<QColor>();
    if (!backgroundColor.isValid())
        backgroundColor = Qt::white;

    QColor highlightColor = settings.value("highlightColor", "").value<QColor>();
    if (!highlightColor.isValid())
        highlightColor = "#00ddff";

    int highlightSize = settings.value("highlightSize", 20).toInt();

    QColor axesColor = settings.value("axesColor", "").value<QColor>();
    if (!axesColor.isValid())
        axesColor = "#000000";

    int axesSize = settings.value("axesSize", 4).toInt();

    bool showPoints = settings.value("showPoints", true).toBool();

    bool showLine = settings.value("showLine", true).toBool();

    bool showAxes = settings.value("showAxes", true).toBool();
    bool invertTheme = settings.value("invertTheme", false).toBool();

    double volume = settings.value("volume", 1.0).toDouble();
    double rate = settings.value("rate", 0.5).toDouble();
    double pitch = settings.value("pitch", 0.5).toDouble();

    int duration = settings.value("duration", 15).toInt();
    int minFreq = settings.value("minFreq", 200).toInt();
    int maxFreq = settings.value("maxFreq", 2000).toInt();
    bool useNotes = settings.value("useNotes", false).toBool();
    bool useNegativeNotes = settings.value("useNegativeNotes", false).toBool();
    bool exploreMode = settings.value("exploreMode", false).toBool();
    int precisionDigits = settings.value("precisionDigits", 2).toInt();

    bool selfVoice = settings.value("selfVoice", true).toBool();

    QColor derivColor = settings.value("derivColor", "").value<QColor>();
    if (!derivColor.isValid())
        derivColor = Qt::green;

    bool intro = settings.value("intro", true).toBool();


    setPointColor(pointColor);
    setPointSize(pointSize);
    setLineColor(lineColor);
    setLineWidth(lineWidth);
    setBackgroundColor(backgroundColor);
    setHighlightColor(highlightColor);
    setHighlightSize(highlightSize);
    setAxesColor(axesColor);
    setAxesSize(axesSize);
    setShowPoints(showPoints);
    setShowLine(showLine);
    setShowAxes(showAxes);
    setInvertTheme(invertTheme);
    setVolume(volume);
    setRate(rate);
    setPitch(pitch);
    setDuration(duration);
    setMinFreq(minFreq);
    setMaxFreq(maxFreq);
    setUseNotes(useNotes);
    setUseNegativeNotes(useNegativeNotes);
    setExploreMode(exploreMode);
    setPrecisionDigits(precisionDigits);
    setSelfVoice(selfVoice);
    setDerivColor(derivColor);
    setIntro(intro);
}

void Parameters::write()
{
    QSettings settings("audiographs", "audiographs");

    settings.setValue(POINTCOLOR, m_pointColor);
    settings.setValue("pointSize", m_pointSize);
    settings.setValue("lineColor", m_lineColor);
    settings.setValue("lineWidth", m_lineWidth);
    settings.setValue("backgroundColor", m_backgroundColor);
    settings.setValue("highlightColor", m_highlightColor);
    settings.setValue("highlightSize", m_highlightSize);
    settings.setValue("axesColor", m_axesColor);
    settings.setValue("axesSize", m_axesSize);
    settings.setValue("showPoints", m_showPoints);
    settings.setValue("showLine", m_showLine);
    settings.setValue("showAxes", m_showAxes);
    settings.setValue("invertTheme", m_invertTheme);
    settings.setValue("volume", m_volume);
    settings.setValue("rate", m_rate);
    settings.setValue("pitch", m_pitch);
    settings.setValue("duration", m_duration);
    settings.setValue("minFreq", m_minFreq);
    settings.setValue("maxFreq", m_maxFreq);
    settings.setValue("useNotes", m_useNotes);
    settings.setValue("useNegativeNotes", m_useNegativeNotes);
    settings.setValue("exploreMode", m_exploreMode);
    settings.setValue("precisionDigits", m_precisionDigits);
    settings.setValue("selfVoice", m_selfVoice);
    settings.setValue("derivColor", m_derivColor);
    settings.setValue("intro", m_intro);
    settings.sync();
 }

void Parameters::reset()
{
    setPointColor(Qt::blue);
    setPointSize(5);
    setLineColor(Qt::red);
    setLineWidth(4);
    setBackgroundColor(Qt::white);
    setDerivColor(Qt::green);
    setHighlightColor("#00ddff");
    setHighlightSize(20);
    setAxesColor(Qt::black);
    setAxesSize(4);
    setShowPoints(true);
    setShowLine(true);
    setShowAxes(true);
    setInvertTheme(false);
    setExploreMode(false);
}

void Parameters::resetAudio()
{
    setDuration(15);
    setMinFreq(200);
    setMaxFreq(2000);
    setUseNotes(false);
    setUseNegativeNotes(false);
    setPrecisionDigits(2);
    setSelfVoice(true);
}

QColor Parameters::axesColor() const
{
    return m_axesColor;
}

void Parameters::setAxesColor(const QColor &axesColor)
{
    m_axesColor = axesColor;
    write();
}

bool Parameters::showAxes() const
{
    return m_showAxes;
}

void Parameters::setShowAxes(bool showAxes)
{
    m_showAxes = showAxes;
    write();
}

int Parameters::axesSize() const
{
    return m_axesSize;
}

void Parameters::setAxesSize(int axesSize)
{
    m_axesSize = axesSize;
    write();
}

double Parameters::volume() const
{
    return m_volume;
}

void Parameters::setVolume(double volume)
{
    m_volume = volume;
}

double Parameters::rate() const
{
    return m_rate;
}

void Parameters::setRate(double rate)
{
    m_rate = rate;
    write();
}

double Parameters::pitch() const
{
    return m_pitch;
}

void Parameters::setPitch(double pitch)
{
    m_pitch = pitch;
    write();
}

int Parameters::duration() const
{
    return m_duration;
}

void Parameters::setDuration(int duration)
{
    m_duration = duration;
    write();
}

int Parameters::minFreq() const
{
    return m_minFreq;
}

void Parameters::setMinFreq(int minFreq)
{
    m_minFreq = minFreq;
    if (m_minFreq < 200)
        m_minFreq = 200;
    if (m_minFreq > 4000)
        m_minFreq = 4000;

    write();
}

int Parameters::maxFreq() const
{
    return m_maxFreq;
}

void Parameters::setMaxFreq(int maxFreq)
{
    m_maxFreq = maxFreq;
    if (m_maxFreq < 400)
        m_maxFreq = 400;
    if (m_maxFreq > 8000)
        m_maxFreq = 8000;
    write();
}

bool Parameters::useNotes() const
{
    return m_useNotes;
}

void Parameters::setUseNotes(bool value)
{
    m_useNotes = value;
    write();
}

bool Parameters::useNegativeNotes() const
{
    return m_useNegativeNotes;
}

void Parameters::setUseNegativeNotes(bool value)
{
    m_useNegativeNotes = value;
    write();
}

bool Parameters::invertTheme() const
{
    return m_invertTheme;
}

void Parameters::setInvertTheme(bool invertTheme)
{
    m_invertTheme = invertTheme;
    write();
}

bool Parameters::exploreMode() const
{
    return m_exploreMode;
}

void Parameters::setExploreMode(bool exploreMode)
{
    m_exploreMode = exploreMode;
    write();
}

int Parameters::precisionDigits() const
{
    return m_precisionDigits;
}

void Parameters::setPrecisionDigits(int precisionDigits)
{
    m_precisionDigits = precisionDigits;
    if (m_precisionDigits < 0)
        m_precisionDigits = 0;
    if (m_precisionDigits > 5)
        m_precisionDigits = 5;
    write();
}

bool Parameters::selfVoice() const
{
    return m_selfVoice;
}

void Parameters::setSelfVoice(bool selfVoice)
{
    m_selfVoice = selfVoice;
}

QColor Parameters::derivColor() const
{
    return m_derivColor;
}

void Parameters::setDerivColor(const QColor &derivColor)
{
    m_derivColor = derivColor;
}

bool Parameters::intro() const
{
    return m_intro;
}

void Parameters::setIntro(bool newIntro)
{
    m_intro = newIntro;
}
