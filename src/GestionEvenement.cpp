#include "nlohmann/json.hpp"
#include <fstream>
#include <QFormLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QMessageBox>
#include <QLabel>
#include <QStandardPaths>
#include "include/Event.hpp" // Inclure les fichiers d'en-tête nécessaires
#include "include/Participant.hpp"
#include "include/Stand.hpp"
#include "include/Manager.hpp"
#include "include/FonctionsJson.hpp"
#include "include/GestionEvenement.hpp"

using json = nlohmann::json;

GestionEvenementDialog::GestionEvenementDialog(QWidget *parent): QDialog(parent) {
    setWindowTitle("EventX - Gestion des événements");

    auto *label = new QLabel("Gestion des événements", this);
    label->setAlignment(Qt::AlignCenter);

    auto *creer = new QPushButton("Créer un événement", this);
    auto *modifier = new QPushButton("Modifier un événement", this);
    auto *supprimer = new QPushButton("Supprimer un événement", this);
    auto *retour = new QPushButton("Retour", this);
    auto *layout = new QVBoxLayout(this);

    layout->addWidget(label);
    layout->addWidget(creer);
    layout->addWidget(modifier);
    layout->addWidget(supprimer);
    layout->addWidget(retour);

    QObject::connect(creer, &QPushButton::clicked, this, &GestionEvenementDialog::creerEvenement);
    QObject::connect(modifier, &QPushButton::clicked, this, &GestionEvenementDialog::modifierEvenement);
    QObject::connect(supprimer, &QPushButton::clicked, this, &GestionEvenementDialog::supprimerEvenement);
    QObject::connect(retour, &QPushButton::clicked, this, &GestionEvenementDialog::close);
}

void GestionEvenementDialog::creerEvenement() {
    QDialog creerDialog(this);
    creerDialog.setWindowTitle("Créer un événement");

    QFormLayout formLayout(&creerDialog);

    // Ajoutez les champs nécessaires pour la création d'un événement
    auto *nomLineEdit = new QLineEdit(&creerDialog);
    auto *dateLineEdit = new QLineEdit(&creerDialog);
    auto *lieuLineEdit = new QLineEdit(&creerDialog);

    formLayout.addRow("Nom de l'événement:", nomLineEdit);
    formLayout.addRow("Date de l'événement:", dateLineEdit);
    formLayout.addRow("Lieu de l'événement:", lieuLineEdit);

    auto *creerButton = new QPushButton("Créer", &creerDialog);
    formLayout.addRow("", creerButton);

    // Connectez le bouton "Créer" à une fonction de traitement
    QObject::connect(creerButton, &QPushButton::clicked, [&]() {
        // Récupérez les valeurs saisies dans les champs
        QString nom = nomLineEdit->text();
        QString date = dateLineEdit->text();
        QString lieu = lieuLineEdit->text();

        if (nom.isEmpty() || date.isEmpty() || lieu.isEmpty()) {
            if (nom.isEmpty()) {
                QMessageBox::warning(nullptr, "Attention !", "Le nom est vide");
            }
            if (date.isEmpty()) {
                QMessageBox::warning(nullptr, "Attention !", "La date est vide");
            }
            if (lieu.isEmpty()) {
                QMessageBox::warning(nullptr, "Attention !", "Le lieu est vide");
            }
        } else {
            if (!verifDate(date.toStdString())) {
                QMessageBox::warning(nullptr, "Attention !", "La date n'est pas au bon format (jj/mm/aaaa)");
                return;
            }
            else {
                // Créez un nouvel événement avec les valeurs récupérées
                auto *event = new Event(nom.toStdString(), date.toStdString(), lieu.toStdString());

                // Utilisez l'événement créé pour modifier le JSON
                ajouterEvent(event);

                emit dataModified();

                QMessageBox::information(nullptr, "Succès !", "L'événement a bien été créé.");
                // Fermez la boîte de dialogue de création
                creerDialog.close();
            }
        }
    });
    creerDialog.exec();
}


