#ifndef EVENT_HPP
#define EVENT_HPP

#include <iostream>
#include <string>
#include <vector>
#include "include/Participant.hpp"
#include "include/Stand.hpp"

class Event {
private:
    std::string m_sEventName;
    std::string m_sEventDate;
    std::string m_sEventLocation;
    std::vector<Participant*> m_pVecParticipantsAll;
    std::vector<Stand*> m_pVecStandAll;

public:
    // Constructor and destructor
    Event(std::string sName_in, std::string sDate_in, std::string sLocation_in);
    virtual ~Event();

    // Getters and setters
    virtual std::string GetType() const;
    std::string GetEventName() const;
    std::string GetEventDate() const;
    std::string GetEventLocation() const;
    std::vector<Participant*> GetAllParticipants() const;
    std::vector<Stand*> GetAllStands() const;

    void SetEventName(const std::string& sName_in);
    void SetEventDate(const std::string& sDate_in);
    void SetEventLocation(const std::string& sLocation_in);

    // Methods
    void AddParticipant(Participant* pParticipantToAdd_in);
    void AddStand(Stand* pStandToAdd_in);
    void DisplayAllParticipants() const;
    // Operator overloads
    bool operator==(const Event& eventToCompare_in) const;
};

#endif // EVENT_HPP