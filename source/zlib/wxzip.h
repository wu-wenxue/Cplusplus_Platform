#ifndef WXZIP_H
#define WXZIP_H
#include "zip.h"
#include <string>

void compressFile(const std::string& zipfilename,const std::string& filename );

void compressFolder(const std::string& zipfilename,const std::string& path);


#endif // WXZIP_H
