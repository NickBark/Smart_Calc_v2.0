QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    basecalc.cpp \
    creditcalc.cpp \
    customgraph.cpp \
    depositcalc.cpp \
    graph.cpp \
    main.cpp \
    mainframe.cpp \
    mainwindow.cpp \
    qcustomplot.cpp

HEADERS += \
    basecalc.h \
    creditcalc.h \
    customgraph.h \
    dependencies.hpp \
    depositcalc.h \
    graph.hpp \
    mainframe.h \
    mainwindow.hpp \
    qcustomplot.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../release/ -ls21_calc_core
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../debug/ -ls21_calc_core
else:unix: LIBS += -L$$PWD/../ -ls21_calc_core

INCLUDEPATH += $$PWD/../
DEPENDPATH += $$PWD/../

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../release/libs21_calc_core.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../debug/libs21_calc_core.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../release/s21_calc_core.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../debug/s21_calc_core.lib
else:unix: PRE_TARGETDEPS += $$PWD/../libs21_calc_core.a
