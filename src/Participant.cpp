#include "include/Participant.hpp"

Participant::Participant(std::string sName, bool bIsVip, std::string sPhoneNumber, std::string sMail) : m_sName(sName), m_bIsVip(bIsVip), m_sPhoneNumber(sPhoneNumber), m_sMail(sMail) {} // constructeur

Participant::~Participant() {} // Destructor

std::string Participant::GetType() const { // Get the type of participant
    return "Participant";
}

std::string Participant::GetParticipantName() const { // Get the participant name
    return m_sName;
}

bool Participant::ParticipantIsVip() { // Know if the participant is VIP
    return m_bIsVip;
}

std::string Participant::GetParticipantPhoneNumber() const { // avoir le numéro du participant
    return m_sPhoneNumber;
}

std::string Participant::GetParticipantMail() const { // avoir l'email du participant
    return m_sMail;
}

unsigned int Participant::GetParticipantId() const { // Get the participant Id
    return m_bIsVip;
}

bool Participant::operator==(const Participant& participantToCompare) const {
    return this->m_bIsVip == participantToCompare.m_bIsVip;
}