TEMPLATE = app
CONFIG += console c++14 thread release
CONFIG -= app_bundle
CONFIG -= qt

HEADERS += \
    Model/Course.h \
    Model/CrsTable.hpp \
    Model/Day.h \
    Model/LecTime.h \
    Base.h \
    Model/Interpreter.hpp

SOURCES += \
    Model/Course.cpp \
    Model/Day.cpp \
    Model/LecTime.cpp \
    Base.cpp \
    main.cpp
