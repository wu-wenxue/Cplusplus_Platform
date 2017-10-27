TARGET = C++platfrom


INCLUDEPATH += ./source \
               ./unit_test


HEADERS += \
    source/platform.h \
    source/config/config.h \
    source/thread/basethread.h \
    source/thread/thread_linux.h \
    source/logger/wxlogger.h \
    unit_test/test.hpp \
    source/time/time_manage.h \
    source/ping/ping.h \
    source/common/common.h \
    source/thread/thread_windows.h \
    source/IPC/socket/tcp_client.h \
    source/IPC/socket/tcp_server.h

SOURCES += \
    source/platform.cpp \
    source/config/config.cpp \
    source/thread/basethread.cpp \
    source/thread/thread_linux.cpp \
    main.cpp \
    source/logger/wxlogger.cpp \
    source/time/time_manage.cpp \
    source/ping/ping.cpp \
    source/common/common.cpp \
    source/thread/thread_windows.cpp \
    source/IPC/socket/tcp_client.cpp \
    source/IPC/socket/tcp_server.cpp


CONFIG += c++11


LIBS += -lwsock32
LIBS += -lpthread libwsock32 libws2_32

QMAKE_CXXFLAGS += -Wall -march=x86-64 -mmmx
