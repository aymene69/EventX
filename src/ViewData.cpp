/********************************************************************
    created:	2023-11-26
    file path:	src/ViewData.cpp
    author:		JOURNOUD Lucas
    copyright:	UNLICENSE

    purpose: W.I.P.
*********************************************************************/

#include "include/ViewData.hpp"

ViewData::ViewData(QWidget* parent) : QDialog(parent) {
    setWindowTitle("EventX - Visualisation des donnees");
    setMinimumSize(500, 300);


    // Charger les données depuis le fichier JSON
    json jsonData = preloadData();

    // Vérifiez s'il y a des événements avant d'essayer d'afficher les données
    if (getNbEvents() == 0) {
        QMessageBox::warning(this, "Avertissement", "Aucun événement à afficher.");
        return;
    }

    // Créer le modèle et la vue pour afficher les données en arbre
    QStandardItemModel* pStandardItemModelData = new QStandardItemModel(this);
    QTreeView* pTreeViewData = new QTreeView(this);
    pTreeViewData->setHeaderHidden(true);
    pTreeViewData->setModel(pStandardItemModelData);
    // Parcourir les événements
    for (const auto& event : jsonData["events"]) {
        
        QStandardItem* pStandardItemEventItem = new QStandardItem(QString("Evenement - Date: %1, Lieu: %2, Nom: %3")
            .arg(QString::fromStdString(event["date"].get<std::string>()))
            .arg(QString::fromStdString(event["lieu"].get<std::string>()))
            .arg(QString::fromStdString(event["nom"].get<std::string>())));
        pStandardItemModelData->appendRow(pStandardItemEventItem);

        
        // Vérifiez s'il y a des participants avant de parcourir les participants
        if (getNbParticipantsFromEvent(event) == 0) {
            QStandardItem* pStandardItemNoParticipants = new QStandardItem("Aucun participant");
            pStandardItemEventItem->appendRow(pStandardItemNoParticipants);
        }
        else {
            QStandardItem* pStandardItemParticipants = new QStandardItem("Participants");
            pStandardItemEventItem->appendRow(pStandardItemParticipants);
            for (const auto& participant : event["participants"]) {
                QStandardItem* pStandardItemParticipant = new QStandardItem(QString("Email: %1, Nom: %2, Numero: %3, VIP: %4")
                    .arg(QString::fromStdString(participant["email"].get<std::string>()))
                    .arg(QString::fromStdString(participant["nom"].get<std::string>()))
                    .arg(QString::fromStdString(participant["numero"].get<std::string>()))
                    .arg(participant["vip"].get<bool>() ? "Oui" : "Non"));
                pStandardItemParticipants->appendRow(pStandardItemParticipant);
            }
        }
        
        
        // Vérifiez s'il y a des stands avant de parcourir les stands
        if (getNbStandsFromEvent(event) == 0) {
            QStandardItem* pStandardItemNoStands = new QStandardItem("Aucun stand");
            pStandardItemEventItem->appendRow(pStandardItemNoStands);
            QStandardItem* pStandardItemNoManagers = new QStandardItem("Aucun manager");
            pStandardItemNoStands->appendRow(pStandardItemNoManagers);
        }
        else {
            // Parcourir les stands de l'événement
            QStandardItem* pStandardItemStands = new QStandardItem("Stands");
            pStandardItemEventItem->appendRow(pStandardItemStands);
            for (const auto& stand : event["stands"]) {
                QStandardItem* pStandardItemStand = new QStandardItem(QString("Nom: %1, Numero: %2, Surface: %3")
                    .arg(QString::fromStdString(stand["nom"].get<std::string>()))
                    .arg(stand["numero"].get<int>())
                    .arg(QString::number(stand["surface"].get<double>())));
                pStandardItemStands->appendRow(pStandardItemStand);
                    if (getNbManagersFromStand(stand) == 0) {
                        QStandardItem* pStandardItemNoManagers = new QStandardItem("Aucun manager");
                        pStandardItemStand->appendRow(pStandardItemNoManagers);
                    }
                    else {
                        // Parcourir les managers du stand
                        QStandardItem* pStandardItemManagers = new QStandardItem("Managers");
                        pStandardItemStand->appendRow(pStandardItemManagers);
                        for (const auto& manager : stand["managers"]) {
                            QStandardItem* pStandardItemManager = new QStandardItem(QString("ID: %1, Nom: %2, Numero: %3")
                                .arg(manager["id"].get<int>())
                                .arg(QString::fromStdString(manager["nom"].get<std::string>()))
                                .arg(QString::fromStdString(manager["numero"].get<std::string>())));
                            pStandardItemManagers->appendRow(pStandardItemManager);
                        
                    }
                }
            }
        }
    }
    // Afficher la vue
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(pTreeViewData);
    setLayout(layout);
    
}