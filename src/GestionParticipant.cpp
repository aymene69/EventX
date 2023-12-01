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
#include "include/Participant.hpp"
#include "include/Stand.hpp"
#include "include/Manager.hpp"
#include "include/FonctionsJson.hpp"
#include "include/GestionParticipant.hpp"
#include "include/FonctionsDemarrage.hpp"

using json = nlohmann::json;

GestionParticipantDialog::GestionParticipantDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("EventX - Gestion des participants");

    auto *label = new QLabel("Gestion des participants", this);
    label->setAlignment(Qt::AlignCenter);

    auto *creer = new QPushButton("Créer un participant", this);
    auto *modifier = new QPushButton("Modifier un participant", this);
    auto *supprimer = new QPushButton("Supprimer un participant", this);
    auto *retour = new QPushButton("Retour", this);
    auto *layout = new QVBoxLayout(this);

    layout->addWidget(label);
    layout->addWidget(creer);
    layout->addWidget(modifier);
    layout->addWidget(supprimer);
    layout->addWidget(retour);

    QObject::connect(creer, &QPushButton::clicked, this, &GestionParticipantDialog::creerParticipant);
    QObject::connect(modifier, &QPushButton::clicked, this, &GestionParticipantDialog::modifierParticipant);
    QObject::connect(supprimer, &QPushButton::clicked, this, &GestionParticipantDialog::supprimerParticipant);
    QObject::connect(retour, &QPushButton::clicked, this, &GestionParticipantDialog::close);
}

void GestionParticipantDialog::creerParticipant() {
    int* nbEvents = new int(0);
    json* data = new json();
    *data = preloadData();
    *nbEvents = getNbEvents();
    if (*nbEvents == 0) {
        QMessageBox::warning(nullptr, "Attention !", "Aucun événement n'a été créé, aucun participant ne peut être créé");
        return;
    } else {
        QDialog creerDialog(this);
        creerDialog.setWindowTitle("Créer un participant");

        QFormLayout formLayout(&creerDialog);

        // Ajoutez les champs nécessaires pour la création d'un participant
        auto *eventComboBox = new QComboBox(&creerDialog);
        auto *nomLineEdit = new QLineEdit(&creerDialog);
        auto *estVIPCheckBox = new QCheckBox(&creerDialog);
        auto *numLineEdit = new QLineEdit(&creerDialog);
        auto *emailLineEdit = new QLineEdit(&creerDialog);
        auto* pRegularExpressionValidatorPhoneNumber= new QRegularExpressionValidator(QRegularExpression("^[\+]?[(]?[0-9]{3}[)]?[-\s\.]?[0-9]{3}[-\s\.]?[0-9]{4,6}$"));
        numLineEdit->setValidator(pRegularExpressionValidatorPhoneNumber);
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
        formLayout.addRow("Nom du participant:", nomLineEdit);
        formLayout.addRow("Est VIP:", estVIPCheckBox);
        formLayout.addRow("Numéro de téléphone:", numLineEdit);
        formLayout.addRow("Adresse e-mail:", emailLineEdit);

        auto *creerButton = new QPushButton("Créer", &creerDialog);
        formLayout.addRow("", creerButton);

        // Connectez le bouton "Créer" à une fonction de traitement
        QObject::connect(creerButton, &QPushButton::clicked, [&]() {
            // Récupérez les valeurs saisies dans les champs

            int index = eventComboBox->currentIndex();
            QString nom = nomLineEdit->text();
            bool estVIP = estVIPCheckBox->isChecked();
            QString num = numLineEdit->text();
            QString email = emailLineEdit->text();

            if (nom.isEmpty() || num.isEmpty() || email.isEmpty()) {
                if (nom.isEmpty()) {
                    QMessageBox::warning(nullptr, "Attention !", "Le nom est vide");
                }
                if (num.isEmpty()) {
                    QMessageBox::warning(nullptr, "Attention !", "Le numéro est vide");
                }
                if (email.isEmpty()) {
                    QMessageBox::warning(nullptr, "Attention !", "L'email est vide");
                }
            } else {
                // Créez un objet Participant avec les valeurs récupérées
                Participant participant(nom.toStdString(), estVIP, num.toStdString(), email.toStdString());
                // Ajoutez le participant à la base de données
                ajouterParticip(&participant, index);
                emit dataModified();
                QMessageBox::information(nullptr, "Succès !", "Le participant a bien été créé");
                creerDialog.close();
            }
        });
        creerDialog.exec();
    }
}

