#ifndef PARTICIPANT_HPP
#define PARTICIPANT_HPP

#include <string>

class Participant {
private:
    std::string m_sName;
    bool m_bIsVip;
    std::string m_sPhoneNumber;
    std::string m_sMail;
    unsigned int m_nId;

public:
    Participant(std::string sName, bool bIsVip, std::string sPhoneNumber, std::string sMail); // constructor
    virtual ~Participant(); // destructor

    // Getters and setters
    virtual std::string GetType() const; // Get the type of participant
    std::string GetParticipantName() const; // Get participant's name
    bool ParticipantIsVip(); // Know if the participant is VIP
    std::string GetParticipantPhoneNumber() const; // Get the participant's number
    std::string GetParticipantMail() const; // Get the participant's email
    unsigned int GetParticipantId() const; // Get participant id

    bool operator==(const Participant& participantToCompare) const;
};

#endif
