#pragma once

#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;


class Role
{
private:
    int code = -1;
    string name;
    float wage;
    vector<string> duties;
    vector<string> requirements;

public:
    Role();
    ~Role();

    friend class RoleHelper;
    friend std::ostream& operator<<(std::ostream& out,const Role& r);

    void setCode(int newCode);
    int getCode() const;

    void setName(const string& newName);
    string getName() const;

    void setWage(float newWage);
    float getWage() const;

    bool addDuty(const string& duty);
    bool removeDuty(const string& duty);
    bool hasDuty(const string& duty) const;
    vector<string> getDuties() const;
    
    bool addRequirement(const string& requirement);
    bool removeRequirement(const string& requirement);
    bool hasRequirement(const string& requirement) const;
    vector<string> getRequirements() const;

    std::string serialize() const;
    void deserialize(const std::string& data);
};
