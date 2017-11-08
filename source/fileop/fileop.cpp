#include "fileop.h"
#include <fstream>
#include <windows.h>

// 读取某给定路径下所有文件夹与文件名称，并带完整路径
void WxFileOp::getAllFiles( string path, vector<string>& files)
{
    //文件句柄
    long  hFile  =  0;
    //文件信息
    struct _finddata_t fileinfo;
    string p;
    if((hFile = _findfirst(p.assign(path).append("\\*").c_str(),&fileinfo)) != -1)
    {
        do
        {
            if((fileinfo.attrib & _A_SUBDIR))
            {
                if(strcmp(fileinfo.name,".") != 0 && strcmp(fileinfo.name,"..") != 0)
                {
                    files.push_back(p.assign(path).append("\\").append(fileinfo.name) );
                    getFilesAll( p.assign(path).append("\\").append(fileinfo.name), files );
                }
            }
            else
            {
                files.push_back(p.assign(path).append("\\").append(fileinfo.name) );
            }
        }while(_findnext(hFile, &fileinfo) == 0);
        _findclose(hFile);
    }
}

// 只读取某给定路径下的当前文件夹名
void WxFileOp::getJustCurrentDir( string path, vector<string>& files)
{
    //文件句柄
    long  hFile  =  0;
    //文件信息
    struct _finddata_t fileinfo;
    string p;
    if((hFile = _findfirst(p.assign(path).append("\\*").c_str(),&fileinfo)) != -1)
    {
        do
        {
            if((fileinfo.attrib & _A_SUBDIR))
            {
                if(strcmp(fileinfo.name,".") != 0 && strcmp(fileinfo.name,"..") != 0)
                {
                    files.push_back(fileinfo.name);
                    //files.push_back(p.assign(path).append("\\").append(fileinfo.name) );
                }

            }
        }while(_findnext(hFile, &fileinfo) == 0);
        _findclose(hFile);
    }
}

// 只读取某给定路径下的当前文件名
void WxFileOp::getJustCurrentFile( string path, vector<string>& files)
{
    //文件句柄
    long  hFile  =  0;
    //文件信息
    struct _finddata_t fileinfo;
    string p;
    if((hFile = _findfirst(p.assign(path).append("\\*").c_str(),&fileinfo)) != -1)
    {
        do
        {
            if((fileinfo.attrib & _A_SUBDIR))
            {
                ;
            }
            else
            {
                files.push_back(fileinfo.name);
                //files.push_back(p.assign(path).append("\\").append(fileinfo.name) );
            }
        }while(_findnext(hFile, &fileinfo) == 0);
        _findclose(hFile);
    }
}


// 只读取某给定路径下的所有文件名(即包含当前目录及子目录的文件) 带路径
void WxFileOp::getFilesAll( string path, vector<string>& files)
{
    //文件句柄
    long  hFile  =  0;
    //文件信息
    struct _finddata_t fileinfo;
    string p;
    if((hFile = _findfirst(p.assign(path).append("\\*").c_str(),&fileinfo)) != -1)
    {
        do
        {
            if((fileinfo.attrib & _A_SUBDIR))
            {
                if(strcmp(fileinfo.name,".") != 0 && strcmp(fileinfo.name,"..") != 0)
                {
                    //files.push_back(p.assign(path).append("\\").append(fileinfo.name) );
                    getFilesAll( p.assign(path).append("\\").append(fileinfo.name), files );
                }
            }
            else
            {
                files.push_back(p.assign(path).append("\\").append(fileinfo.name) );
            }
        }while(_findnext(hFile, &fileinfo) == 0);
        _findclose(hFile);
    }
}

bool WxFileOp::fileIsExist(const string& file_name)
{
    fstream _file;
    _file.open(file_name,ios::in);
    if(!_file)
    {
        return false;
    }
    return true;
}

bool WxFileOp::renameFile(const string& src_name,const string& dst_name)
{
    rename(src_name.data(),dst_name.data());

    return fileIsExist(dst_name);
}

bool WxFileOp::removeFile(const string& file_name)
{
    remove(file_name.data());
    return !fileIsExist(file_name);
}

bool WxFileOp::pathIsExist(const string& path)
{
    DIR* dir;
    if((dir = opendir(path.data())) == NULL)
    {
        return false;
    }
    return true;
}

bool WxFileOp::createFolder(const string& path)
{
    mkdir(path.data());
    return pathIsExist(path);
}

bool WxFileOp::removeFolder(const string& path)
{
    rmdir(path.data());
    return !pathIsExist(path);
}

bool WxFileOp::renameFolder(const string& old_folder_name,const string& new_folder_name)
{
    rename(old_folder_name.data(),new_folder_name.data());
    return pathIsExist(new_folder_name);
}

string WxFileOp::getFileNameFromPath(const string& path)
{
    string filename;
    const char* tmpptr = path.c_str();
    const char* lastslash = NULL;
    for(;*tmpptr;tmpptr++)
    {
        if(*tmpptr == '\\' || *tmpptr == '/')
        {
            lastslash = tmpptr;
        }
    }
    if(NULL != lastslash)
    {
        filename += (lastslash + 1);
    }
    return filename;
}


