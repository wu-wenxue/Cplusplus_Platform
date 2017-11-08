#ifndef FILEOP_H
#define FILEOP_H
#include <io.h>
#include <fstream>
#include <string>
#include <vector>
#include <dirent.h>
#include <stdlib.h>
#include <direct.h>

using namespace std;

class WxFileOp
{

public:

    // 读取某给定路径下所有文件夹与文件名称，并带完整路径
    static void getAllFiles( string path, vector<string>& files);

    // 只读取某给定路径下的当前文件夹名
    static void getJustCurrentDir( string path, vector<string>& files);

    // 只读取某给定路径下的当前文件名
    static void getJustCurrentFile( string path, vector<string>& files);

    // 只读取某给定路径下的所有文件名(即包含当前目录及子目录的文件)
    static void getFilesAll( string path, vector<string>& files);

    static bool fileIsExist(const string& file_name);

    static bool renameFile(const string& src_name,const string& dst_name);

    static bool removeFile(const string& filename);

    static bool pathIsExist(const string& path);

    static bool createFolder(const string& path);

    static bool removeFolder(const string& path);

    static bool renameFolder(const string& old_folder_name, const string& new_folder_name);

    static string getFileNameFromPath(const string& path);

};
#endif // FILEOP_H
