#include "include/Event.hpp"

Event::Event(std::string name, std::string date, std::string lieu) : eventNom(name), eventDate(date), eventLieu(lieu) {} // constructeur

Event::~Event() { // destructeur
    for (auto participant : participants) {
        delete participant;
    }
    for (auto stand : stands) {
        delete stand;
    }
}

std::string Event::getEventNom() const { // avoir le nom de l'event
    return eventNom;
}

void Event::setEventNom(const std::string& nom) { // changer le nom de l'event
    eventNom = nom;
}

void Event::ajouterParticipant(Participant* participant) { // ajouter un participant à l'event
    participants.push_back(participant);
}

void Event::listeParticipants() const { // afficher la liste des participants à l'event
    std::cout << "Participants pour l'événement " << eventNom << ":\n";
    for (const auto& participant : participants) {
        std::cout << participant->getNomParticipant() << "\n";
    }
}

void Event::ajouterStand(Stand* stand) { // ajouter un stand à l'event
    stands.push_back(stand);
}

bool Event::operator==(const Event& other) const { // comparer deux events
    return eventNom == other.eventNom && eventDate == other.eventDate && eventLieu == other.eventLieu;
}
