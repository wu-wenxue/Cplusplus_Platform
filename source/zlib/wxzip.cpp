#include "wxzip.h"
#include "fileop/fileop.h"
#include "logger/wxlogger.h"

Wxlogger* logger = Wxlogger::getInstance();

void compressFile(const std::string& zipfilename,const std::string& filename )
{
    string savename = WxFileOp::getFileNameFromPath(filename);
    zipFile zf = zipOpen(zipfilename.c_str(),APPEND_STATUS_CREATE);
    if(NULL == zf)
    {
        WXLOG_FATAL(logger,"error opening " << zipfilename);
        return ;
    }
    zip_fileinfo zfi = {0};

    const int buffer_size = 1024*1024;
    char *read_buffer = new char[buffer_size];

    int res = zipOpenNewFileInZip(zf,savename.c_str(),&zfi,NULL,0,NULL,0,NULL,Z_DEFLATED,Z_DEFAULT_COMPRESSION);
    if(res != 0)
    {
        WXLOG_ERROR(logger,"error in opening " << savename << " in zipfile");
        return;
    }
    FILE* fin;
    fin = fopen(filename.c_str(),"rb");
    if(fin)
    {
        int read_size = 0;
        do{
            memset(read_buffer,0,buffer_size);
            read_size = fread(read_buffer,sizeof(char),buffer_size,fin);
            zipWriteInFileInZip(zf,read_buffer,read_size);
        }while(read_size);
    } else {
        WXLOG_ERROR(logger,"open file " << filename << " failed,this file will not be compress to " << zipfilename);
    }
    if(fin)
    {
        fclose(fin);
    }
    zipCloseFileInZip(zf);


    if(NULL != read_buffer) { delete read_buffer; read_buffer = NULL;}
    zipClose(zf,NULL);

}

void compressFolder(const std::string& zipfilename,const std::string& path)
{
    std::vector<string> files;
    WxFileOp::getJustCurrentFile(path,files);

    zipFile zf = zipOpen(zipfilename.c_str(),APPEND_STATUS_CREATE);
    if(NULL == zf)
    {
        WXLOG_FATAL(logger,"error opening " << zipfilename);
        return ;
    }
    zip_fileinfo zfi = {0};

    const int buffer_size = 1024*1024;
    char *read_buffer = new char[buffer_size];

    for(auto savename : files)
    {
        WXLOG_WARN(logger,savename);
        int res = zipOpenNewFileInZip(zf,savename.c_str(),&zfi,NULL,0,NULL,0,NULL,Z_DEFLATED,Z_DEFAULT_COMPRESSION);
        if(res != 0)
        {
            WXLOG_ERROR(logger,"error in opening " << savename << " in zipfile");
            continue;
        }
        FILE* fin;
        string fullname;
        if(path.at(path.size() - 1) == '\\' || path.at(path.size()-1) == '/')
        {
            fullname = path + savename;
        }
        else
        {
            fullname = path + '/' + savename;
        }
        fin = fopen(fullname.c_str(),"rb");
        if(fin)
        {
            int read_size = 0;
            do{
                memset(read_buffer,0,buffer_size);
                read_size = fread(read_buffer,sizeof(char),buffer_size,fin);
                zipWriteInFileInZip(zf,read_buffer,read_size);
            }while(read_size);
        } else {
            WXLOG_ERROR(logger,"open file " << fullname << " failed,this file will not be compress to " << zipfilename);
        }
        if(fin)
        {
            fclose(fin);
        }
        zipCloseFileInZip(zf);

    }
    if(NULL != read_buffer) { delete read_buffer; read_buffer = NULL;}
    zipClose(zf,NULL);
}
