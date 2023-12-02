#ifndef STAND_HPP
#define STAND_HPP

#include <string>
#include <vector>
#include "include/Manager.hpp"

class Stand {
private:
    std::string m_sName;
    double m_dSurface;
    unsigned int m_nId;
    std::vector<Manager*> m_pVecManagers;

public:
    Stand(std::string sName, double dSurface);
    virtual ~Stand();

    virtual std::string GetType() const;
    std::string GetStandName() const;
    unsigned int GetStandId() const;
    double GetStandSurface() const;
    std::vector<Manager*> GetManagers();

    void AddManager(Manager* pManagerToAdd);

    // Operator overloads
    bool operator==(const Stand& standToCompare) const;
};

#endif // STAND_HPP
