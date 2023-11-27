#include "nlohmann/json.hpp"
#include <fstream>
#include <QFormLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QMessageBox>
#include <QLabel>
#include <QDateEdit>
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
    setFixedSize(250, 175);

    auto *creer = new QPushButton("Créer un événement", this);
    auto *modifier = new QPushButton("Modifier un événement", this);
    auto *supprimer = new QPushButton("Supprimer un événement", this);
    auto *retour = new QPushButton("Retour", this);
    auto *layout = new QVBoxLayout(this);

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
    auto* nomLineEdit = new QLineEdit(&creerDialog);
    auto* pDateEditDateEvent = new QDateEdit(&creerDialog);
    pDateEditDateEvent->setDate(QDate::currentDate());
    auto* lieuLineEdit = new QLineEdit(&creerDialog);

    formLayout.addRow("Nom de l'événement:", nomLineEdit);
    formLayout.addRow("Date de l'événement:", pDateEditDateEvent);
    formLayout.addRow("Lieu de l'événement:", lieuLineEdit);

    auto* creerButton = new QPushButton("Créer", &creerDialog);
    formLayout.addRow("", creerButton);

    // Connectez le bouton "Créer" à une fonction de traitement
    QObject::connect(creerButton, &QPushButton::clicked, [&]() {
    // Récupérez les valeurs saisies dans les champs
    QString nom = nomLineEdit->text();
    QString date = pDateEditDateEvent->date().toString("dd/MM/yyyy");
    QString lieu = lieuLineEdit->text();

    if (nom.isEmpty() || lieu.isEmpty()) {
        if (nom.isEmpty()) {
            QMessageBox::warning(nullptr, "Attention !", "Le nom est vide");
        }
        if (lieu.isEmpty()) {
            QMessageBox::warning(nullptr, "Attention !", "Le lieu est vide");
        }
    }
    else {
            // Créez un nouvel événement avec les valeurs récupérées
            auto* event = new Event(nom.toStdString(), date.toStdString(), lieu.toStdString());

            // Utilisez l'événement créé pour modifier le JSON
            ajouterEvent(event);

            emit dataModified();

            QMessageBox::information(nullptr, "Succès !", "L'événement a bien été créé.");
            // Fermez la boîte de dialogue de création
            creerDialog.close();
    }
        });

    creerDialog.exec();
}

void GestionEvenementDialog::modifierEvenement() {
    QDialog* pDialogModify = new QDialog(this);
    pDialogModify->setWindowTitle("Modifier un événement");
    std::vector<Event*> vecEventAll;
    json jsonData;
    std::ifstream ifstreamJsonStream(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation).toStdString() + "/data.json");
    ifstreamJsonStream >> jsonData;
    ifstreamJsonStream.close();
    const json& eventsJson = jsonData["events"];
    if (eventsJson.size() == 0) {
        QMessageBox::warning(nullptr, "Attention !", "Aucun événement n'a été trouvé.");
        delete pDialogModify;
    }
    else {
        for (json::const_iterator it = eventsJson.begin(); it != eventsJson.end(); ++it) {
            Event* pEventSingle = new Event(it.value()["nom"], it.value()["date"], it.value()["lieu"]);
            vecEventAll.push_back(pEventSingle);
        }
        QFormLayout* pFormLayoutDialog = new QFormLayout(pDialogModify);
        // Add the fields needed to modify an event
        auto* pComboBoxEvent = new QComboBox(pDialogModify);
        for (int i = 0; i < vecEventAll.size(); i++) {
            pComboBoxEvent->addItem(QString::fromStdString(vecEventAll[i]->getEventNom()));
        }
        auto* pLineEditName = new QLineEdit(pDialogModify);
        auto* pLineEditDate = new QLineEdit(pDialogModify);
        auto* pLineEditLocation = new QLineEdit(pDialogModify);
        // Connect the combobox's currentTextChanged signal
        QObject::connect(pComboBoxEvent, static_cast<void(QComboBox::*)(const QString&)>(&QComboBox::currentTextChanged), [&](const QString& _insSelectedText) {
                // Find the corresponding event in the events vector
                for (const Event* pEventWanted : vecEventAll) {
                    if (QString::fromStdString(pEventWanted->getEventNom()) == _insSelectedText) {
                        // Update input fields with the values of the selected event
                        pLineEditName->setText(_insSelectedText);
                        pLineEditDate->setText(QString::fromStdString(pEventWanted->getEventDate()));
                        pLineEditLocation->setText(QString::fromStdString(pEventWanted->getEventLieu()));
                        break;
                    }
                }
            });
        emit pComboBoxEvent->currentTextChanged(pComboBoxEvent->currentText());
        pFormLayoutDialog->addRow("Nom de l'événement:", pComboBoxEvent);
        pFormLayoutDialog->addRow("Nouveau nom de l'événement:", pLineEditName);
        pFormLayoutDialog->addRow("Nouvelle date de l'événement:", pLineEditDate);
        pFormLayoutDialog->addRow("Nouveau lieu de l'événement:", pLineEditLocation);
        auto* pPushButtonModify = new QPushButton("Modifier", pDialogModify);
        pFormLayoutDialog->addRow("", pPushButtonModify);
        // Connect the "Modify" button to a processing function
        QObject::connect(pPushButtonModify, &QPushButton::clicked, [&]() {
        // Retrieve the values entered in the fields
        int nIndex = pComboBoxEvent->currentIndex();
        QString stringName = pLineEditName->text();
        QString stringDate = pLineEditDate->text();
        QString stringLocation = pLineEditLocation->text();
        if (stringName.isEmpty() || stringLocation.isEmpty()) {
            QMessageBox::warning(nullptr, "Attention !", "Veuillez remplir tous les champs.");
        }
        else {
            // Create a new event with the retrieved values
            Event* pEventNew = new Event(stringName.toStdString(), stringDate.toStdString(), stringLocation.toStdString());

            // Use the created event to modify the JSON
            modifierEvent(pEventNew, nIndex);
            QMessageBox::information(nullptr, "Succès !", "L'événement a bien été modifié.");
            // Close the edit dialog box
            pDialogModify->close();
            delete pDialogModify;
        }
            });
        pDialogModify->exec();
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