TEMPLATE = app
CONFIG += console c++14 thread debug
CONFIG -= app_bundle
CONFIG -= qt

HEADERS += \
    Model/Course.h \
    Model/CrsTable.hpp \
    Model/Day.h \
    Model/Interpreter.hpp \
    Model/LecTime.h \
    Stage/Chain.h \
    Stage/Plan.hpp \
    Stage/Schedule.h \
    Stage/Time.hpp \
    Base.h \
    Model/RBTree.h

SOURCES += \
    Model/Course.cpp \
    Model/Day.cpp \
    Model/LecTime.cpp \
    Test/io_test.cpp \
    Base.cpp \
    main.cpp \
    Test/stage_test.cpp

DISTFILES += \
    README.md