void GestionParticipantDialog::modifierParticipant() {
    QDialog modifierDialog(this);
    modifierDialog.setWindowTitle("Modifier un participant");

    std::vector<Participant> participants;
    json j;
    j = preloadData();
    int* nbParticipants = new int(0);
    for (const auto &eventJson : j["events"]) {
        if (eventJson.find("participants") != eventJson.end()) {
            const auto &participantsJson = eventJson["participants"];
            *nbParticipants += participantsJson.size();
        }
    }
    const json &eventsJson = j["events"];
    if (*nbParticipants == 0) {
        QMessageBox::warning(nullptr, "Attention !", "Aucun participant n'a été trouvé.");
        return; // Ajout d'un return pour éviter l'exécution du reste de la fonction
    } else {
        // Ajout d'un QFormLayout pour les champs de modification
        QFormLayout formLayout(&modifierDialog);
        // Ajoutez les champs nécessaires pour la modification d'un participant
        auto *eventComboBox = new QComboBox(&modifierDialog);
        participantComboBox = new QComboBox(&modifierDialog); // Créez la QComboBox ici
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
        QObject::connect(eventComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &GestionParticipantDialog::onEventComboBoxChanged);
        auto *nomLineEdit = new QLineEdit(&modifierDialog);
        auto *estVIPCheckBox = new QCheckBox(&modifierDialog);
        auto *numLineEdit = new QLineEdit(&modifierDialog);
        auto *emailLineEdit = new QLineEdit(&modifierDialog);
        auto* pRegularExpressionValidatorPhoneNumber = new QRegularExpressionValidator(QRegularExpression("^[\+]?[(]?[0-9]{3}[)]?[-\s\.]?[0-9]{3}[-\s\.]?[0-9]{4,6}$"));
        numLineEdit->setValidator(pRegularExpressionValidatorPhoneNumber);
        formLayout.addRow("Événement:", eventComboBox);
        formLayout.addRow("Participant:", participantComboBox);
        formLayout.addRow("Nom du participant:", nomLineEdit);
        formLayout.addRow("Est VIP:", estVIPCheckBox);
        formLayout.addRow("Numéro de téléphone:", numLineEdit);
        formLayout.addRow("Adresse e-mail:", emailLineEdit);
        auto* labelNoParticipant = new QLabel("L'évènement séléctionné n'as pas de participant. \r\nVeuillez lui créer un participant ou bien séléctionnez un autre évènement.", &modifierDialog);
        formLayout.addRow("", labelNoParticipant);
        auto* modifierButton = new QPushButton("Modifier", &modifierDialog);
        formLayout.addRow("", modifierButton);
        QObject::connect(participantComboBox, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), [&]{
            int eventIndex = eventComboBox->currentIndex();
            int participantIndex = participantComboBox->currentIndex();
            const json& selectedEvent = eventsJson[eventIndex]; //Get the actual event
            if(getNbParticipantsFromEvent(selectedEvent)!=0) {
                const auto& participantsJson = selectedEvent["participants"]; //Get all participants of the event
                const json& participantJson = participantsJson[participantIndex]; //Get the actual participant
                nomLineEdit->setText(QString::fromStdString(participantJson["nom"]));
                numLineEdit->setText(QString::fromStdString(participantJson["numero"]));
                emailLineEdit->setText(QString::fromStdString(participantJson["email"]));
                estVIPCheckBox->setChecked(participantJson["vip"]);
            }
            else {
                nomLineEdit->setText("");
                numLineEdit->setText("");
                emailLineEdit->setText("");
                estVIPCheckBox->setChecked(false);
            }
        });
        // Appeler explicitement onEventComboBoxChanged pour charger les participants initialement
        onEventComboBoxChanged(0);
        // Connectez le bouton "Modifier" à une fonction de traitement
        QObject::connect(modifierButton, &QPushButton::clicked, [&]() {
            // Récupérez les valeurs sélectionnées
            int eventIndex = eventComboBox->currentIndex();
            int participantIndex = participantComboBox->currentIndex();
            const json &selectedEvent = eventsJson[eventIndex];
            if (selectedEvent.find("participants") != selectedEvent.end()) {
                const auto &participantsJson = selectedEvent["participants"];
                if (participantIndex < participantsJson.size()) {
                    const json &participantJson = participantsJson[participantIndex];
                    QString nom = nomLineEdit->text();
                    bool estVIP = estVIPCheckBox->isChecked();
                    QString num = numLineEdit->text();
                    QString email = emailLineEdit->text();
                    if (nom.isEmpty() || num.isEmpty() || email.isEmpty()) {
                        if (nom.isEmpty()) {
                            QMessageBox::warning(nullptr, "Attention !", "Le nom est vide");
                        }
                        if (num.isEmpty()) {
                            QMessageBox::warning(nullptr, "Attention !", "Le numéro est vide");
                        }
                        if (email.isEmpty()) {
                            QMessageBox::warning(nullptr, "Attention !", "L'email est vide");
                        }
                    } else {
                        // Créez un objet Participant avec les valeurs récupérées
                        Participant participant(nom.toStdString(), estVIP, num.toStdString(), email.toStdString());
                        // Modifiez le participant dans la base de données
                        modifierParticip(&participant, eventIndex, participantIndex);
                        QMessageBox::information(nullptr, "Succès !", "Le participant a bien été modifié.");
                        modifierDialog.close();
                        return;
                    }
                    QMessageBox::information(nullptr, "Succès !", "Le participant a bien été modifié.");
                    modifierDialog.close();
                    return;
                }
            }
        });
        modifierDialog.exec();
    }
}

