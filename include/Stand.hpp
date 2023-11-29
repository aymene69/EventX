#ifndef STAND_HPP
#define STAND_HPP

#include <string>
#include <vector>
#include "include/Manager.hpp"
class Stand {
private:
    std::string standNom;
    int standId;
    double standSurface;
    std::vector<Manager*> managers;

public:
    Stand(std::string nom, double surface);
    virtual ~Stand();


    virtual std::string getType() const;
    std::string getStandNom() const;
    int getStandId() const;
    double getStandSurface() const;
    std::vector<Manager*> getManagers();


    void addManager(Manager* m);

    // Operator overloads
    bool operator==(const Stand& other) const;
};

#endif // STAND_HPP
