/********************************************************************
    created:	2023-11-20
    file path:	include/Manager.hpp
    author:		W.I.P.
    copyright:	UNLICENSE

    purpose: W.I.P.
*********************************************************************/

#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <string>

class Manager {
private:
    std::string managerNom;
    int managerId;
    std::string managerNum;

public:
    Manager(std::string nom, int id, std::string num);
    virtual ~Manager();

    virtual std::string getType() const;

    // Getters
    std::string getManagerNom() const;
    int getManagerId() const;
    std::string getManagerNum() const;

    // Setter for contact (assuming id doesn't change)
    void setManagerNum(const std::string& num);

    // Operator overloads
    bool operator==(const Manager& m) const;

};

#endif // MANAGER_HPP
