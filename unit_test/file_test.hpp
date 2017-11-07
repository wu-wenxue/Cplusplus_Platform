#ifndef FILE_TEST_HPP
#define FILE_TEST_HPP

#include "fileop/fileop.h"
#include <windows.h>
#include "common/common.h"

void test_file1()
{
    rename("./data/test.zip","./data/test.zip2");
    remove("./data/test.zip2");

    string path = "./data2";
    DIR* dir;

    if((dir = opendir(path.data())) == NULL)
    {
        cout << path << " is not exist" << endl;
        mkdir(path.data());
    }
    else
    {
//        cout << path << " is exist" << endl;
//        rmdir(path.data());
    }
    rename("./data2","./data3");

//    struct _finddata_t fileinfo;


//    ::MoveFile((LPCWSTR)"./data2",(LPCWSTR)"./data4");

//    LPCWSTR lpszFromPath = (LPCWSTR)("E:/Project/C++/CplusplusPlatForm-Debug/data2/");
//    LPCWSTR lpszToPath = (LPCWSTR)("E:/Project/C++/CplusplusPlatForm-Debug/data3/");

//    int nLengthFrm = wcslen(lpszFromPath);
//    wchar_t* NewPathFrm = new wchar_t[nLengthFrm + 2];
//    wcscpy(NewPathFrm,lpszFromPath);
//    NewPathFrm[nLengthFrm] = '\0';
//    NewPathFrm[nLengthFrm + 1] = '\0';

//    SHFILEOPSTRUCT FileOp;
//    ZeroMemory((void*)&FileOp,sizeof(SHFILEOPSTRUCT));

//    FileOp.fFlags = FOF_NOCONFIRMATION;
//    FileOp.hNameMappings = NULL;
//    FileOp.hwnd = NULL;
//    FileOp.lpszProgressTitle = NULL;
//    FileOp.pFrom = NewPathFrm;
//    FileOp.pTo = lpszToPath;
//    FileOp.wFunc = FO_RENAME;

//    std::cout << SHFileOperation(&FileOp) << std::endl;

}

void test_file2()
{
    vector<string> fileList;
    WxFileOp::getAllFiles("./data",fileList);
//    string file;
    for (auto file : fileList)
    {
        cout << file <<endl;
    }

    cout << endl;

    vector<string> fileList2;
    WxFileOp::getFilesAll("./debug",fileList2);
    for(auto file : fileList2)
    {
        cout << file << endl;
    }

}


void test_file()
{

//    test_file2();

    string str = "name";
    int i = 0;
    string temp_name = str + "." + int2string(i);
    cout << "tmep_name : " << temp_name << endl;
}

#endif // FILE_TEST_HPP
