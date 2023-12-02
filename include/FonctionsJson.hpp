#ifndef FONCTIONSJSON_HPP
#define FONCTIONSJSON_HPP

#include <iostream>
#include <fstream>
#include <regex>
#include <QStandardPaths>
#include "nlohmann/json.hpp"
#include "include/Event.hpp"
#include "include/Participant.hpp"
#include "include/Stand.hpp"
#include "include/Manager.hpp"
#include "include/FonctionsDemarrage.hpp"

using json = nlohmann::json;

void AddEvent(void* pObject_in);
void AddParticipant(void* pObject_in, unsigned int nIndexEvent_in);
void AddStand(void* pObject_in, unsigned int nIndexEvent_in);
void AddManager(void* pObject_in, unsigned int nIndexEvent_in, unsigned int nIndexStand_in);

void ModifyEvent(void* object_in, unsigned int nIndex_in);
void ModifyParticipant(void* object_in, unsigned int nIndexEvent_in, unsigned int nIndexParticipant_in);
void ModifyStand(void* object_in, unsigned int nIndexEvent_in, unsigned int nIndexStand_in);
void ModifyManager(void* object_in, unsigned int nIndexEvent_in, unsigned int nIndexStand_in, unsigned int nIndexManager_in);

void DeleteEvent(void* object_in, unsigned int nIndexEvent_in);
void DeleteParticipant(unsigned int nIndexEvent_in, unsigned int nIndexParticipant_in);
void DeleteStand(unsigned int nIndexEvent_in, unsigned int nIndexStand_in);
void DeleteManager(unsigned int nIndexEvent_in, unsigned int nIndexStand_in, unsigned int nIndexManager_in);

#endif
