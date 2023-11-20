#include <iostream>
#include <stdexcept>
#include <string>
#include "Database.hpp"
#include <algorithm>

using namespace std;

const char* DB_FILE_NAME = "db.txt";
namespace Records
{

    Database::Database()
    {
        mRoles = fileManager.Read(DB_FILE_NAME);
    }
    Database::~Database()
    {
        Save();
    }

    auto Database::GetRoleByCode(int roleCode) -> decltype (vector<Role>().begin())
    {
        return std::find_if(mRoles.begin(),mRoles.end(),
                            [&roleCode](const Role& role)
                            { return roleCode == role.getCode(); });
    }

    Database &Database::GetInstance()
    {
        static Database SigletoneDB;
        return SigletoneDB;
    }
    void Database::addRole(int roleCode, std::string roleName, float roleWage)
    {
        
        if(GetRoleByCode(roleCode) != (mRoles.end()))
        {
            throw std::runtime_error("There is a role with the same code");
        }

        if(roleName.size() < 3)
            throw std::runtime_error("Name is too small");

        if(roleWage < 0)
            throw std::runtime_error("Wage cannot be negative");


        Role theRole;
        theRole.setCode(roleCode);
        theRole.setName(roleName);
        theRole.setWage(roleWage);

        mRoles.push_back(move(theRole));
        Save();
    }

    void Database::removeRole(int roleCode)
    {
        auto roleByCode = GetRoleByCode(roleCode);

        if( roleByCode == mRoles.end())
        {
            throw std::runtime_error("No Role with this code exists");
        }
        mRoles.erase(roleByCode);
        Save();
    }
    Role &Database::getRole(int roleCode)
    {
        for (int i = 0; i < mNextSlot; i++)
        {
            if (mRoles[i].getCode() == roleCode)
            {
                return mRoles[i];
            }
        }
        throw std::runtime_error("No Role with this code exists");
    }

    void Database::addDuty(int roleCode, string duty)
    {
        auto roleByCode = GetRoleByCode(roleCode);

        if( roleByCode == mRoles.end())
        {
            throw std::runtime_error("No Role with this code exists");
        }

        if(duty.size() < 3)
            throw std::runtime_error("Duty is too small");
        if((*roleByCode).hasDuty(duty))
            throw std::runtime_error("The role already has the duty");

        (*roleByCode).addDuty(duty);
    }

    void Database::removeDuty(int roleCode, string duty)
    {
        auto roleByCode = GetRoleByCode(roleCode);

        if( roleByCode == mRoles.end())
        {
            throw std::runtime_error("No Role with this code exists");
        }

        if(!(*roleByCode).hasDuty(duty))
            throw std::runtime_error("The role already doesn't have the duty");

        (*roleByCode).removeDuty(duty);
    }

    void Database::addRequirement(int roleCode, const string &requirement)
    {
        auto roleByCode = GetRoleByCode(roleCode);

        if( roleByCode == mRoles.end())
        {
            throw std::runtime_error("No Role with this code exists");
        }

        if(requirement.size() < 3)
            throw std::runtime_error("Requirement is too small");
        if((*roleByCode).hasRequirement(requirement))
            throw std::runtime_error("The role already has the requirement");

        (*roleByCode).addRequirement(requirement);
    }

    void Database::removeRequirement(int roleCode, const string &requirement)
    {
        auto roleByCode = GetRoleByCode(roleCode);

        if( roleByCode == mRoles.end())
        {
            throw std::runtime_error("No Role with this code exists");
        }

        if(!(*roleByCode).hasRequirement(requirement))
            throw std::runtime_error("The role already doesn't have the requirement");

        (*roleByCode).removeRequirement(requirement);
    }

    void Database::promoteRole(int roleCode, const float delta)
    {
        auto roleByCode = GetRoleByCode(roleCode);

        if( roleByCode == mRoles.end())
            throw std::runtime_error("No Role with this code exists");


        float oldWage = roleByCode->getWage();
        float newWage = oldWage + delta;
        roleByCode->setWage(newWage);
    }

    void Database::demoteRole(int roleCode, const float delta)
    {
        auto roleByCode = GetRoleByCode(roleCode);

        if( roleByCode == mRoles.end())
            throw std::runtime_error("No Role with this code exists");


        float oldWage = roleByCode->getWage();
        float newWage = oldWage - delta;
        if( newWage < 0)
            throw std::runtime_error("Wage cannot be negative!");


        roleByCode->setWage(newWage);
    }

    const vector<Role> &Database::getAllRoles()
    {
        return mRoles;
    }

    void Database::Save()
    {
        fileManager.Write(DB_FILE_NAME,mRoles);
    }
}
