#include "FileUtil.h"

int FileUtil::getFileList(string path, vector<string> &file_list)
{
    DIR* dirp = opendir(path.c_str());
    struct dirent *file;

    if(dirp == NULL)
        return EXIT_FAILURE;

    while((file = readdir(dirp)) != NULL)
    {
        string name(file->d_name);

        struct stat st;
        if(stat((path + "/" + name).c_str(), &st))
            continue;

        if(S_ISREG(st.st_mode))
        {
            file_list.push_back(string(file->d_name));
        }
    } 

    closedir(dirp);
    return EXIT_SUCCESS;
}

int FileUtil::getDirectoryList(string path, vector<string> &dir_list)
{
    DIR* dirp = opendir(path.c_str());
    struct dirent *file;

    if(dirp == NULL)
        return EXIT_FAILURE;

    while((file = readdir(dirp)) != NULL)
    {
        string name(file->d_name);

        if(!name.compare(".") || !name.compare(".."))
            continue;

        struct stat st;
        if(stat((path + "/" + name).c_str(), &st))
            continue;

        if(S_ISDIR(st.st_mode))
        {
            dir_list.push_back(string(file->d_name));
        }
    }

    closedir(dirp);
    return EXIT_SUCCESS;
}
