#include "wxlogger.h"
#include <fstream>"
#include <stdio.h>
#include <iostream>
#include "fileop/fileop.h"
#include "common/common.h"
#include "zlib.h"

#if defined(__unix__) || defined(unix)
#include <sys/time.h>
#endif

#ifdef _WIN32
#include <windows.h>
#endif

Wxlogger* Wxlogger::_instance = NULL;

Wxlogger::Wxlogger()
{
    m_Name = string("log.log");
    m_level = INFO;
    m_logFileSize = 30*1024;
    m_logSaveCount = 2;
}

void Wxlogger::SetLogName(string path,string filename)
{
//    m_Path = path;
    if(!WxFileOp::pathIsExist(path))
    {
        while(!WxFileOp::createFolder(path)) break;
    }

    if(filename.empty())
    {
        std::cout << "ERROR : log filename is null !!!!" << std::endl;
    }
    m_Name = path + filename;
}

void Wxlogger::SetLogLevel(loglevel level)
{
    m_level = level;
}

void Wxlogger::SetLogFileSize(const int size)
{
    m_logFileSize = size;
}

void Wxlogger::SetLogSaveCount(const int n)
{
    m_logSaveCount = n;
}

Wxlogger* Wxlogger::getInstance()
{
    if(NULL == _instance)
    {
        _instance = new Wxlogger();
    }
    return _instance;
}

void Wxlogger::WxLog(loglevel level, ostringstream &oss)
{
    mut.lock();
    if(getLogFileSize() > m_logFileSize)
    {
        BackLogFile();
    }

    ofstream outfile;
    outfile.open(m_Name.c_str(),ios::out|ios::app|ios::ate);

    switch(level)
    {
    case INFO:
    {
        if(level < m_level) break;

        if(outfile.is_open())
        {
            outfile << "[INFO ] " << this->GetCurrentTime_byms().data()  <<" : "<< oss.str() << std::endl;
        }
    }
        break;
    case WARN:
    {
        if(level < m_level) break;
        if(outfile.is_open())
        {
            outfile << "[WARN ] " << this->GetCurrentTime_byms().data()  <<" : "<< oss.str() << std::endl;
        }
    }
        break;
    case ERR:
    {
        if(level < m_level) break;
        if(outfile.is_open())
        {
            outfile << "[ERROR] " << this->GetCurrentTime_byms().data()  <<" : "<< oss.str() << std::endl;
        }
    }
        break;
    case FATAL:
    {
        if(level < m_level) break;
        if(outfile.is_open())
        {
            outfile << "[FATAL] " << this->GetCurrentTime_byms().data()  <<" : "<< oss.str() << std::endl;
        }
    }
        break;
    default:
        break;
    }
    outfile.close();
    mut.unlock();

}

string Wxlogger::GetCurrentTime_()
{
    struct tm* ct;   //tm结构指针
    const time_t t = time(NULL);
    ct = localtime(&t);
    char temp[50] = {0};
    sprintf(temp,"%d-%d-%d %d:%d:%d" ,ct->tm_year + 1900,ct->tm_mon + 1,ct->tm_mday,ct->tm_hour,ct->tm_min,ct->tm_sec);

    return string(temp);
}

string Wxlogger::GetCurrentTime_byms()
{
    int ms = 0;

#if defined(__unix__) || defined(unix)
    struct timeval tv;
    gettimeofday(&tv,NULL);
    ms = tv.tv_usec/1000;
#endif

#ifdef _WIN32
    SYSTEMTIME wtm;
    GetLocalTime(&wtm);

    ms = wtm.wMilliseconds;
#endif

    struct tm* stm;
    const time_t t = time(NULL);
    stm = localtime(&t);

    char time[50] = {0};
    sprintf(time,"%04d-%02d-%02d %02d:%02d:%02d.%03d",stm->tm_year+1900,stm->tm_mon+1,stm->tm_mday,stm->tm_hour,stm->tm_min,stm->tm_sec,ms);
    return string(time);
}

string Wxlogger::GetCurrentTime_byus()
{
    int us = 0;
#if defined(__unix__) || defined(unix)
    struct timeval tv;
    gettimeofday(&tv,NULL);
    us = tv.tv_usec;
#endif

#ifdef _WIN32
    SYSTEMTIME wtm;
    GetLocalTime(&wtm);

    us = wtm.wMilliseconds*1000;
#endif

    struct tm* stm;
    const time_t t = time(NULL);
    stm = localtime(&t);

    char time[50] = {0};
    sprintf(time,"%04d-%02d-%02d %02d:%02d:%02d.%06d",stm->tm_year+1900,stm->tm_mon+1,stm->tm_mday,stm->tm_hour,stm->tm_min,stm->tm_sec,us);
    return string(time);
}

int Wxlogger::getLogFileSize()
{
    FILE* file = fopen(m_Name.data(),"rb");
    if(file)
    {
        int size = filelength(fileno(file));
        fclose(file);
        return size;
    }
    return -1;

#if defined(__unix__) || defined(unix)
    struct _stat info;
    if(_stat(m_Name,&info) == 0)
    {
        int size = info.st.size;
        return size;
    }
    return -1;
#endif

#ifdef _WIN32
    HANDLE handle = CreateFileA(m_Name.data(),FILE_READ_EA,FILE_SHARE_READ,0,OPEN_EXISTING,0,0);
    if(handle != INVALID_HANDLE_VALUE)
    {
        int size = GetFileSize(handle,NULL);
        CloseHandle(handle);
        return size;
    }
    return -1;
#endif
}

void Wxlogger::BackLogFile()
{
    for(int i = m_logSaveCount-1; i > 0 ; )
    {
        i--;
        string temp_name =  m_Name + "." + int2string(i);
        if(WxFileOp::fileIsExist(temp_name))
        {
            string new_name = m_Name + "." + int2string(i+1);
            while(!WxFileOp::renameFile(temp_name,new_name)) break;
        }
    }

    gzFile file;
    string new_name = m_Name + "." + int2string(0);
    file = gzopen(new_name.data(),"wb");

    FILE* file_src = fopen(m_Name.data(),"r");

    const int buffer_size = m_logFileSize + 1024*1024;
    char* buffer_src = new char[buffer_size];
    memset(buffer_src,0, buffer_size);

    unsigned long  len_src = fread(buffer_src,sizeof(char),buffer_size - 1,file_src);
    gzputs(file,buffer_src);
    gzseek(file,1L,SEEK_CUR);
    gzclose(file);
    fclose(file_src);
    if(NULL != buffer_src) {delete buffer_src; buffer_src = NULL;}


    while(!WxFileOp::removeFile(m_Name)) break;
}
