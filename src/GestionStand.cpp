/********************************************************************
    created:	2023-11-24
    file path:	src/GestionStand.cpp
    author:		W.I.P.
    copyright:	UNLICENSE

    purpose: W.I.P.
*********************************************************************/

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
#include "include/Event.hpp" // Inclure les fichiers d'en-tête nécessaires
#include "include/Stand.hpp"
#include "include/Manager.hpp"
#include "include/FonctionsJson.hpp"
#include "include/GestionStand.hpp"
#include "include/FonctionsDemarrage.hpp"

using json = nlohmann::json;

GestionStandDialog::GestionStandDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("EventX - Gestion des stands");

    auto *label = new QLabel("Gestion des stands", this);
    label->setAlignment(Qt::AlignCenter);

    auto *creer = new QPushButton("Créer un stand", this);
    auto *modifier = new QPushButton("Modifier un stand", this);
    auto *supprimer = new QPushButton("Supprimer un stand", this);
    auto *retour = new QPushButton("Retour", this);
    auto *layout = new QVBoxLayout(this);

    layout->addWidget(label);
    layout->addWidget(creer);
    layout->addWidget(modifier);
    layout->addWidget(supprimer);
    layout->addWidget(retour);

    QObject::connect(creer, &QPushButton::clicked, this, &GestionStandDialog::creerStand);
    QObject::connect(modifier, &QPushButton::clicked, this, &GestionStandDialog::modifierStand);
    QObject::connect(supprimer, &QPushButton::clicked, this, &GestionStandDialog::supprimerStand);
    QObject::connect(retour, &QPushButton::clicked, this, &GestionStandDialog::close);
}

void GestionStandDialog::creerStand() {
    int* nbEvents = new int(0);
    json* data = new json();
    *data = preloadData();
    *nbEvents = getNbEvents();
    if (*nbEvents == 0) {
        QMessageBox::warning(nullptr, "Attention !", "Aucun événement n'a été créé, aucun stand ne peut être créé");
        return;
    } else {
        QDialog creerDialog(this);
        creerDialog.setWindowTitle("Créer un stand");

        QFormLayout formLayout(&creerDialog);

        // Ajoutez les champs nécessaires pour la création d'un participant
        auto *eventComboBox = new QComboBox(&creerDialog);
        auto *nomLineEdit = new QLineEdit(&creerDialog);
        auto *surfaceLineEdit = new QLineEdit(&creerDialog);

        std::vector<Event> events;
        json j;
        std::ifstream i(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation).toStdString() + "/data.json");
        i >> j;
        i.close();
        const json &eventsJson = j["events"];
        for (const auto &eventJson: eventsJson) {
            Event event(eventJson["nom"], eventJson["date"], eventJson["lieu"]);
            events.push_back(event);
        }
        for (const auto &event: events) {
            eventComboBox->addItem(QString::fromStdString(event.getEventNom()));
        }

        formLayout.addRow("Événement:", eventComboBox);
        formLayout.addRow("Nom du stand:", nomLineEdit);
        formLayout.addRow("Surface du stand:", surfaceLineEdit);

        auto *creerButton = new QPushButton("Créer", &creerDialog);
        formLayout.addRow("", creerButton);

        // Connectez le bouton "Créer" à une fonction de traitement
        QObject::connect(creerButton, &QPushButton::clicked, [&]() {
            // Récupérez les valeurs saisies dans les champs

            int index = eventComboBox->currentIndex();
            QString nom = nomLineEdit->text();
            QString surface = surfaceLineEdit->text();

            if (nom.isEmpty() || surface.isEmpty()) {
                if (nom.isEmpty()) {
                    QMessageBox::warning(nullptr, "Attention !", "Le nom est vide");
                }
                if (surface.isEmpty()) {
                    QMessageBox::warning(nullptr, "Attention !", "La surface est vide");
                }
            } else {
                // Créez un objet Stand avec les valeurs récupérées
                Stand stand(nom.toStdString(), surface.toInt());
                // Ajoutez le stand à la base de données
                ajouterStand(&stand, index);
                emit dataModified();
                QMessageBox::information(nullptr, "Succès !", "Le stand a bien été créé");
                creerDialog.close();
            }
        });
        creerDialog.exec();
    }
}

