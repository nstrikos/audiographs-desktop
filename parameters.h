#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <QObject>
#include <QString>
#include <QColor>
#include <QPoint>
#include <QSettings>

class Parameters : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QColor pointColor READ pointColor WRITE setPointColor NOTIFY pointColorChanged)
    Q_PROPERTY(int pointSize READ pointSize WRITE setPointSize NOTIFY pointSizeChanged)
    Q_PROPERTY(QColor lineColor READ lineColor WRITE setLineColor NOTIFY lineColorChanged)
    Q_PROPERTY(int lineWidth READ lineWidth WRITE setLineWidth NOTIFY lineWidthChanged)
    Q_PROPERTY(QColor highlightColor READ highlightColor WRITE setHighlightColor NOTIFY highlightColorChanged)
    Q_PROPERTY(int highlightSize READ highlightSize WRITE setHighlightSize NOTIFY highlightSizeChanged)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)
    Q_PROPERTY(bool showPoints READ showPoints WRITE setShowPoints NOTIFY showPointsChanged)
    Q_PROPERTY(bool showLine READ showLine WRITE setShowLine NOTIFY showLineChanged)
    Q_PROPERTY(QColor axesColor READ axesColor WRITE setAxesColor NOTIFY axesColorChanged)
    Q_PROPERTY(int axesSize READ axesSize WRITE setAxesSize NOTIFY axesSizeChanged)
    Q_PROPERTY(bool showAxes READ showAxes WRITE setShowAxes NOTIFY showAxesChanged)
    Q_PROPERTY(bool invertTheme READ invertTheme WRITE setInvertTheme NOTIFY invertThemeChanged)
    Q_PROPERTY(double volume READ volume WRITE setVolume NOTIFY volumeChanged)
    Q_PROPERTY(double rate READ rate WRITE setRate NOTIFY rateChanged)
    Q_PROPERTY(double pitch READ pitch WRITE setPitch NOTIFY pitchChanged)
    Q_PROPERTY(int duration READ duration WRITE setDuration NOTIFY durationChanged)
    Q_PROPERTY(int minFreq READ minFreq WRITE setMinFreq NOTIFY minFreqChanged)
    Q_PROPERTY(int maxFreq READ maxFreq WRITE setMaxFreq NOTIFY maxFreqChanged)
    Q_PROPERTY(bool useNotes READ useNotes WRITE setUseNotes NOTIFY useNotesChanged)
    Q_PROPERTY(bool useNegativeNotes READ useNegativeNotes WRITE setUseNegativeNotes NOTIFY useNegativeNotesChanged)
    Q_PROPERTY(bool exploreMode READ exploreMode WRITE setExploreMode NOTIFY exploreModeChanged)
    Q_PROPERTY(int precisionDigits READ precisionDigits WRITE setPrecisionDigits NOTIFY precisionDigitsChanged)
    Q_PROPERTY(bool selfVoice READ selfVoice WRITE setSelfVoice NOTIFY selfVoiceChanged)
    Q_PROPERTY(QColor derivColor READ derivColor WRITE setDerivColor NOTIFY derivColorChanged)
    Q_PROPERTY(bool intro READ intro WRITE setIntro NOTIFY introChanged)

public:
    static Parameters& getInstance()
    {
        static Parameters instance;
        return instance;
    }
    ~Parameters();

    bool showPoints() const;
    void setShowPoints(bool showPoints);

    bool showLine() const;
    void setShowLine(bool showLine);

    QColor pointColor() const;
    void setPointColor(const QColor &pointColor);

    int pointSize() const;
    void setPointSize(int pointSize);

    QColor lineColor() const;
    void setLineColor(const QColor &lineColor);

    int lineWidth() const;
    void setLineWidth(int lineWidth);

    QColor backgroundColor() const;
    void setBackgroundColor(const QColor &backgroundColor);

    QColor highlightColor() const;
    void setHighlightColor(const QColor &highlightColor);

    int highlightSize() const;
    void setHighlightSize(int highlightSize);

    void read();
    void write();
    Q_INVOKABLE void reset();
    Q_INVOKABLE void resetAudio();

    QColor axesColor() const;
    void setAxesColor(const QColor &axesColor);

    bool showAxes() const;
    void setShowAxes(bool showAxes);

    int axesSize() const;
    void setAxesSize(int axesSize);

    double volume() const;
    void setVolume(double volume);

    double rate() const;
    void setRate(double rate);

    double pitch() const;
    void setPitch(double pitch);

    int duration() const;
    void setDuration(int duration);

    int minFreq() const;
    void setMinFreq(int minFreq);

    int maxFreq() const;
    void setMaxFreq(int maxFreq);

    bool useNotes() const;
    void setUseNotes(bool value);

    bool useNegativeNotes() const;
    void setUseNegativeNotes(bool value);

    bool invertTheme() const;
    void setInvertTheme(bool invertTheme);

    bool exploreMode() const;
    void setExploreMode(bool exploreMode);

    int precisionDigits() const;
    void setPrecisionDigits(int precisionDigits);

    bool selfVoice() const;
    void setSelfVoice(bool selfVoice);

    QColor derivColor() const;
    void setDerivColor(const QColor &derivColor);

    bool intro() const;
    void setIntro(bool newIntro);

private:
    Parameters() {
        read();
    }
    Parameters(Parameters const&);     // Don't Implement
    void operator=(Parameters const&); // Don't implement

    bool m_showPoints;
    bool m_showLine;
    bool m_showAxes;
    QColor m_pointColor;
    int m_pointSize;
    QColor m_lineColor;
    int m_lineWidth;
    QColor m_backgroundColor;
    QColor m_highlightColor;
    QColor m_axesColor;
    int m_axesSize;
    int m_highlightSize;
    bool m_invertTheme;
    double m_volume;
    double m_rate;
    double m_pitch;
    int m_duration;
    int m_minFreq;
    int m_maxFreq;
    bool m_useNotes;
    bool m_useNegativeNotes;
    bool m_exploreMode;
    int m_precisionDigits;
    bool m_selfVoice;
    QColor m_derivColor;
    bool m_intro;

    const QString POINTCOLOR = "pointColor";

signals:
    void pointColorChanged();
    void pointSizeChanged();
    void lineColorChanged();
    void lineWidthChanged();
    void highlightColorChanged();
    void highlightSizeChanged();
    void backgroundColorChanged();
    void showPointsChanged();
    void showLineChanged();
    void axesColorChanged();
    void axesSizeChanged();
    void showAxesChanged();
    void invertThemeChanged();
    void volumeChanged();
    void rateChanged();
    void pitchChanged();
    void durationChanged();
    void minFreqChanged();
    void maxFreqChanged();
    void useNotesChanged();
    void useNegativeNotesChanged();
    void exploreModeChanged();
    void precisionDigitsChanged();
    void selfVoiceChanged();
    void derivColorChanged();
    void introChanged();
};

#endif // PARAMETERS_H
