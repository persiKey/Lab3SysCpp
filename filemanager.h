#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <vector>
#include <radio.hpp>

class FileManager
{
public:
    FileManager();
    vector<Role> Read(string fileName);
    void Write(string fileName, const vector<Role>& roles);
};

#endif // FILEMANAGER_H
