#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <string>

class Manager {
private:
    std::string m_sName;
    std::string m_sPhoneNumber;
    unsigned int m_nId;

public:
    Manager(std::string m_sName, std::string m_sPhoneNumber, unsigned int m_nId);
    virtual ~Manager();

    virtual std::string GetType() const;

    // Getters
    std::string GetManagerName() const;
    std::string GetManagerPhoneNumber() const;
    unsigned int GetManagerId() const;

    // Setter for contact (assuming id doesn't change)
    void SetManagerPhoneNumber(const std::string& sPhoneNumber);

    // Operator overloads
    bool operator==(const Manager& managerToCompare) const;
};

#endif // MANAGER_HPP
