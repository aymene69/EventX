/********************************************************************
    created:	2023-11-22
    file path:	include/FonctionsDemarrage.hpp
    author:		W.I.P.
    copyright:	UNLICENSE

    purpose: W.I.P.
*********************************************************************/

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
