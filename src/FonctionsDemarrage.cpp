#include "include/FonctionsDemarrage.hpp"

json PreloadData() {
    std::ifstream ifstreamData(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation).toStdString() + "/data.json");
    json jsonData_out;
    if (!ifstreamData.is_open()) {
        QMessageBox::critical(nullptr, "EventX - Erreur","Aucune donnée n'a été trouvée. Une base de donnée vide vous sera fournie.");
        std::ofstream ofstreamData(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation).toStdString() + "/data.json");
        ofstreamData << jsonData_out;
        ofstreamData.close();
    } else {
        ifstreamData >> jsonData_out;
    }
    return jsonData_out;
}

unsigned int GetNumberOfEvents() {
    json jsonData_out;
    jsonData_out = PreloadData();
    return jsonData_out["events"].size();
}

unsigned int GetNumberOfParticipants() {
    json jsonData;
    jsonData = PreloadData();
    unsigned int nNumberOfParticipants_out = 0;
    for (auto& eventActual : jsonData["events"]) {
        nNumberOfParticipants_out += eventActual["participants"].size();
    }
    return nNumberOfParticipants_out;
}

unsigned int GetNumberOfStands() {
    json jsonData;
    jsonData = PreloadData();
    unsigned int nNumberOfStands_out = 0;
    for (auto& eventActual : jsonData["events"]) {
        nNumberOfStands_out += eventActual["stands"].size();
    }
    return nNumberOfStands_out;
}

unsigned int GetNumberOfManagers() {
    json jsonData;
    jsonData = PreloadData();
    unsigned int nNumberOfManagers_out = 0;
    // we look at the number of managers on each stand for each event
    for (auto& eventActual : jsonData["events"]) {
        for (auto& standActual : eventActual["stands"]) {
            nNumberOfManagers_out += standActual["managers"].size();
        }
    }
    return nNumberOfManagers_out;
}

unsigned int GetNumberOfParticipantsFromAEvent(const json& jsonEventToAnalyze_in) {
    if (jsonEventToAnalyze_in.contains("participants") && jsonEventToAnalyze_in["participants"].is_array()) {
        return jsonEventToAnalyze_in["participants"].size();
    }
    // If "participants" is not an array or does not exist, return 0
    return 0;
}

unsigned int GetNumberOfStandsFromAEvent(const json& jsonEventToAnalyze_in) {
    if (jsonEventToAnalyze_in.contains("stands") && jsonEventToAnalyze_in["stands"].is_array()) {
        return jsonEventToAnalyze_in["stands"].size();
    }
    // If "participants" is not an array or does not exist, return 0
    return 0;
}

unsigned int GetNumberOfManagersFromAStand(const json& jsonEventToAnalyze_in) {
    if (jsonEventToAnalyze_in.contains("managers") && jsonEventToAnalyze_in["managers"].is_array()) {
        return jsonEventToAnalyze_in["managers"].size();
    }
    // If "managers" is not an array or does not exist, return 0
    return 0;
}