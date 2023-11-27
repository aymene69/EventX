#ifndef FONCTIONSDEMARRAGE_HPP
#define FONCTIONSDEMARRAGE_HPP
#include "nlohmann/json.hpp"

using json = nlohmann::json;

json preloadData();

int getNbEvents();
int getNbParticipants();
int getNbStands();
int getNbManagers();
int getNbManagersFromStand(const json& stand);
int getNbParticipantsFromEvent(const json& event);
int getNbStandsFromEvent(const json& event);

#endif
