QT += testlib network xml
QT -= gui

#Here we have included the "TESTING MODULE" into our project and eliminated the "GUI MODULE" because this subproject will
#be used to test our code. So that our project should be TEST DRIVEN ONE.

CONFIG += c++17

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

#qt: This adds the Qt module to the project, enabling it to use Qt libraries and features.
#
#console: This specifies that the application is a console application. On some platforms,
#this will ensure that a console window is created when the application is run.
#
#warn_on: This enables compiler warnings. It's generally a good practice to have this on to
#catch potential issues in the code.
#
#depend_includepath: This ensures that include paths are considered when determining dependencies.
#This can be useful for ensuring that changes in header files trigger recompilation of dependent source files.
#
#testcase: This indicates that the project is a test case. This is often used in the context of unit
#testing with Qt's test framework, Qt Test.

TARGET = tst_clienttests.cpp

#The above line specifies that our final compiled product name will be tst_clienttests.cpp.exe (windows in this case)

TEMPLATE = app

#This subproject is considered to build an application (final product will be an executable)

INCLUDEPATH += source \
    ../cm-lib/source

SOURCES +=  \
    source/controllers/mastercontrollertests.cpp \
    source/data/datetimedecoratortests.cpp \
    source/data/enumeratordecoratortests.cpp \
    source/data/intdecoratortests.cpp \
    source/data/stringdecoratortests.cpp \
    source/main.cpp \
    source/models/clienttests.cpp \
    source/testsuite.cpp

include(../qmake-target-platform.pri)
include(../qmake-destination-path.pri)

DESTDIR = $$PWD/../binaries/$$DESTINATION_PATH
OBJECTS_DIR = $$PWD/build/$$DESTINATION_PATH/.obj
MOC_DIR = $$PWD/build/$$DESTINATION_PATH/.moc
RCC_DIR = $$PWD/build/$$DESTINATION_PATH/.qrc
UI_DIR = $$PWD/build/$$DESTINATION_PATH/.ui

LIBS += -L$$PWD/../binaries/$$DESTINATION_PATH -lcm-lib

HEADERS += \
    source/controllers/mastercontrollertests.h \
    source/data/datetimedecoratortests.h \
    source/data/enumeratordecoratortests.h \
    source/data/intdecoratortests.h \
    source/data/stringdecoratortests.h \
    source/models/clienttests.h \
    source/testsuite.h