void GestionEvenementDialog::modifierEvenement() {
    QDialog modifierDialog(this);
    modifierDialog.setWindowTitle("Modifier un événement");

    std::vector<Event> events;
    json j;
    std::ifstream i(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation).toStdString() + "/data.json");
    i >> j;
    i.close();
    const json &eventsJson = j["events"];
    if (eventsJson.size() == 0) {
        QMessageBox::warning(nullptr, "Attention !", "Aucun événement n'a été trouvé.");
    } else {
        for (json::const_iterator it = eventsJson.begin(); it != eventsJson.end(); ++it) {
            Event event(it.value()["nom"], it.value()["date"], it.value()["lieu"]);
            events.push_back(event);
        }

        QFormLayout formLayout(&modifierDialog);

        // Ajoutez les champs nécessaires pour la modification d'un événement
        auto *comboBox = new QComboBox(&modifierDialog);
        for (int i = 0; i < events.size(); i++) {
            comboBox->addItem(QString::fromStdString(events[i].getEventNom()));
        }

        auto *nomLineEdit = new QLineEdit(&modifierDialog);
        auto *dateLineEdit = new QLineEdit(&modifierDialog);
        auto *lieuLineEdit = new QLineEdit(&modifierDialog);

        formLayout.addRow("Nom de l'événement:", comboBox);
        formLayout.addRow("Nouveau nom de l'événement:", nomLineEdit);
        formLayout.addRow("Nouvelle date de l'événement:", dateLineEdit);
        formLayout.addRow("Nouveau lieu de l'événement:", lieuLineEdit);

        auto *modifierButton = new QPushButton("Modifier", &modifierDialog);
        formLayout.addRow("", modifierButton);

        // Connectez le bouton "Modifier" à une fonction de traitement
        QObject::connect(modifierButton, &QPushButton::clicked, [&]() {
            // Récupérez les valeurs saisies dans les champs
            int index = comboBox->currentIndex();
            QString nom = nomLineEdit->text();
            QString date = dateLineEdit->text();
            QString lieu = lieuLineEdit->text();

            if (nom.isEmpty() || date.isEmpty() || lieu.isEmpty()) {
                QMessageBox::warning(nullptr, "Attention !", "Veuillez remplir tous les champs.");
            } else {
                if (!verifDate(date.toStdString())) {
                    QMessageBox::warning(nullptr, "Attention !", "La date n'est pas au bon format (jj/mm/aaaa)");
                    return;
                } else {
                    // Créez un nouvel événement avec les valeurs récupérées
                    auto *event = new Event(nom.toStdString(), date.toStdString(), lieu.toStdString());

                    // Utilisez l'événement créé pour modifier le JSON
                    modifierEvent(event, index);
                    QMessageBox::information(nullptr, "Succès !", "L'événement a bien été modifié.");
                    // Fermez la boîte de dialogue de modification
                    modifierDialog.close();
                }
            }
        });
        modifierDialog.exec();
    }
}


void GestionEvenementDialog::supprimerEvenement() {
    QDialog supprimerDialog(this);
    supprimerDialog.setWindowTitle("Supprimer un événement");

    std::vector<Event> events;
    json j;
    std::ifstream i(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation).toStdString() + "/data.json");
    i >> j;
    i.close();
    const json& eventsJson = j["events"];
    if (eventsJson.size() == 0) {
        QMessageBox::warning(nullptr, "Attention !", "Aucun événement n'a été trouvé.");
    }
    else {
        for (json::const_iterator it = eventsJson.begin(); it != eventsJson.end(); ++it) {
            Event event(it.value()["nom"], it.value()["date"], it.value()["lieu"]);
            events.push_back(event);
        }

        QFormLayout formLayout(&supprimerDialog);

        // Ajoutez les champs nécessaires pour la suppression d'un événement
        auto *comboBox = new QComboBox(&supprimerDialog);
        for (int i = 0; i < events.size(); i++) {
            comboBox->addItem(QString::fromStdString(events[i].getEventNom()));
        }

        formLayout.addRow("Nom de l'événement:", comboBox);

        auto *supprimerButton = new QPushButton("Supprimer", &supprimerDialog);
        formLayout.addRow("", supprimerButton);

        // Connectez le bouton "Supprimer" à une fonction de traitement
        QObject::connect(supprimerButton, &QPushButton::clicked, [&]() {
            // Récupérez les valeurs saisies dans les champs
            int index = comboBox->currentIndex();

            // Utilisez l'objet Event existant pour modifier le JSON
            supprimerEvent(&events[index], index);
            emit dataModified();
            QMessageBox::information(nullptr, "Succès !", "L'événement a bien été supprimé.");
            // Fermez la boîte de dialogue de suppression
            supprimerDialog.close();
        });
        supprimerDialog.exec();
    }

}