void GestionStandDialog::modifierStand() {
    QDialog modifierDialog(this);
    modifierDialog.setWindowTitle("Modifier un stand");

    std::vector<Stand> stands;
    json j;
    j = preloadData();
    const json &eventsJson = j["events"];
    if (getNbStands() == 0) {
        QMessageBox::warning(nullptr, "Attention !", "Aucun stand n'a été trouvé.");
        return; // Ajout d'un return pour éviter l'exécution du reste de la fonction
    } else {
        // Ajout d'un QFormLayout pour les champs de modification
        QFormLayout formLayout(&modifierDialog);

        // Ajoutez les champs nécessaires pour la modification d'un participant
        auto *eventComboBox = new QComboBox(&modifierDialog);
        standComboBox = new QComboBox(&modifierDialog); // Créez la QComboBox ici

        std::vector<Event> events;
        const json &eventsJson = j["events"];
        for (const auto &eventJson: eventsJson) {
            Event event(eventJson["nom"], eventJson["date"], eventJson["lieu"]);
            events.push_back(event);
        }
        for (const auto &event: events) {
            eventComboBox->addItem(QString::fromStdString(event.getEventNom()));
        }

        // Connectez le changement de l'événement à la mise à jour des participants
        QObject::connect(eventComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
                         this, &GestionStandDialog::onEventComboBoxChanged);

        auto *nomLineEdit = new QLineEdit(&modifierDialog);
        auto *surfaceLineEdit = new QLineEdit(&modifierDialog);


        formLayout.addRow("Événement:", eventComboBox);
        formLayout.addRow("Stand:", standComboBox);
        formLayout.addRow("Nom du stand:", nomLineEdit);

        // Appeler explicitement onEventComboBoxChanged pour charger les participants initialement
        onEventComboBoxChanged(0);

        auto *modifierButton = new QPushButton("Modifier", &modifierDialog);
        formLayout.addRow("", modifierButton);

        // Connectez le bouton "Modifier" à une fonction de traitement
        QObject::connect(modifierButton, &QPushButton::clicked, [&]() {
            // Récupérez les valeurs sélectionnées
            int eventIndex = eventComboBox->currentIndex();
            int standIndex = standComboBox->currentIndex();

            const json &selectedEvent = eventsJson[eventIndex];
            if (selectedEvent.find("stands") != selectedEvent.end()) {
                const auto &standsJson = selectedEvent["stands"];
                if (standIndex < standsJson.size()) {
                    const json &standJson = standsJson[standIndex];
                    QString nom = nomLineEdit->text();
                    QString surface = surfaceLineEdit->text();

                    if (nom.isEmpty() || surface.isEmpty()) {
                        if (nom.isEmpty()) {
                            QMessageBox::warning(nullptr, "Attention !", "Le nom est vide");
                        }
                        if (surface.isEmpty()) {
                            QMessageBox::warning(nullptr, "Attention !", "La surface est vide");
                        }
                    } else {
                        // Créez un objet Stand avec les valeurs récupérées
                        Stand stand(nom.toStdString(), surface.toInt());
                        // Modifiez le stand dans la base de données
                        modifierStandd(&stand, eventIndex, standIndex);

                        QMessageBox::information(nullptr, "Succès !", "Le stand a bien été modifié.");
                        modifierDialog.close();
                        return;
                    }

                    QMessageBox::information(nullptr, "Succès !", "Le stand a bien été modifié.");
                    modifierDialog.close();
                    return;
                }
            }
        });

        modifierDialog.exec();
    }
}

void GestionStandDialog::supprimerStand() {
    QDialog supprimerDialog(this);
    supprimerDialog.setWindowTitle("Supprimer un stand");

    std::vector<Stand> stands;
    json j;
    j = preloadData();
    const json &eventsJson = j["events"];
    if (getNbStands() == 0) {
        QMessageBox::warning(nullptr, "Attention !", "Aucun stand n'a été trouvé.");
        return; // Ajout d'un return pour éviter l'exécution du reste de la fonction
    } else {
        // Ajout d'un QFormLayout pour les champs de suppression
        QFormLayout formLayout(&supprimerDialog);

        // Ajoutez les champs nécessaires pour la suppression d'un participant
        auto *eventComboBox = new QComboBox(&supprimerDialog);
        standComboBox = new QComboBox(&supprimerDialog); // Créez la QComboBox ici

        std::vector<Event> events;
        const json &eventsJson = j["events"];
        for (const auto &eventJson: eventsJson) {
            Event event(eventJson["nom"], eventJson["date"], eventJson["lieu"]);
            events.push_back(event);
        }
        for (const auto &event: events) {
            eventComboBox->addItem(QString::fromStdString(event.getEventNom()));
        }

        // Connectez le changement de l'événement à la mise à jour des participants
        QObject::connect(eventComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
                         this, &GestionStandDialog::onEventComboBoxChanged);

        formLayout.addRow("Événement:", eventComboBox);
        formLayout.addRow("Stand:", standComboBox);

        // Appeler explicitement onEventComboBoxChanged pour charger les participants initialement
        onEventComboBoxChanged(0);

        auto *supprimerButton = new QPushButton("Supprimer", &supprimerDialog);
        formLayout.addRow("", supprimerButton);

        // Connectez le bouton "Supprimer" à une fonction de traitement
        QObject::connect(supprimerButton, &QPushButton::clicked, [&]() {
            // Récupérez les valeurs sélectionnées
            int eventIndex = eventComboBox->currentIndex();
            int standIndex = standComboBox->currentIndex();

            const json &selectedEvent = eventsJson[eventIndex];
            if (selectedEvent.find("stands") != selectedEvent.end()) {
                const auto &standsJson = selectedEvent["stands"];
                if (standIndex < standsJson.size()) {
                    const json &standJson = standsJson[standIndex];
                    supprimerStandd(eventIndex, standIndex);
                    emit dataModified();
                    QMessageBox::information(nullptr, "Succès !", "Le stand a bien été supprimé.");
                    supprimerDialog.close();
                    return;
                }
            }
        });

        supprimerDialog.exec();
    }
}


void GestionStandDialog::onEventComboBoxChanged(int index) {
    // Effacez la QComboBox des participants
    standComboBox->clear();

    // Chargez les participants liés à l'événement sélectionné
    json data = preloadData(); // Assurez-vous de récupérer vos données de manière appropriée
    const auto &selectedEvent = data["events"][index];

    if (selectedEvent.find("stands") != selectedEvent.end()) {
        const auto &stands = selectedEvent["stands"];
        for (const auto &stand : stands) {
            standComboBox->addItem(QString::fromStdString(stand["nom"])); // Ajoutez le participant à la QComboBox
        }
    }

}