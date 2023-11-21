#ifndef EVENT_HPP
#define EVENT_HPP

#include <iostream>
#include <string>
#include <vector>
#include "include/Participant.hpp"
#include "include/Stand.hpp"

class Event {
private:
    std::string eventNom;
    std::string eventDate;
    std::string eventLieu;
    std::vector<Participant*> participants;
    std::vector<Stand*> stands;

public:
    Event(std::string name, std::string date, std::string lieu);
    ~Event();

    // Getters and setters
    std::string getEventNom() const;
    std::string getEventDate() const;
    std::string getEventLieu() const;
    std::vector<Participant*> getParticipants() const;
    std::vector<Stand*> getStands() const;

    void setEventNom(const std::string& nom);

    // Methods
    void ajouterParticipant(Participant* participant);
    void listeParticipants() const;
    void ajouterStand(Stand* stand);
    // Operator overloads
    bool operator==(const Event& e) const;
};

#endif // EVENT_HPP
