/********************************************************************
    created:	2023-11-22
    file path:	src/FonctionsDemarrage.cpp
    author:		W.I.P.
    copyright:	UNLICENSE

    purpose: W.I.P.
*********************************************************************/

#include "nlohmann/json.hpp"
#include "include/FonctionsDemarrage.hpp"
#include <fstream>
#include <iostream>
#include <QMessageBox>
#include <QStandardPaths>

using json = nlohmann::json;

json preloadData() {
    std::ifstream i(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation).toStdString() + "/data.json");

    if (!i.is_open()) {
        QMessageBox::critical(nullptr, "EventX - Erreur","Aucune donnée n'a été trouvée. Une base de donnée vide vous sera fournie.");
        std::ofstream o(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation).toStdString() + "/data.json");
        json data;
        o << data;
        o.close();
        return data;
    } else {
        json data;
        i >> data;
        return data;
    }
}

int getNbEvents() {
    json j;
    j = preloadData();
    return j["events"].size();
}

int getNbParticipants() {
    json j;
    j = preloadData();
    int nbParticipants = 0;
    for (auto& event : j["events"]) {
        nbParticipants += event["participants"].size();
    }
    return nbParticipants;
}

int getNbParticipantsFromEvent(const json& event) {
    if (event.contains("participants") && event["participants"].is_array()) {
        return event["participants"].size();
    }
    // Si "participants" n'est pas un tableau ou n'existe pas, renvoyer 0
    return 0;
}

int getNbStands() {
    json j;
    j = preloadData();
    int nbStands = 0;
    for (auto& event : j["events"]) {
        nbStands += event["stands"].size();
    }
    return nbStands;
}

int getNbStandsFromEvent(const json& event) {
    if (event.contains("stands") && event["stands"].is_array()) {
        return event["stands"].size();
    }
    // Si "participants" n'est pas un tableau ou n'existe pas, renvoyer 0
    return 0;
}

int getNbManagers() {
    json j;
    j = preloadData();
    int nbManagers = 0;
    // on regarde le nombre de managers de chaque stands de chaque event
    for (auto& event : j["events"]) {
        for (auto& stand : event["stands"]) {
            nbManagers += stand["managers"].size();
        }
    }
    return nbManagers;
}

int getNbManagersFromStand(const json& stand) {
        if (stand.contains("managers") && stand["managers"].is_array()) {
            return stand["managers"].size();
        }
        // Si "managers" n'est pas un tableau ou n'existe pas, renvoyer 0
        return 0;
}