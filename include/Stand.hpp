/********************************************************************
    created:	2023-11-20
    file path:	include/Stand.hpp
    author:		W.I.P.
    copyright:	UNLICENSE

    purpose: W.I.P.
*********************************************************************/

#ifndef STAND_HPP
#define STAND_HPP

#include <string>
#include <vector>
#include "include/Manager.hpp"
class Stand {
private:
    std::string standNom;
    int standNum;
    double standSurface;
    std::vector<Manager*> managers;

public:
    Stand(std::string nom, int num);
    virtual ~Stand();


    virtual std::string getType() const;
    std::string getStandNom() const;
    int getStandNum() const;
    double getStandSurface() const;
    std::vector<Manager*> getManagers();


    void addManager(Manager* m);

    // Operator overloads
    bool operator==(const Stand& other) const;
};

#endif // STAND_HPP
