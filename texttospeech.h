#ifndef TEXTTOSPEECH_H
#define TEXTTOSPEECH_H

#include <QObject>
#include <QTextToSpeech>
#include <QString>
#include <QVector>
#include "parameters.h"


class TextToSpeech : public QObject
{
    Q_OBJECT

public:
    TextToSpeech();
    ~TextToSpeech();

    Q_PROPERTY(QStringList engines  READ engines NOTIFY enginesChanged())
    Q_PROPERTY(QStringList languages  READ languages NOTIFY languagesChanged())
    Q_PROPERTY(QStringList voicesNames READ voicesNames NOTIFY voicesNamesChanged())
    Q_PROPERTY(double volume READ volume WRITE setVolume NOTIFY volumeChanged)
    Q_PROPERTY(double pitch READ pitch WRITE setPitch NOTIFY pitchChanged)
    Q_PROPERTY(double rate READ rate WRITE setRate NOTIFY rateChanged)

    QVector<QVoice> voices() const;

    QStringList engines() const;
    QStringList languages() const;

    Q_INVOKABLE void speak(QString text);
    Q_INVOKABLE void stop();
    Q_INVOKABLE void currentEngineChanged(int index);
    Q_INVOKABLE void currentLanguageChanged(int index);
    Q_INVOKABLE void currentVoiceChanged(int index);
    Q_INVOKABLE QString normalizeText(QString text);

    QStringList voicesNames() const;

    double volume() const;
    void setVolume(double volume);

    double pitch() const;
    void setPitch(double pitch);

    double rate() const;
    void setRate(double rate);

signals:
    void enginesChanged();
    void languagesChanged();
    void voicesNamesChanged();
    void volumeChanged();
    void pitchChanged();
    void rateChanged();

private:
    QTextToSpeech *m_speech;
    QVector<QVoice> m_voices;
    QStringList m_languages;
    QStringList m_engines;
    QStringList m_voicesNames;
    QVector<QLocale> m_locales;
    QLocale m_locale;
    double m_volume;
    double m_pitch;
    double m_rate;
    Parameters *m_parameters;
};

#endif // TEXTTOSPEECH_H
