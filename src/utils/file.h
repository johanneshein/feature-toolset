#ifndef SDK_FEATURE_TOOLSET_UTILS_FILE_H_
#define SDK_FEATURE_TOOLSET_UTILS_FILE_H_

#include <sys/stat.h>

bool fileExists(std::string fileName)
{
    struct stat fileStat;

    if (stat(fileName.c_str(), &fileStat) != -1)
    {
        return true;
    }

    return false;
}

#endif // SDK_FEATURE_TOOLSET_UTILS_FILE_H_
