#include "include/Participant.hpp"

Participant::Participant(int participantID, std::string name, bool vip, std::string numero, std::string email) : participantID(participantID), participantNom(name), participantEstVIP(vip), participantNum(numero), participantEmail(email) {} // constructeur

Participant::~Participant() {} // destructeur

std::string Participant::getType() const { // avoir le type de participant
    return "Participant";
}

int Participant::getIDParticipantID() const { // avoir l'id du participant
    return participantID;
}

std::string Participant::getNomParticipant() const { // avoir le nom du participant
    return participantNom;
}

bool Participant::getVIPParticipant() { // savoir si le participant est VIP
    return participantEstVIP;
}

std::string Participant::getNumParticipant() const { // avoir le numéro du participant
    return participantNum;
}

std::string Participant::getEmailParticipant() const { // avoir l'email du participant
    return participantEmail;
}


bool Participant::operator==(const Participant& p) const { // p=celui avec qui on va comparer
    return participantID == p.participantID;
}
