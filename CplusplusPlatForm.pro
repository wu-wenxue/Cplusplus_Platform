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
    source/IPC/socket/tcp_server.h \
    unit_test/http_test.hpp \
    source/http/http_client.h \
    source/IPC/socket/tcp_linux.h \
    source/time/sntp.hpp \
    source/IPC/socket/epoll_server.h

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
    source/IPC/socket/tcp_server.cpp \
    source/http/http_client.cpp \
    source/IPC/socket/tcp_linux.cpp \
    source/IPC/socket/epoll_server.cpp

win32{

INCLUDEPATH += ./deploy/windows/curllib/include

LIBS += -lwsock32
LIBS += -lpthread libwsock32 libws2_32
LIBS += E:\Project\C++\Cplusplus_Platform\deploy\windows\curllib\lib\libcurl.dll

}

unix{

INCLUDEPATH += /usr/local/include   \
               /usr/include

LIBS += -L/usr/local/lib \
        -L/usr/lib   \
        -lcrypto -lssl -Wl,-rpath,/usr/local/lib \
        -lcurl
}


CONFIG += c++11



LIBS += -lpthread
#LIBS += -L./deploy/curllib/lib/ -lcurldll


QMAKE_CXXFLAGS += -Wall -march=x86-64 -mmmx -lws2_32 -lwinmm -lwldap32