void GestionParticipantDialog::supprimerParticipant() {
    QDialog supprimerDialog(this);
    supprimerDialog.setWindowTitle("Supprimer un participant");

    std::vector<Participant> participants;
    json j;
    j = preloadData();
    int* nbParticipants = new int(0);
    for (const auto &eventJson : j["events"]) {
        if (eventJson.find("participants") != eventJson.end()) {
            const auto &participantsJson = eventJson["participants"];
            *nbParticipants += participantsJson.size();
        }
    }
    const json &eventsJson = j["events"];
    if (*nbParticipants == 0) {
        QMessageBox::warning(nullptr, "Attention !", "Aucun participant n'a été trouvé.");
        return; // Ajout d'un return pour éviter l'exécution du reste de la fonction
    } else {
        // Ajout d'un QFormLayout pour les champs de suppression
        QFormLayout formLayout(&supprimerDialog);

        // Ajoutez les champs nécessaires pour la suppression d'un participant
        auto *eventComboBox = new QComboBox(&supprimerDialog);
        participantComboBox = new QComboBox(&supprimerDialog); // Créez la QComboBox ici

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
                         this, &GestionParticipantDialog::onEventComboBoxChanged);

        formLayout.addRow("Événement:", eventComboBox);
        formLayout.addRow("Participant:", participantComboBox);
        auto* labelNoParticipant = new QLabel("L'évènement séléctionné n'as pas de participant. \r\nVeuillez séléctionnez un autre évènement.", &supprimerDialog);
        formLayout.addRow("", labelNoParticipant);
        auto* supprimerButton = new QPushButton("Supprimer", &supprimerDialog);
        formLayout.addRow("", supprimerButton);
        // Appeler explicitement onEventComboBoxChanged pour charger les participants initialement
        onEventComboBoxChanged(0);



        // Connectez le bouton "Supprimer" à une fonction de traitement
        QObject::connect(supprimerButton, &QPushButton::clicked, [&]() {
            // Récupérez les valeurs sélectionnées
            int eventIndex = eventComboBox->currentIndex();
            int participantIndex = participantComboBox->currentIndex();

            const json &selectedEvent = eventsJson[eventIndex];
            if (selectedEvent.find("participants") != selectedEvent.end()) {
                const auto &participantsJson = selectedEvent["participants"];
                if (participantIndex < participantsJson.size()) {
                    const json &participantJson = participantsJson[participantIndex];
                    supprimerParticip(eventIndex, participantIndex);
                    emit dataModified();
                    QMessageBox::information(nullptr, "Succès !", "Le participant a bien été supprimé.");
                    supprimerDialog.close();
                    return;
                }
            }
        });

        supprimerDialog.exec();
    }
}




void GestionParticipantDialog::onEventComboBoxChanged(int index) {


    // Effacez la QComboBox des participants
    participantComboBox->clear();

    // Chargez les participants liés à l'événement sélectionné
    json data = preloadData(); // Assurez-vous de récupérer vos données de manière appropriée
    const auto &selectedEvent = data["events"][index];
    QFormLayout* formLayout = qobject_cast<QFormLayout*>(participantComboBox->parentWidget()->layout());
    QDialog* dialog = qobject_cast<QDialog*>(formLayout->parent());

    if (selectedEvent.find("participants") != selectedEvent.end()) {
        if(formLayout->rowCount()==8) { //Modify participant
            formLayout->setRowVisible(1, true);
            formLayout->setRowVisible(2, true);
            formLayout->setRowVisible(3, true);
            formLayout->setRowVisible(4, true);
            formLayout->setRowVisible(5, true);
            formLayout->setRowVisible(6, false);
            formLayout->setRowVisible(7, true);
            dialog->setFixedSize(280, 208);
        }
         else if (formLayout->rowCount() == 4) { //Delete participant
            formLayout->setRowVisible(1, true);
            formLayout->setRowVisible(2, false);
            formLayout->setRowVisible(3, true);
            dialog->setFixedSize(200, 102);
        }
        
        const auto &participants = selectedEvent["participants"];
        for (const auto &participant : participants) {
            participantComboBox->addItem(QString::fromStdString(participant["nom"])); // Ajoutez le participant à la QComboBox
        }
    }
    else {
        if (formLayout->rowCount() == 8) {//Modify participant

            formLayout->setRowVisible(1, false);
            formLayout->setRowVisible(2, false);
            formLayout->setRowVisible(3, false);
            formLayout->setRowVisible(4, false);
            formLayout->setRowVisible(5, false);
            formLayout->setRowVisible(6, true);
            formLayout->setRowVisible(7, false);
            dialog->setFixedSize(480, 208);
        }
        else if (formLayout->rowCount() == 4) { //Delete participant
            formLayout->setRowVisible(1, false);
            formLayout->setRowVisible(2, true);
            formLayout->setRowVisible(3, false);
            dialog->setFixedSize(281, 102);
        }

    }

}