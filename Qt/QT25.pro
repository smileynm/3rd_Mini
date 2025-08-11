QT       += core gui sql network httpserver


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += model view controller lang

SOURCES += \
    controller/admincontroller.cpp \
    controller/logincontroller.cpp \
    controller/normalcontroller.cpp \
    model/database.cpp \
    model/member.cpp \
    model/membermanager.cpp \
    model/orderedproduct.cpp \
    model/product.cpp \
    model/productmanager.cpp \
    model/raspiconnector.cpp \
    model/qrproduct.cpp \
    view/admin.cpp \
    model/main.cpp \
    view/adminchatform.cpp \
    view/admininfoform.cpp \
    view/adminorderlistform.cpp \
    view/adminproductform.cpp \
    view/login.cpp \
    view/normal.cpp \
    view/normalchatform.cpp \
    view/normalorderform.cpp \
    view/normalorderverifyform.cpp

HEADERS += \
    controller/admincontroller.h \
    controller/logincontroller.h \
    controller/normalcontroller.h \
    model/database.h \
    model/member.h \
    model/membermanager.h \
    model/orderedproduct.h \
    model/product.h \
    model/productmanager.h \
    model/raspiconnector.h \
    model/qrproduct.h \
    view/admin.h \
    view/adminchatform.h \
    view/admininfoform.h \
    view/adminorderlistform.h \
    view/adminproductform.h \
    view/login.h \
    view/normal.h \
    view/normalchatform.h \
    view/normalorderform.h \
    view/normalorderverifyform.h

FORMS += \
    view/admin.ui \
    view/adminchatform.ui \
    view/admininfoform.ui \
    view/adminorderlistform.ui \
    view/adminproductform.ui \
    view/login.ui \
    view/normal.ui \
    view/normalchatform.ui \
    view/normalorderform.ui \
    view/normalorderverifyform.ui

TRANSLATIONS += \
    lang/QT25_ko_KR.ts

CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
INCLUDEPATH += "C:/Program Files/MySQL/MySQL Server 8.0/include"
LIBS += -L"C:/Program Files/MySQL/MySQL Server 8.0/lib" -lmysqlclient
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
