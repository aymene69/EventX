#include "include/Manager.hpp"

Manager::Manager(std::string nom, int id, std::string num) : managerNom(nom), managerId(id), managerNum(num) {}

Manager::~Manager() {}

std::string Manager::getType() const {
    return "Manager";
}

std::string Manager::getManagerNom() const {
    return managerNom;
}

int Manager::getManagerId() const {
    return managerId;
}

std::string Manager::getManagerNum() const {
    return managerNum;
}

void Manager::setManagerNum(const std::string& num) {
    managerNum = num;
}

bool Manager::operator==(const Manager& m) const {
    return managerId == m.managerId;
}
