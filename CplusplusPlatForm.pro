TARGET = C++platfrom


INCLUDEPATH += ./source \
               ./unit_test


HEADERS += \
    source/platform.h \
    source/config/config.h \
    source/thread/basethread.h \
    source/thread/thread_linux.h \
    unit_test/thread_test.hpp \
    source/logger/wxlogger.h \
    unit_test/test.hpp \
    source/time/time_manage.h

SOURCES += \
    source/platform.cpp \
    source/config/config.cpp \
    source/thread/basethread.cpp \
    source/thread/thread_linux.cpp \
    main.cpp \
    source/logger/wxlogger.cpp \
    source/time/time_manage.cpp


CONFIG += c++11
QMAKE_CXXFLAGS += -Wall -march=x86-64 -mmmx
