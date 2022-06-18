TEMPLATE = app
CONFIG += console c++11
QT+=xml network
QT-= gui
TEMPLATE = app
TARGET = ATSS
INCLUDEPATH += . -I..\..\..\Qt\Qt5.14.1\5.14.1\mingw73_64\include -I..\..\..\Qt\Qt5.14.1\5.14.1\mingw73_64\include\QtXml -I..\..\..\Qt\Qt5.14.1\5.14.1\mingw73_64\include\QtNetwork -I..\..\..\Qt\Qt5.14.1\5.14.1\mingw73_64\include\QtCore -I. -I..\..\..\Qt\Qt5.14.1\5.14.1\mingw73_64\mkspecs\win32-g++
DEFINES+= LINE_ONE WINDOWS_VER  UNICODE _UNICODE WIN32 MINGW_HAS_SECURE_API=1 LINE_ONE WINDOWS_VER QT_QML_DEBUG QT_XML_LIB QT_NETWORK_LIB QT_CORE_LIB QT_NEEDS_QMAIN
QMAKE_CXXFLAGS+=-mno-ms-bitfields
LIBS += C:\Qt\Qt5.14.1\5.14.1\mingw73_64\lib\libQt5Xml.a C:\Qt\Qt5.14.1\5.14.1\mingw73_64\lib\libQt5Network.a C:\Qt\Qt5.14.1\5.14.1\mingw73_64\lib\libQt5Core.a  -lmingw32 C:\Qt\Qt5.14.1\5.14.1\mingw73_64\lib\libqtmain.a -LC:\openssl\lib -LC:\Utils\my_sql\mysql-5.7.25-winx64\lib -LC:\Utils\postgresql\pgsql\lib -lshell32 C:\Qt\Qt5.14.1\Tools\mingw730_64\x86_64-w64-mingw32\lib\libws2_32.a

SOURCES += \
        src/ATSS_Communication.cpp \
        src/ATSS_DBData.cpp \
        src/ATSS_Main.cpp \
        src/ATSS_MessageProcessor.cpp

HEADERS += \
    inc/ATSS_Communication.h \
    inc/ATSS_DBData.h \
    inc/ATSS_Includes.h \
    inc/ATSS_MessageProcessor.h \
    inc/IDD.h \
    inc/IRS.h

DISTFILES += \
    Makefile
