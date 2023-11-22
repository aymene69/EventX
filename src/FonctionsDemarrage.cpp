#include "nlohmann/json.hpp"
#include "include/FonctionsDemarrage.hpp"
#include <fstream>
#include <QMessageBox>

using json = nlohmann::json;

json preloadData() {
    std::ifstream i("data.json");

    if (!i.is_open()) {
        QMessageBox::critical(nullptr, "EventX - Erreur","Aucune donnée n'a été trouvée. Une base de donnée vide vous sera fournie.");
        std::ofstream o("data.json");
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

int getNbEvents(json data) {
    const json& events = data["events"];
    return events.size();
}