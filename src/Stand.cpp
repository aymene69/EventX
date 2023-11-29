#include "include/Stand.hpp"

Stand::Stand(std::string nom, double surface) : standNom(nom), standSurface(surface), standId(0) {} // constructeur

Stand::~Stand() { // destructeur
    for (auto& m : managers) {
        delete m;
    }
}

std::string Stand::getType() const { // avoir le type de stand
    return "Stand";
}

std::string Stand::getStandNom() const { // avoir le nom du stand
    return standNom;
}

int Stand::getStandId() const { // avoir le numéro du stand
    return standId;
}

double Stand::getStandSurface() const { // avoir la surface du stand
    return standSurface;
}

std::vector<Manager*> Stand::getManagers() { // avoir la liste des managers du stand
    return managers;
}

void Stand::addManager(Manager* manager) { // ajouter un manager au stand
    managers.push_back(manager);
}


bool Stand::operator==(const Stand& s) const { // comparer deux stands
    return standId == s.standId;
}
