#include "nlohmann/json.hpp"
#include <fstream>
#include <QFormLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QMessageBox>
#include <QLabel>
#include <QCheckBox>
#include <QStandardPaths>
#include <QStandardItemModel>
#include <QTreeView>
#include "include/Event.hpp" // Inclure les fichiers d'en-t�te n�cessaires
#include "include/Stand.hpp"
#include "include/Manager.hpp"
#include "include/FonctionsJson.hpp"
#include "include/GestionManager.hpp"
#include "include/FonctionsDemarrage.hpp"
#include "include/ViewData.hpp"

using json = nlohmann::json;




ViewData::ViewData(QWidget* parent) : QDialog(parent) {
    setWindowTitle("EventX - Visualisation des donnees");

    // Charger les donn�es depuis le fichier JSON
    json data = preloadData();

    // V�rifiez s'il y a des �v�nements avant d'essayer d'afficher les donn�es
    if (getNbEvents() == 0) {
        QMessageBox::warning(this, "Avertissement", "Aucun �v�nement � afficher.");
        return;
    }

    // Cr�er le mod�le et la vue pour afficher les donn�es en arbre
    QStandardItemModel* model = new QStandardItemModel(this);
    QTreeView* treeView = new QTreeView(this);
    treeView->setModel(model);

    // Parcourir les �v�nements
    for (const auto& event : data["events"]) {
        QStandardItem* eventItem = new QStandardItem(QString("Evenement - Date: %1, Lieu: %2, Nom: %3")
            .arg(QString::fromStdString(event["date"].get<std::string>()))
            .arg(QString::fromStdString(event["lieu"].get<std::string>()))
            .arg(QString::fromStdString(event["nom"].get<std::string>())));
        model->appendRow(eventItem);

        

        // V�rifiez s'il y a des participants avant de parcourir les participants
        if (getNbParticipantsFromEvent(event) == 0) {
            QStandardItem* noParticipantsItem = new QStandardItem("Aucun participant");
            eventItem->appendRow(noParticipantsItem);
        }
        else {
            QStandardItem* participantsItem = new QStandardItem("Participants");
            eventItem->appendRow(participantsItem);
            for (const auto& participant : event["participants"]) {
                QStandardItem* participantItem = new QStandardItem(QString("Email: %1, Nom: %2, Numero: %3, VIP: %4")
                    .arg(QString::fromStdString(participant["email"].get<std::string>()))
                    .arg(QString::fromStdString(participant["nom"].get<std::string>()))
                    .arg(QString::fromStdString(participant["numero"].get<std::string>()))
                    .arg(participant["vip"].get<bool>() ? "Oui" : "Non"));
                participantsItem->appendRow(participantItem);
            }
        }

        // V�rifiez s'il y a des stands avant de parcourir les stands
        if (getNbStandsFromEvent(event) == 0) {
            QStandardItem* noStandsItem = new QStandardItem("Aucun stand");
            eventItem->appendRow(noStandsItem);


            QStandardItem* noManagersItem = new QStandardItem("Aucun manager");
            noStandsItem->appendRow(noManagersItem);
        }
        else {
            // Parcourir les stands de l'�v�nement
            QStandardItem* standsItem = new QStandardItem("Stands");
            eventItem->appendRow(standsItem);
            for (const auto& stand : event["stands"]) {
                QStandardItem* standItem = new QStandardItem(QString("Nom: %1, Numero: %2, Surface: %3")
                    .arg(QString::fromStdString(stand["nom"].get<std::string>()))
                    .arg(stand["numero"].get<int>())
                    .arg(QString::number(stand["surface"].get<double>())));
                standsItem->appendRow(standItem);
                    if (getNbManagersFromStand(stand) == 0) {
                        QStandardItem* noManagersItem = new QStandardItem("Aucun manager");
                        standItem->appendRow(noManagersItem);
                    }
                    else {
                        // Parcourir les managers du stand
                        QStandardItem* managersItem = new QStandardItem("Managers");
                        standItem->appendRow(managersItem);
                        for (const auto& manager : stand["managers"]) {
                            QStandardItem* managerItem = new QStandardItem(QString("ID: %1, Nom: %2, Numero: %3")
                                .arg(manager["id"].get<int>())
                                .arg(QString::fromStdString(manager["nom"].get<std::string>()))
                                .arg(QString::fromStdString(manager["numero"].get<std::string>())));
                            managersItem->appendRow(managerItem);
                        
                    }
                }
            }
        }
    }
    // Afficher la vue
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(treeView);
    setLayout(layout);
}