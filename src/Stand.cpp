#include "include/Stand.hpp"

Stand::Stand(std::string sName, double dSurface) : m_sName(sName), m_dSurface(dSurface), m_nId(0) {} // constructeur

Stand::~Stand() { // Destructor
    for (auto& managerActual : this->m_pVecManagers) {
        delete managerActual;
    }
}

std::string Stand::GetType() const { // Get the type of stand
    return "Stand";
}

std::string Stand::GetStandName() const {  // Get the stand name
    return this->m_sName;
}

unsigned int Stand::GetStandId() const { // Get the stand Id
    return this->m_nId;
}

double Stand::GetStandSurface() const { // Get the stand surface
    return this->m_dSurface;
}

std::vector<Manager*> Stand::GetManagers() { // Get the list of managers
    return this->m_pVecManagers;
}

void Stand::AddManager(Manager* pManagerToAdd) { // Add a manager to the booth
    this->m_pVecManagers.push_back(pManagerToAdd);
}

bool Stand::operator==(const Stand& standToCompare) const { // Compare two stands
    return this->m_nId == standToCompare.m_nId;
}