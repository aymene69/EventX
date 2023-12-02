#include "include/FonctionsJson.hpp"

void AddEvent(void* pObject_in) {
    std::ifstream ifstreamData(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation).toStdString() + "/data.json");
    json jsonData;
    ifstreamData >> jsonData;
    ifstreamData.close();
    Event* eventToAdd = (Event*) pObject_in;
    json eventJson;
    eventJson["nom"] = eventToAdd->GetEventName();
    eventJson["date"] = eventToAdd->GetEventDate();
    eventJson["lieu"] = eventToAdd->GetEventLocation();
    jsonData["events"].push_back(eventJson);

    std::ofstream ofstreamData(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation).toStdString() + "/data.json");
    ofstreamData << std::setw(4) << jsonData << std::endl;
    ofstreamData.close();
}

void AddParticipant(void* pObject_in, unsigned int nIndexEvent_in) {
    std::ifstream ifstreamData(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation).toStdString() + "/data.json");
    json jsonData;
    ifstreamData >> jsonData;
    ifstreamData.close();
    Participant* participantToAdd = (Participant*) pObject_in;
    json participantJson;
    // Add participants to the event index
    participantJson["id"] = GetNumberOfParticipants() +1;
    participantJson["nom"] = participantToAdd->GetParticipantName();
    participantJson["vip"] = participantToAdd->ParticipantIsVip();
    participantJson["numero"] = participantToAdd->GetParticipantPhoneNumber();
    participantJson["email"] = participantToAdd->GetParticipantMail();
    jsonData["events"][nIndexEvent_in]["participants"].push_back(participantJson);

    std::ofstream ofstreamData(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation).toStdString() + "/data.json");
    ofstreamData << std::setw(4) << jsonData << std::endl;
    ofstreamData.close();
}

void AddStand(void* pObject_in, unsigned int nIndexEvent_in) {
    std::ifstream ifstreamData(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation).toStdString() + "/data.json");
    json jsonData;
    ifstreamData >> jsonData;
    ifstreamData.close();
    Stand* stand = (Stand*)pObject_in;
    json jsonStand;
    // Add stands to event index
    jsonStand["nom"] = stand->GetStandName();
    jsonStand["id"] = stand->GetStandId();
    jsonStand["surface"] = stand->GetStandSurface();
    jsonData["events"][nIndexEvent_in]["stands"].push_back(jsonStand);

    std::ofstream ofstreamData(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation).toStdString() + "/data.json");
    ofstreamData << std::setw(4) << jsonData << std::endl;
    ofstreamData.close();
}

void AddManager(void* pObject_in, unsigned int nIndexEvent_in, unsigned int nIndexStand_in) {
    std::ifstream ifstreamData(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation).toStdString() + "/data.json");
    json jsonData;
    ifstreamData >> jsonData;
    ifstreamData.close();
    Manager* manager = (Manager*)pObject_in;
    json managerJson;
    int* pnId = new int(0);
    *pnId = GetNumberOfManagers() +1;
    //on ajoute les managers dans l'index de l'event
    managerJson["nom"] = manager->GetManagerName();
    managerJson["numero"] = manager->GetManagerPhoneNumber();
    managerJson["id"] = *pnId;
    jsonData["events"][nIndexEvent_in]["stands"][nIndexStand_in]["managers"].push_back(managerJson);

    std::ofstream ofstreamData(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation).toStdString() + "/data.json");
    ofstreamData << std::setw(4) << jsonData << std::endl;
    ofstreamData.close();
    delete pnId;
}

void ModifyEvent(void* pObject_in, unsigned int nIndexEvent_in) {
    std::ifstream ifstreamData(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation).toStdString() + "/data.json");
    json jsonData;
    ifstreamData >> jsonData;
    ifstreamData.close();

    Event* event = static_cast<Event*>(pObject_in);
    json eventJson;
    eventJson["nom"] = event->GetEventName();
    eventJson["date"] = event->GetEventDate();
    eventJson["lieu"] = event->GetEventLocation();
    jsonData["events"][nIndexEvent_in] = eventJson;


    std::ofstream ofstreamData(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation).toStdString() + "/data.json");
    ofstreamData << std::setw(4) << jsonData << std::endl;
    ofstreamData.close();
}

