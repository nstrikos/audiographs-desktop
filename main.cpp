#include "mainwindow.h"

#include <QApplication>

#include "function/functionExpression.h"
#include "function/functionConnector.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "function/functionDisplayView.h"
#include "function/functionPointView.h"
#include "function/functionExpression.h"
#include "function/point.h"

#include "texttospeech.h"

int main(int argc, char *argv[])
{
    bool runMobile = false;

#ifdef Q_OS_ANDROID
    runMobile = true;
#endif

    if ((argc == 2) && (strcmp(argv[1], "--mobile") == 0))
        runMobile = true;

    if (!runMobile) {
        QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
        QApplication a(argc, argv);
        MainWindow w;
        w.showMaximized();

        FunctionExpression functionExpression;

        FunctionConnector functionConnector;

        functionConnector.start(w, functionExpression);

        return a.exec();
    } else {
        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

        QGuiApplication app(argc, argv);

        app.setOrganizationName("Nick Strikos");
        app.setOrganizationDomain("nstrikos@yahoo.gr");
        app.setApplicationName("audiographs");

        qmlRegisterType<FunctionDisplayView>("DisplayView", 1, 0, "DisplayView");
        qmlRegisterType<FunctionPointView>("PointView", 1, 0, "PointView");
        qmlRegisterType<Points>("Points", 1, 0, "Points");

        Parameters *parameters = &Parameters::getInstance();
        FunctionExpression functionExpression;
        TextToSpeech textToSpeech;

        QQmlApplicationEngine engine;
        engine.rootContext()->setContextProperty("parameters", parameters);
        engine.rootContext()->setContextProperty("functionExpression", &functionExpression);
        engine.rootContext()->setContextProperty("textToSpeech", &textToSpeech);
        //qRegisterMetaType<FunctionController*>("FunctionController*");


        const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
        QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                         &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
        engine.load(url);

        QObject *rootObject = engine.rootObjects().first();
        QObject *qmlPointView = rootObject->findChild<QObject*>("pointView");
        QObject *qmlDisplayView = rootObject->findChild<QObject*>("displayView");
        QObject *qmlDerivativeView = rootObject->findChild<QObject*>("derivativeView");

        //            FunctionPointView *pointView = static_cast<FunctionPointView*>(qmlPointView);
        FunctionDisplayView *displayView = static_cast<FunctionDisplayView*>(qmlDisplayView);
        QObject::connect(&functionExpression, &FunctionExpression::newGraph, displayView, &FunctionDisplayView::draw);
        QObject::connect(&functionExpression, &FunctionExpression::error, displayView, &FunctionDisplayView::clear);

        FunctionPointView *pointView = static_cast<FunctionPointView*>(qmlPointView);
        QObject::connect(&functionExpression, &FunctionExpression::newGraph, pointView, &FunctionPointView::draw);
        QObject::connect(&functionExpression, &FunctionExpression::newCurrentPoint, pointView, &FunctionPointView::setCurrentPoint);

        FunctionDisplayView *derivativeView = static_cast<FunctionDisplayView*>(qmlDerivativeView);
        QObject::connect(&functionExpression, &FunctionExpression::updateDerivative, derivativeView, &FunctionDisplayView::draw);
        QObject::connect(&functionExpression, &FunctionExpression::error, derivativeView, &FunctionDisplayView::clear);

        return app.exec();
    }
}
