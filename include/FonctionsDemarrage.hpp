#ifndef FONCTIONSDEMARRAGE_HPP
#define FONCTIONSDEMARRAGE_HPP

#include "nlohmann/json.hpp"
#include <fstream>
#include <iostream>
#include <QMessageBox>
#include <QStandardPaths>

using json = nlohmann::json;

json PreloadData();

unsigned int GetNumberOfEvents();
unsigned int GetNumberOfParticipants();
unsigned int GetNumberOfStands();
unsigned int GetNumberOfManagers();
unsigned int GetNumberOfParticipantsFromAEvent(const json& event);
unsigned int GetNumberOfManagersFromAStand(const json& stand);
unsigned int GetNumberOfStandsFromAEvent(const json& event);

#endif
