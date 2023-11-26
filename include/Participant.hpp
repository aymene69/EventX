/********************************************************************
    created:	2023-11-20
    file path:	include/Participant.hpp
    author:		W.I.P.
    copyright:	UNLICENSE

    purpose: W.I.P.
*********************************************************************/

#ifndef PARTICIPANT_HPP
#define PARTICIPANT_HPP

#include <string>

class Participant {
private:
    int participantID;
    std::string participantNom;
    bool participantEstVIP;
    std::string participantNum;
    std::string participantEmail;


public:
    Participant(int participantID, std::string name, bool vip, std::string numero, std::string email); // constructeur
    virtual ~Participant(); // destructeur

// Getters and setters
    virtual std::string getType() const; // avoir le type de participant
    int getIDParticipantID() const; // avoir l'id du participant
    std::string getNomParticipant() const; // avoir le nom du participant
    bool getVIPParticipant(); // savoir si le participant est VIP
    std::string getNumParticipant() const; // avoir le numéro du participant
    std::string getEmailParticipant() const; // avoir l'email du participant

    bool operator==(const Participant& p) const; // p=celui avec qui on va comparer
};

#endif
