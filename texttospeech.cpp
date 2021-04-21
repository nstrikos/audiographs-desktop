#include "texttospeech.h"

#include <QDebug>

TextToSpeech::TextToSpeech()
{
    m_parameters = &Parameters::getInstance();
    m_volume = m_parameters->volume();
    m_rate = m_parameters->rate();
    m_pitch = m_parameters->pitch();

    m_speech = nullptr;

    foreach (QString engine, QTextToSpeech::availableEngines())
        m_engines.append(engine);

    currentEngineChanged(0);
}

TextToSpeech::~TextToSpeech()
{

}

QVector<QVoice> TextToSpeech::voices() const
{
    return m_voices;
}

QStringList TextToSpeech::engines() const
{
    return m_engines;
}

void TextToSpeech::currentEngineChanged(int index)
{
    QString engineName = m_engines.at(index);

    if (m_speech != nullptr)
        delete m_speech;

    if (engineName == "default")
        m_speech = new QTextToSpeech(this);
    else
        m_speech = new QTextToSpeech(engineName, this);

    m_locales.clear();
    m_locales = m_speech->availableLocales();
    m_languages.clear();
    for (int i = 0; i < m_locales.size(); i++) {
        QLocale locale = m_locales.at(i);
        QString language = QLocale::languageToString(locale.language());
        m_languages.append(language);
    }

    emit languagesChanged();
}

void TextToSpeech::currentLanguageChanged(int index)
{
    m_voices.clear();
    m_voicesNames.clear();

    QLocale locale = m_locales.at(index);

    m_speech->setLocale(locale);

    m_voices = m_speech->availableVoices();

    for (int i = 0; i < m_voices.size(); i++) {
        m_voicesNames.append(m_voices.at(i).name());
    }

    emit voicesNamesChanged();
}

void TextToSpeech::currentVoiceChanged(int index)
{
    m_speech->setVoice(m_voices.at(index));
}

QString TextToSpeech::normalizeText(QString text)
{
    QString normText = text;
    normText.replace("(", " left parenthesis ");
    normText.replace(")", " right parenthesis ");
    normText.replace("^", " power ");
    normText.replace("+", " plus ");
    normText.replace("-", " minus ");
    normText.replace("*", " asterisk ");
    normText.replace("/", " slash ");
    normText.replace(",", " comma ");
    normText.replace(">", " greater than ");
    normText.replace("<", " less than ");
    normText.replace("=", " equals ");
    normText.replace(".", " period ");

    return normText;
}

QStringList TextToSpeech::voicesNames() const
{
    return m_voicesNames;
}

double TextToSpeech::volume() const
{
    return m_volume;
}

void TextToSpeech::setVolume(double volume)
{
    m_volume = volume / 100.0;
    m_speech->setVolume(m_volume);
    m_parameters->setVolume(m_volume);
}

double TextToSpeech::pitch() const
{
    return m_pitch;
}

void TextToSpeech::setPitch(double pitch)
{
    m_pitch = pitch / 100.0;
    m_speech->setPitch(m_pitch);
    m_parameters->setPitch(m_pitch);
}

double TextToSpeech::rate() const
{
    return m_rate;
}

void TextToSpeech::setRate(double rate)
{
    m_rate = rate / 100.0;
    m_speech->setRate(m_rate);
    m_parameters->setRate(m_rate);
}

QStringList TextToSpeech::languages() const
{
    return m_languages;
}

void TextToSpeech::speak(QString text)
{
    m_speech->say(text);
    qDebug() << text;
}

void TextToSpeech::stop()
{
    m_speech->stop();
}
