QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../src/controller/calculator_controller.cpp \
    ../src/controller/credit_controller.cpp \
    ../src/model/calculator_model.cpp \
    ../src/model/credit_model.cpp \
    ../src/view/choosewindow.cpp \
    ../src/view/creditwindow.cpp \
    ../src/view/main.cpp \
    ../src/view/mainwindow.cpp \
    ../src/view/plotwindow.cpp \
    ../src/qcustomplot.cpp

HEADERS += \
    ../src/controller/calculator_controller.h \
    ../src/controller/credit_controller.h \
    ../src/model/calculator_model.h \
    ../src/model/credit_model.h \
    ../src/view/choosewindow.h \
    ../src/view/creditwindow.h \
    ../src/view/mainwindow.h \
    ../src/view/plotwindow.h \
    ../src/qcustomplot.h

FORMS += \
    ../src/view/ui/choosewindow.ui \
    ../src/view/ui/creditwindow.ui \
    ../src/view/ui/mainwindow.ui \
    ../src/view/ui/plotwindow.ui

ICON = ../src/view/icns/SmartCalcV2.icns


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
