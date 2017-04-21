QT += qml gui quick positioning location

CONFIG += c++11

SOURCES += main.cpp \
    XbeeInterface.cpp

RESOURCES += qml.qrc \
    images/marker.png \
    images/quadcopter.png \
    images/target.png

LIBS += \
    -lboost_system\
    -lboost_thread\


# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    marker.png \
    math.min.js

HEADERS += \
    XbeeInterface.hpp

INCLUDEPATH += $$PWD/../CommProto-MessageStandards2017/packets/cpp

unix:!macx: LIBS += -L$$PWD/../CommProtocol/build/ -lCommProtocol-Static

INCLUDEPATH += $$PWD/../CommProtocol/CommProto/include
DEPENDPATH += $$PWD/../CommProtocol/CommProto/include

unix:!macx: PRE_TARGETDEPS += $$PWD/../CommProtocol/build/libCommProtocol-Static.a

unix:!macx: LIBS += -L$$PWD/../CommProtocol/build/libxbee3/ -llibxbee3

INCLUDEPATH += $$PWD/../CommProtocol/libxbee3
DEPENDPATH += $$PWD/../CommProtocol/libxbee3

unix:!macx: LIBS += -L$$PWD/../CommProtocol/build/Encryption/cryptopp563/ -lcryptopp

INCLUDEPATH += $$PWD/../CommProtocol/Encryption/cryptopp563
DEPENDPATH += $$PWD/../CommProtocol/Encryption/cryptopp563

unix:!macx: PRE_TARGETDEPS += $$PWD/../CommProtocol/build/Encryption/cryptopp563/libcryptopp.a
