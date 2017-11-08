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
    source/IPC/socket/epoll_server.h \
    source/json/config.h \
    source/json/json.h \
    source/json/reader.h \
    source/json/value.h \
    source/json/writer.h \
    source/json/autolink.h \
    source/json/features.h \
    source/json/forwards.h \
    source/json/json_batchallocator.h \
    source/threadpool/BusyThreadContainer.h \
    source/threadpool/IdleThreadContainer.h \
    source/threadpool/MyTask.h \
    source/threadpool/MyThread.h \
    source/threadpool/MyThreadPool.h \
    source/threadpool/Task.h \
    source/threadpool/TaskContainer.h \
    unit_test/threadpool_test.hpp \
    unit_test/json_test.hpp \
    unit_test/test_zlib.hpp \
    unit_test/test_zlib2.hpp \
    source/fileop/fileop.h \
    unit_test/file_test.hpp \
    source/zlib/crypt.h \
    source/zlib/ioapi.h \
    source/zlib/iowin32.h \
    source/zlib/mztools.h \
    source/zlib/unzip.h \
    source/zlib/zip.h \
    unit_test/zip_test/iowin32.h \
    unit_test/zip_test/test_zip.hpp \
    source/zlib/wxzip.h

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
    source/IPC/socket/epoll_server.cpp \
    source/json/json_reader.cpp \
    source/json/json_value.cpp \
    source/json/json_writer.cpp \
    source/json/json_internalarray.inl \
    source/json/json_internalmap.inl \
    source/json/json_valueiterator.inl \
    source/threadpool/BusyThreadContainer.cpp \
    source/threadpool/IdleThreadContainer.cpp \
    source/threadpool/MyTask.cpp \
    source/threadpool/MyThread.cpp \
    source/threadpool/MyThreadPool.cpp \
    source/threadpool/Task.cpp \
    source/threadpool/TaskContainer.cpp \
    source/fileop/fileop.cpp \
    source/zlib/ioapi.c \
    source/zlib/mztools.c \
    source/zlib/unzip.c \
    source/zlib/zip.c \
    unit_test/zip_test/iowin32.c \
    unit_test/zip_test/miniunz.c \
    unit_test/zip_test/minizip.c \
    source/zlib/wxzip.cpp

win32{

INCLUDEPATH += ./deploy/windows/curllib/include  \
               ./deploy/windows/zlib/include

LIBS += -lwsock32
LIBS += libwsock32 libws2_32
LIBS += E:\Project\C++\Cplusplus_Platform\deploy\windows\curllib\lib\libcurl.dll
LIBS += E:\Project\C++\Cplusplus_Platform\deploy\windows\zlib\Debug\lib\libzlib.dll

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

DISTFILES += \
    source/json/sconscript \
    conf/config.ini \
    conf/config.json \
    data/testjson.json \
    data/testjsonarray.json \
    data/example.json
