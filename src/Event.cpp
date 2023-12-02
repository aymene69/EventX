#include "include/Event.hpp"

Event::Event(std::string sName_in, std::string sDate_in, std::string sLocation_in) : m_sEventName(sName_in), m_sEventDate(sDate_in), m_sEventLocation(sLocation_in) {} // constructor

Event::~Event() {} // Destructor

std::string Event::GetType() const { // Get event type
    return "event";
}

std::string Event::GetEventName() const { // Get event name
    return this->m_sEventName;
}

std::string Event::GetEventDate() const { // Get event date
    return this->m_sEventDate;
}

std::string Event::GetEventLocation() const { // Get event location
    return this->m_sEventLocation;
}

std::vector<Participant*> Event::GetAllParticipants() const { // Get all participant of the event
    return this->m_pVecParticipantsAll;
}

std::vector<Stand*> Event::GetAllStands() const { // Get all stands of the event
    return this->m_pVecStandAll;
}

void Event::SetEventName(const std::string& sName_in) { // Change name of the event
    this->m_sEventName = sName_in;
}

void Event::SetEventDate(const std::string& sDate_in) { // Change date of the event
    this->m_sEventDate = sDate_in;
}

void Event::SetEventLocation(const std::string& sLocation_in) { // Change location of the event
    this->m_sEventLocation = sLocation_in;
}

void Event::AddParticipant(Participant* pParticipantToAdd_in) { // Add a participant to the event
    this->m_pVecParticipantsAll.push_back(pParticipantToAdd_in);
}

void Event::AddStand(Stand* pStandToAdd_in) { // Add a stand to the event
    this->m_pVecStandAll.push_back(pStandToAdd_in);
}

void Event::DisplayAllParticipants() const { // Display list of event participants
    std::cout << "Participants pour l'événement " << this->m_sEventName << ":\n";
    for (const auto& participant : this->m_pVecParticipantsAll) {
        std::cout << participant->GetParticipantName() << "\n";
    }
}

bool Event::operator==(const Event& eventToCompare_in) const { // Compare two events
    return this->m_sEventName == eventToCompare_in.m_sEventName && this->m_sEventDate == eventToCompare_in.m_sEventDate && this->m_sEventLocation == eventToCompare_in.m_sEventLocation;
}