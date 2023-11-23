#include "include/FonctionsJson.hpp"
#include <fstream>
#include <regex>
#include "nlohmann/json.hpp"
#include "include/Event.hpp"
#include "include/Participant.hpp"
#include "include/Stand.hpp"
#include "include/Manager.hpp"

using json = nlohmann::json;

bool verifDate(std::string date) {
    std::regex dateRegex("([0-9]{2})/([0-9]{2})/([0-9]{4})");
    return std::regex_match(date, dateRegex);
}

void ajouterEvent(void* object) {
    std::ifstream i("data.json");
    json j;
    i >> j;
    i.close();
    Event* event = (Event*) object;
    json eventJson;
    eventJson["nom"] = event->getEventNom();
    eventJson["date"] = event->getEventDate();
    eventJson["lieu"] = event->getEventLieu();
    j["events"].push_back(eventJson);

    std::ofstream o("data.json");
    o << std::setw(4) << j << std::endl;
    o.close();
}

void ajouterParticip(void* object, int index) {
    std::ifstream i("data.json");
    json j;
    i >> j;
    i.close();
    Participant* participant = (Participant*) object;
    json participantJson;
    //on ajoute les participants dans l'index de l'event
    participantJson["nom"] = participant->getNomParticipant();
    participantJson["vip"] = participant->getVIPParticipant();
    participantJson["numero"] = participant->getNumParticipant();
    participantJson["email"] = participant->getEmailParticipant();
    j["events"][index]["participants"].push_back(participantJson);

    std::ofstream o("data.json");
    o << std::setw(4) << j << std::endl;
    o.close();
}

void modifierEvent(void* object, int index) {
    std::ifstream i("data.json");
    json j;
    i >> j;
    i.close();

    Event* event = static_cast<Event*>(object);
    json eventJson;
    eventJson["nom"] = event->getEventNom();
    eventJson["date"] = event->getEventDate();
    eventJson["lieu"] = event->getEventLieu();
    j["events"][index] = eventJson;


    std::ofstream o("data.json");
    o << std::setw(4) << j << std::endl;
    o.close();
}

void modifierParticip(void* object, int indexEvent, int indexParticipant) {
    std::ifstream i("data.json");
    json j;
    i >> j;
    i.close();

    Participant* participant = static_cast<Participant*>(object);
    json participantJson;
    participantJson["nom"] = participant->getNomParticipant();
    participantJson["vip"] = participant->getVIPParticipant();
    participantJson["numero"] = participant->getNumParticipant();
    participantJson["email"] = participant->getEmailParticipant();
    j["events"][indexEvent]["participants"][indexParticipant] = participantJson;

    std::ofstream o("data.json");
    o << std::setw(4) << j << std::endl;
    o.close();
}

void supprimerEvent(void* object, int index) {
    std::ifstream i("data.json");
    json j;
    i >> j;
    i.close();

    j["events"].erase(index);


    std::ofstream o("data.json");
    o << std::setw(4) << j << std::endl;
    o.close();
}

void supprimerParticip(int indexEvent, int indexParticipant) {
    json j;
    std::ifstream i("data.json");
    i >> j;
    i.close();

    j["events"][indexEvent]["participants"].erase(indexParticipant);

    std::ofstream o("data.json");
    o << std::setw(4) << j << std::endl;
    o.close();
}

