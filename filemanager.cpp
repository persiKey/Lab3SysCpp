#include "filemanager.h"
#include <fstream>
#include <exception>



FileManager::FileManager()
{

}

vector<Role> FileManager::Read(std::string fileName)
{
    std::ifstream file(fileName);
    vector<Role> result;

    if(!file)
    {
        throw std::exception();
    }

    string inputStr;
    Role inputRole;
    while(std::getline(file,inputStr))
    {
        inputRole.deserialize(inputStr);
        result.push_back(inputRole);
    }

    return result;
}

void FileManager::Write(std::string fileName, const vector<Role> &roles)
{
    std::ofstream file(fileName, std::ios_base::out);

    for(const auto& r : roles)
    {
        file << r.serialize() << '\n';
    }
}
