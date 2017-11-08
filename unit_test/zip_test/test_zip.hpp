#ifndef TEST_ZIP_HPP
#define TEST_ZIP_HPP
#include "zlib/zip.h"

void test_zip1()
{
    zipFile zf;
    zf = zipOpen("./data/test.zip",APPEND_STATUS_CREATE);

//    zipOpenNewFileInZip(
//                                       zipFile file,
//                                       const char* filename,
//                                       const zip_fileinfo* zipfi,
//                                       const void* extrafield_local,
//                                       uInt size_extrafield_local,
//                                       const void* extrafield_global,
//                                       uInt size_extrafield_global,
//                                       const char* comment,
//                                       int method,
//                                       int level
//                );

    zip_fileinfo zfi = {0};
    char* savefilename = "test.txt";
    zipOpenNewFileInZip(zf,savefilename,&zfi,NULL,0,NULL,0,NULL,Z_DEFLATED,Z_DEFAULT_COMPRESSION);

    FILE* fin;
    fin = fopen("./data/test.txt","rb");
    char *read_buffer = new char[1024*1024];
    int size_read = fread(read_buffer,1,1024*1024,fin);

    zipWriteInFileInZip(zf,read_buffer,size_read);

    if(NULL != read_buffer) { delete read_buffer; read_buffer = NULL;}
    fclose(fin);
    zipCloseFileInZip(zf);
    zipClose(zf,NULL);

}

void test_zip2()
{
    zipFile zf;
    zf = zipOpen("./data/test.zip",APPEND_STATUS_ADDINZIP);

    zip_fileinfo zfi = {0};
    char* savefilename = "testjson.json";
    zipOpenNewFileInZip(zf,savefilename,&zfi,NULL,0,NULL,0,NULL,Z_DEFLATED,Z_DEFAULT_COMPRESSION);

    FILE* fin;
    fin = fopen("./data/testjson.json","rb");
    char* buf = new char[1024*1024];
    int size = fread(buf,1,1024*1024,fin);

    zipWriteInFileInZip(zf,buf,size);

    if(NULL != buf) { delete buf; buf = NULL;}
    fclose(fin);
    zipCloseFileInZip(zf);
    zipClose(zf,NULL);
}

#include"zlib/wxzip.h"

void test_zip3()
{
    compressFolder("./data/test_folder.zip","./data");
}

void test_zip()
{
//    test_zip1();
//    test_zip2();
    test_zip3();
}

#endif // TEST_ZIP_HPP
