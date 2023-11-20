#include "radio.hpp"
#include <algorithm>
#include <sstream>
#include <fstream>
#include <string>

Role::Role(/* args */)
{
    //std::cout << "ctor\n";
}

Role::~Role()
{
     //std::cout << "dtor\n";
}

std::ostream &operator<<(std::ostream &out, const Role &r)
{
    out << "Code: " << r.code << '\n';
    out << "Name: " << r.name << '\n';
    out << "Wage: " << r.wage << '\n';
    out << "Duties:\n";
    for (const auto &d : r.duties)
        out << '\t' << d << '\n';
    out << "Requirements:\n";
    for (const auto &rq : r.requirements)
        out << '\t' << rq << '\n';
    
    return out;
}



void Role::setCode(int newCode)
{
    code = newCode;
}

int Role::getCode() const
{
    return code;
}

void Role::setName(const string& newName)
{
    name = newName;
}

string Role::getName() const
{
    return name;
}

void Role::setWage(float newWage)
{
    wage = newWage;
}

float Role::getWage() const
{
    return wage;
}

bool Role::addDuty(const string &duty)
{
    if(duty.empty())
        return false;

    if(hasDuty(duty))
        return false;
    
    duties.push_back(duty);
    return true;
}

bool Role::removeDuty(const string &duty)
{
    auto findRes = std::find(duties.begin(), duties.end(), duty);
    if( findRes == duties.end() )
        return false;
    
    duties.erase(findRes);
    return true;
}

bool Role::hasDuty(const string &duty) const
{
    auto findRes = std::find(duties.begin(), duties.end(), duty);
    return findRes != duties.end();
}

vector<string> Role::getDuties() const
{
    return duties;
}

bool Role::addRequirement(const string &requirement)
{
    if(requirement.empty())
        return false;

    if(hasRequirement(requirement))
        return false;
    
    requirements.push_back(requirement);
    return true;
}

bool Role::removeRequirement(const string &requirement)
{
    auto findRes = std::find(requirements.begin(), requirements.end(), requirement);
    if( findRes == requirements.end() )
        return false;
    
    requirements.erase(findRes);
    return true;
}

bool Role::hasRequirement(const string &requirement) const
{
    auto findRes = std::find(requirements.begin(), requirements.end(), requirement);
    return findRes != requirements.end();
}

vector<string> Role::getRequirements() const
{
    return requirements;
}

std::string Role::serialize() const
{
    std::ostringstream oss;
    oss << code << ',' << name << ',' << wage << ',';

    for (const auto& duty : duties)
    {
        oss << duty << ';';
    }

    oss << ',';

    for (const auto& requirement : requirements)
    {
        oss << requirement << ';';
    }

    return oss.str();
}

void Role::deserialize(const std::string &indata)
{
    std::istringstream iss(indata);
    char delimiter = ',';

    string data;
    // Read code, name, and wage
    std::getline(iss, data, delimiter);
    code = std::stoi(data);

    std::getline(iss, name, delimiter);
    std::getline(iss, data, delimiter);
    wage = std::stof(data);

    // Read duties
    std::getline(iss, data, delimiter);
    duties.clear();
    std::istringstream dutiesStream(data);
    while (std::getline(dutiesStream, data, ';'))
    {
        duties.push_back(data);
    }

    // Read requirements
    std::getline(iss, data, delimiter);
    requirements.clear();
    std::istringstream requirementsStream(data);
    while (std::getline(requirementsStream, data, ';'))
    {
        requirements.push_back(data);
    }
}
