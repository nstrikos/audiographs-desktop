TARGET = audiographs-desktop

QT       += core gui multimedia texttospeech quick

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

#QMAKE_CXXFLAGS += -bigobj

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    aboutDialog.cpp \
    audionotes/audionotes.cpp \
    audionotes/audiopoints.cpp \
    errorDisplayDialog.cpp \
    function/currentPoint.cpp \
    function/dragHandler.cpp \
    function/functionConnector.cpp \
    function/functionDescription.cpp \
    function/functionDisplayView.cpp \
    function/functionDisplayViewInterface.cpp \
    function/functionExpression.cpp \
    function/functionModel.cpp \
    function/functionPointView.cpp \
    function/functionZoomer.cpp \
    function/pinchHandler.cpp \
    function/point.cpp \
    function/pointInterest.cpp \
    generator/audio.cpp \
    generator/audioengine.cpp \
    generator/genclipper.cpp \
    generator/generator.cpp \
    generator/genfunctioncalculator.cpp \
    generator/genmaxfinder.cpp \
    generator/genminfinder.cpp \
    generator/genmod.cpp \
    generator/genmodvalues.cpp \
    generator/genparameters.cpp \
    generator/genphicalculator.cpp \
    generator/gensum.cpp \
    main.cpp \
    mainwindow.cpp \
    parameters.cpp \
    renderArea.cpp \
    texttospeech.cpp

HEADERS += \
    aboutDialog.h \
    audionotes/audionotes.h \
    audionotes/audiopoints.h \
    constants.h \
    errorDisplayDialog.h \
    function/currentPoint.h \
    function/dragHandler.h \
    function/functionConnector.h \
    function/functionDescription.h \
    function/functionDisplayView.h \
    function/functionDisplayViewInterface.h \
    function/functionExpression.h \
    function/functionModel.h \
    function/functionPointView.h \
    function/functionZoomer.h \
    function/pinchHandler.h \
    function/point.h \
    function/pointInterest.h \
    generator/audio.h \
    generator/audioengine.h \
    generator/genclipper.h \
    generator/generator.h \
    generator/genfunctioncalculator.h \
    generator/genmaxfinder.h \
    generator/genminfinder.h \
    generator/genmod.h \
    generator/genmodvalues.h \
    generator/genparameters.h \
    generator/genphicalculator.h \
    generator/gensum.h \
    mainwindow.h \
    parameters.h \
    renderArea.h \
    texttospeech.h

linux:!android: {
   HEADERS += parsers/exprtk/exprtk.hpp
} else: {
SOURCES += parsers/fparser/fparser.cc \
    parsers/fparser/fpoptimizer.cc \

HEADERS +=   parsers/fparser/extrasrc/fpaux.hh \
   parsers/fparser/extrasrc/fptypes.hh \
   parsers/fparser/fparser.hh \
   parsers/fparser/fparser_gmpint.hh \
   parsers/fparser/fparser_mpfr.hh \
   parsers/fparser/fpconfig.hh \
}

FORMS += \
    aboutDialog.ui \
    errorDisplayDialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32: {
DISTFILES += \
    parsers/fparser/extrasrc/fp_identifier_parser.inc \
    parsers/fparser/extrasrc/fp_opcode_add.inc
}

RESOURCES += \
    help.qrc \
    qml.qrc

DISTFILES +=

RC_ICONS = audiographs.ico
