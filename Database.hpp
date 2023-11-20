#pragma once

#include <iostream>
#include "radio.hpp"
#include "filemanager.h"

namespace Records
{

    class Database
    {
    private:
        FileManager fileManager;
        Database();
        ~Database();

        auto GetRoleByCode(int roleCode) -> decltype (vector<Role>().begin());
    public:
        static Database& GetInstance();
        void addRole(int roleCode, std::string roleName, float roleWage);
        void removeRole(int roleCode);
        Role& getRole(int roleCode);

        void addDuty(int roleCode,std::string duty);
        void removeDuty(int roleCode,std::string duty);

        void addRequirement(int roleCode, const string &requirement);
        void removeRequirement(int roleCode, const string &requirement);

        void promoteRole(int roleCode, const float delta);
        void demoteRole(int roleCode, const float delta);

        const vector<Role>& getAllRoles();

    Database(const Database& ) = delete;
    Database& operator= (const Database& ) = delete;

    protected:
        void Save();
        vector<Role> mRoles;
        int mNextSlot;
        int mNextRoleNumber;
    };
}
