#ifndef TEST_ZLIB_HPP
#define TEST_ZLIB_HPP
#include "zlib.h"
#include <string>
#include <logger/wxlogger.h>

using namespace std;

const char* pFileCom = "./data/test.txt";
const char* pFileSave = "./data/test.zip";

#define MAX_LEN 1024*100

/*
void test_zlib()
{
    FILE* fp1 = NULL;
    fp1 = fopen(pFileCom,"rb");
    assert(fp1);

    unsigned char* pBufferRes = new unsigned char[MAX_LEN];
    unsigned char* pBufferDes = new unsigned char[MAX_LEN];

    memset(pBufferRes,0,MAX_LEN);
    memset(pBufferDes,0,MAX_LEN);

    fread(pBufferRes,sizeof(unsigned char),MAX_LEN-1,fp1);
    uLongf lSize = strlen((const char*)pBufferRes);

    // dynamic load DLL
    HINSTANCE hIns = ::LoadLibrary(_T("."));
    uLongf desLen;
    if(hIns)
    {
        typedef int (*fun)(Bytef*,uLongf*,const Bytef*,uLongf);
        fun f = NULL;
        f = (fun)GetProcAddress(hIns,"compress");
    }

}
*/
const unsigned int MaxBufferSize = 1024*100;
void test_zlib2()
{
    FILE* file_src;
    FILE* file_compress;
    FILE* file_uncompress;
    unsigned long len_src;
    unsigned long len_compress;
    unsigned long len_uncompress = MaxBufferSize;
    unsigned char* buffer_src = new unsigned char[MaxBufferSize];
    memset(buffer_src,0,MaxBufferSize);
    unsigned char* buffer_compress = new unsigned char[MaxBufferSize];
    memset(buffer_compress,0,MaxBufferSize);
    unsigned char* buffer_uncompress = new unsigned char[MaxBufferSize];
    memset(buffer_uncompress,0,MaxBufferSize);

    file_src = fopen("./data/test.txt","r");
    file_compress = fopen("./data/compress.zip","w");
    file_uncompress = fopen("./data/uncompress.txt","w");

    //compress
    len_src = fread(buffer_src,sizeof(char),MaxBufferSize - 1,file_src);
    compress(buffer_compress,&len_compress,buffer_src,len_src);
    fwrite(buffer_compress,sizeof(char),len_compress,file_compress);

    // uncompress
    uncompress(buffer_uncompress,&len_uncompress,buffer_compress,len_compress);
    fwrite(buffer_uncompress,sizeof(char),len_uncompress,file_uncompress);

    fclose(file_src);
    fclose(file_compress);
    fclose(file_uncompress);

    if(NULL != buffer_src) {delete buffer_src;buffer_src = NULL;}
    if(NULL != buffer_compress) {delete buffer_compress; buffer_compress = NULL;}
    if(NULL != buffer_uncompress) {delete buffer_uncompress; buffer_uncompress = NULL;}
}

void test_zlib3()
{
    Wxlogger* logger = Wxlogger::getInstance();
    string str;
    str.append("中华人民共和国,china mobile,123456 中华人民共和国 中华人民共和国 中华人民共和国");

    unsigned long len_compress;
    unsigned long len_uncompress;
    unsigned char* buffer_compress = new unsigned char[MaxBufferSize];
    memset(buffer_compress,0,MaxBufferSize);
    unsigned char* buffer_uncompress = new unsigned char[MaxBufferSize];
    memset(buffer_uncompress,0,MaxBufferSize);
    compress(buffer_compress,&len_compress,(unsigned char*)const_cast<char*>(str.data()),str.length());
    uncompress(buffer_uncompress,&len_uncompress,buffer_compress,len_compress);

    WXLOG_INFO(logger,"src : " << str << ",length : " << str.size());
    WXLOG_INFO(logger,"compress : " << buffer_compress << ",length : " << len_compress);
    WXLOG_INFO(logger,"uncompress : " << buffer_uncompress << ", length : " << len_uncompress);

    if(NULL != buffer_compress) {delete buffer_compress; buffer_compress = NULL;}
    if(NULL != buffer_uncompress) {delete buffer_uncompress; buffer_uncompress = NULL;}
}

void test_zlib4()
{
    gzFile file;
    char* filename = "./data/test.zip";
    FILE* file_src;
    file_src = fopen("./data/test.txt","r");
    unsigned long len_src;
    char* buffer_src = new char[MaxBufferSize];
    len_src = fread(buffer_src,sizeof(char),MaxBufferSize - 1,file_src);

    file = gzopen(filename,"wb");

    gzputs(file,buffer_src);

/*
    gzputc(file,'h');
    if(gzputs(file,"ello") != 4)
    {

    }

    if(gzprintf(file,",%s!","hello") != 8)
    {

    }
*/

    gzseek(file, 1L,SEEK_CUR);
    gzclose(file);


}

#include <dirent.h>
#include <stdlib.h>
#include <windows.h>
#include <direct.h>
#include <io.h>

void test_zlib()
{
//    test_zlib2();
    test_zlib3();
    test_zlib4();



//    GetDirAllFile()
}

#endif // TEST_ZLIB_HPP
