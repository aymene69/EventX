#include "include/Manager.hpp"

Manager::Manager(std::string sName, std::string sPhoneNumber, unsigned int nId) : m_sName(sName), m_sPhoneNumber(sPhoneNumber), m_nId(nId) {}

Manager::~Manager() {}

std::string Manager::GetType() const {
    return "Manager";
}

std::string Manager::GetManagerName() const {
    return m_sName;
}

std::string Manager::GetManagerPhoneNumber() const {
    return m_sPhoneNumber;
}

unsigned int Manager::GetManagerId() const {
    return m_nId;
}

void Manager::SetManagerPhoneNumber(const std::string& sPhoneNumber) {
    m_sPhoneNumber = sPhoneNumber;
}

bool Manager::operator==(const Manager& managerToCompare) const {
    return this->m_nId == managerToCompare.m_nId;
}