void ModifyParticipant(void* pObject_in, unsigned int nIndexEvent_in, unsigned int nIndexParticipant_in) {
    std::ifstream ifstreamData(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation).toStdString() + "/data.json");
    json jsonData;
    ifstreamData >> jsonData;
    ifstreamData.close();

    Participant* participant = static_cast<Participant*>(pObject_in);
    json participantJson;
    participantJson["nom"] = participant->GetParticipantName();
    participantJson["vip"] = participant->ParticipantIsVip();
    participantJson["numero"] = participant->GetParticipantPhoneNumber();
    participantJson["email"] = participant->GetParticipantMail();
    jsonData["events"][nIndexEvent_in]["participants"][nIndexParticipant_in] = participantJson;

    std::ofstream ofstreamData(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation).toStdString() + "/data.json");
    ofstreamData << std::setw(4) << jsonData << std::endl;
    ofstreamData.close();
}

void ModifyStand(void* pObject_in, unsigned int nIndexEvent_in, unsigned int nIndexStand_in) {
    std::ifstream ifstreamData(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation).toStdString() + "/data.json");
    json jsonData;
    ifstreamData >> jsonData;
    ifstreamData.close();

    Stand* stand = static_cast<Stand*>(pObject_in);
    json standJson;
    standJson["nom"] = stand->GetStandName();
    standJson["id"] = stand->GetStandId();
    standJson["surface"] = stand->GetStandSurface();
    jsonData["events"][nIndexEvent_in]["stands"][nIndexStand_in] = standJson;

    std::ofstream ofstreamData(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation).toStdString() + "/data.json");
    ofstreamData << std::setw(4) << jsonData << std::endl;
    ofstreamData.close();
}

void ModifyManager(void* pObject_in, unsigned int nIndexEvent_in, unsigned int nIndexStand_in, unsigned int nIndexManager_in) {
    std::ifstream ifstreamData(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation).toStdString() + "/data.json");
    json jsonData;
    ifstreamData >> jsonData;
    ifstreamData.close();

    Manager* managerWithNewValues = static_cast<Manager*>(pObject_in);
    json jsonManagerToModify;
    jsonManagerToModify["nom"] = managerWithNewValues->GetManagerName();
    jsonManagerToModify["numero"] = managerWithNewValues->GetManagerPhoneNumber();
    jsonManagerToModify["id"] = managerWithNewValues->GetManagerId();
    jsonData["events"][nIndexEvent_in]["stands"][nIndexStand_in]["managers"][nIndexManager_in] = jsonManagerToModify;

    std::ofstream ofstreamData(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation).toStdString() + "/data.json");
    ofstreamData << std::setw(4) << jsonData << std::endl;
    ofstreamData.close();
}

void DeleteEvent(void* pObject_in, unsigned int nIndexEvent_in) {
    std::ifstream ifstreamData(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation).toStdString() + "/data.json");
    json jsonData;
    ifstreamData >> jsonData;
    ifstreamData.close();

    jsonData["events"].erase(nIndexEvent_in);

    std::ofstream ofstreamData(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation).toStdString() + "/data.json");
    ofstreamData << std::setw(4) << jsonData << std::endl;
    ofstreamData.close();
}

void DeleteParticipant(unsigned int nIndexEvent_in, unsigned int nIndexParticipant_in) {
    json jsonData;
    std::ifstream ifstreamData(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation).toStdString() + "/data.json");
    ifstreamData >> jsonData;
    ifstreamData.close();

    jsonData["events"][nIndexEvent_in]["participants"].erase(nIndexParticipant_in);

    std::ofstream ofstreamData(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation).toStdString() + "/data.json");
    ofstreamData << std::setw(4) << jsonData << std::endl;
    ofstreamData.close();
}

void DeleteStand(unsigned int nIndexEvent_in, unsigned int nIndexStand_in) {
    json jsonData;
    std::ifstream ifstreamData(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation).toStdString() + "/data.json");
    ifstreamData >> jsonData;
    ifstreamData.close();

    jsonData["events"][nIndexEvent_in]["stands"].erase(nIndexStand_in);

    std::ofstream ofstreamData(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation).toStdString() + "/data.json");
    ofstreamData << std::setw(4) << jsonData << std::endl;
    ofstreamData.close();
}

void DeleteManager(unsigned int nIndexEvent_in, unsigned int nIndexStand_in, unsigned int nIndexManager_in) {
    json jsonData;
    std::ifstream ifstreamData(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation).toStdString() + "/data.json");
    ifstreamData >> jsonData;
    ifstreamData.close();

    jsonData["events"][nIndexEvent_in]["stands"][nIndexStand_in]["managers"].erase(nIndexManager_in);

    std::ofstream ofstreamData(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation).toStdString() + "/data.json");
    ofstreamData << std::setw(4) << jsonData << std::endl;
    ofstreamData.close();
}