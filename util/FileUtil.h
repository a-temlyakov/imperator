#ifndef FILEUTIL_H
#define FILEUTIL_H

#include <stdlib.h>
#include <string>
#include <vector>
#include <dirent.h>
#include <sys/stat.h>

using namespace std;

class FileUtil{
    private:
        FileUtil() {} //This prevents creation of instances of this class

    public:
        static int getFileList(string, vector<string>&);
        static int getDirectoryList(string, vector<string>&);
};
#endif //FILEUTIL_H

