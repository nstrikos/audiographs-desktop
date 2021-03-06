#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStateMachine>

#include "function/point.h"
#include "parameters.h"

#include <QMenu>
#include <QAction>

#include "errorDisplayDialog.h"
#include "helpDialog.h"
#include "aboutDialog.h"
#include "texttospeech.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class KeyReceiver;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    bool eventFilter(QObject* obj, QEvent* event);

signals:
    void calculate(QString expression, QString minX, QString maxX, QString minY, QString maxY);
    void evaluate();
    void functionError();
    void newgraph();
    void playPressed();
    void playSound();
    void stopSound();
    void audioFinished();
    void newCurrentPoint(double x, double y);
    void nextPoint();
    void previousPoint();
    void sayX();
    void sayY();
    void sayDerivative();
    void decStep();
    void incStep();
    void previousPointInterest();
    void nextPointInterest();
    void externalPreviousPointInterest();
    void externalNextPointInterest();
    void interestingPointFinished();
    void stopInterestingPoint();
    void previousFast();
    void nextFast();
    void externalPreviousFast();
    void externalNextFast();
    void firstPoint();
    void lastPoint();
    void errorAccepted();
    void derivativeMode(int mode);

public slots:
    void updateGraph(QVector<Point> *points, double minX, double maxX, double minY, double maxY);
    void updateDerivative(QVector<Point> *points, double minX, double maxX, double minY, double maxY);

    void error(QString errorString);

    void on_startSoundPushButton_clicked();

    void on_nextPushButton_clicked();

    void on_previousPushButton_clicked();

    void on_nextPointInterestPushButton_clicked();

    void on_previousPointInterestPushButton_clicked();

    void on_xPushButton_clicked();

    void on_yPushButton_clicked();

    void on_previousFastPushButton_clicked();

    void on_nextFastPushButton_clicked();

    void on_firstPointPushButton_clicked();

    void on_lastPointPushButton_clicked();

    void exit();

private slots:
    void initialStateActivated();
    void evaluateStateActivated();
    void graphReadyStateActivated();
    void playSoundStateActivated();
    void playSoundStateDeactivated();
    void exploreStateActivated();
    void exploreStateDeactivated();
    void interestingPointStateActivated();
    void interestingPointStateDeactivated();
    void interestingPointStoppedStateActivated();
    void interestingPointStoppedStateDeactivated();
    void errorDisplayStateActivated();

    void on_functionLineEdit_textEdited(const QString &arg1);
    void zoom(int delta);
    void mousePressed(int x, int y);
    void mouseMove(int diffX, int diffY);
    void mouseReleased();

    void on_minXLineEdit_textEdited(const QString &arg1);

    void on_maxXLineEdit_textEdited(const QString &arg1);

    void on_minYLineEdit_textEdited(const QString &arg1);

    void on_maxYLineEdit_textEdited(const QString &arg1);

    void on_graphColorPushButton_clicked();

    void on_backgroundColorPushButton_clicked();

    void on_highlightColorPushButton_clicked();

    void on_axesColorPushButton_clicked();

    void on_resetGraphSettingsPushButton_clicked();

    void on_resetAudioPushButton_clicked();

    void newExpression();

    void quit();

    void on_decStepPushButton_clicked();

    void on_incStepPushButton_clicked();

    void on_functionLineEdit_cursorPositionChanged(int arg1, int arg2);
    void selfVoiceActionActivated();
    void useNotesActionActivated();
    void useNegativeNotesActionActivated();

    void on_normalModePushButton_clicked();

    void on_firstDerivativePushButton_clicked();

    void on_secondDerivativePushButton_clicked();

    void durationSpinBoxValueChanged(int value);
    void minFreqSpinBoxValueChanged(int value);
    void maxFreqSpinBoxValueChanged(int value);
    void precisionDigitsSpinboxValueChanged(int value);
    void selfVoiceCheckBoxStateChanged();
    void useNotesCheckBoxStateChanged();
    void useNegativeNotesCheckBoxStateChanged();
    void graphWidthSpinBoxValueChanged(int value);
    void highlightSizeSpinBoxValueChanged(int value);
    void axesSizeSpinBoxValueChanged(int value);
    void showGridCheckBoxStateChanged();

    void on_derivativeColorPushButton_clicked();

    void showShortcuts();
    void closeShortcuts();
    void showAboutDialog();
    void closeAboutDialog();

    void sayWidget();

    void openRecentFile();

    void on_derivativePushButton_clicked();

private:
    Ui::MainWindow *ui;

    void initActions();
    void initMenu();
    void initStateMachine();
    void setButtonColors();
    void initGraphControls();
    void enableControls();
    void disableControls();

    QStateMachine stateMachine;
    QState initialState, errorDisplayState, evaluateState, graphReadyState,
    playSoundState, exploreState, interestingPointState, interestingPointStoppedState;

    QVector<Point> *m_points;
    QVector<Point> *m_derivPoints;
    double m_minX, m_maxX, m_minY, m_maxY;

    bool m_mousePressed = false;
    int m_xStartDrag, m_yStartDrag;
    double m_minXDrag, m_maxXDrag, m_minYDrag, m_maxYDrag;

    Parameters *m_parameters;

    QAction *newExpressionAction;
    QAction *startSoundButtonAction;
    QAction *nextAction;
    QAction *previousAction;
    QAction *sayXAction;
    QAction *sayYAction;
    QAction *sayDerivativeAction;
    QAction *incStepAction;
    QAction *decStepAction;
    QAction *previousInterestPointAction;
    QAction *nextInterestPointAction;
    QAction *nextFastAction;
    QAction *previousFastAction;
    QAction *firstPointAction;
    QAction *lastPointAction;
    QAction *selfVoiceAction;
    QAction *useNotesAction;
    QAction *useNegativeNotesAction;
    QAction *normalModeAction;
    QAction *firstDerivativeModeAction;
    QAction *secondDerivativeModeAction;
    QAction *showShortcutsAction;
    QAction *aboutAction;
    QMenu *helpMenu;
    QMenu *fileMenu;
    QMenu *controlMenu;

    bool canZoomDrag = false;

    KeyReceiver *keyReceiver;

    ErrorDisplayDialog *errorDisplayDialog;
    HelpDialog *helpDialog;
    AboutDialog *aboutDialog;
    QString m_errorString;

    TextToSpeech *m_textToSpeech;

    void accessText(QWidget *widget, QString text);
    QString normalizeText(QString text);

    void readSettings();
    void writeSettings();

    void updateRecentFileActions();
    enum {MaxRecentFiles = 9};
    QStringList recentFiles;
    QAction *recentFileActions[MaxRecentFiles];
    QAction *separatorAction;
    QAction *exitAction;

    QString helpFile;
};
#endif // MAINWINDOW_H
