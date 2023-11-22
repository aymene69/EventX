#ifndef FONCTIONSDEMARRAGE_HPP
#define FONCTIONSDEMARRAGE_HPP
#include "nlohmann/json.hpp"

using json = nlohmann::json;

json preloadData();

int getNbEvents(json data);

#endif
