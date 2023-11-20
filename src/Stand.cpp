#include "include/Stand.hpp"

Stand::Stand(std::string nom, int num) : standNom(nom), standNum(num) {} // constructeur

Stand::~Stand() { // destructeur
    for (auto& m : managers) {
        delete m;
    }
}

std::string Stand::getStandNom() const { // avoir le nom du stand
    return standNom;
}

int Stand::getStandNum() const { // avoir le numéro du stand
    return standNum;
}

std::vector<Manager*> Stand::getManagers() { // avoir la liste des managers du stand
    return managers;
}

void Stand::addManager(Manager* manager) { // ajouter un manager au stand
    managers.push_back(manager);
}


bool Stand::operator==(const Stand& s) const { // comparer deux stands
    return standNum == s.standNum;
}
