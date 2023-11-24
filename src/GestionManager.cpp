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
#include "include/GestionManager.hpp"
#include "include/FonctionsDemarrage.hpp"

using json = nlohmann::json;

GestionManagerDialog::GestionManagerDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("EventX - Gestion des managers");

    auto *label = new QLabel("Gestion des managers", this);
    label->setAlignment(Qt::AlignCenter);

    auto *creer = new QPushButton("Créer un manager", this);
    auto *modifier = new QPushButton("Modifier un manager", this);
    auto *supprimer = new QPushButton("Supprimer un manager", this);
    auto *retour = new QPushButton("Retour", this);
    auto *layout = new QVBoxLayout(this);

    layout->addWidget(label);
    layout->addWidget(creer);
    layout->addWidget(modifier);
    layout->addWidget(supprimer);
    layout->addWidget(retour);

    QObject::connect(creer, &QPushButton::clicked, this, &GestionManagerDialog::creerManager);
    QObject::connect(modifier, &QPushButton::clicked, this, &GestionManagerDialog::modifierManager);
    QObject::connect(supprimer, &QPushButton::clicked, this, &GestionManagerDialog::supprimerManager);
    QObject::connect(retour, &QPushButton::clicked, this, &GestionManagerDialog::close);
}

void GestionManagerDialog::creerManager() {
    int* nbEvents = new int(0);
    int* nbStands = new int(0);
    json* data = new json();
    *data = preloadData();
    *nbEvents = getNbEvents();
    *nbStands = getNbStands();
    if (*nbEvents == 0) {
        QMessageBox::warning(nullptr, "Attention !", "Aucun événement n'a été créé, aucun manager ne peut être créé");
        return;
    } else if (*nbStands == 0) {
        QMessageBox::warning(nullptr, "Attention !", "Aucun stand n'a été créé, aucun manager ne peut être créé");
        return;
    } else {
        QDialog creerDialog(this);
        creerDialog.setWindowTitle("Créer un Manager");

        QFormLayout formLayout(&creerDialog);

        // Ajoutez les champs nécessaires pour la création d'un participant
        eventComboBox = new QComboBox(&creerDialog);
        standComboBox = new QComboBox(&creerDialog);
        auto *nomLineEdit = new QLineEdit(&creerDialog);
        auto *idLineEdit = new QLineEdit(&creerDialog);
        auto *numLineEdit = new QLineEdit(&creerDialog);

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

        // on fais la combobox des stands selon l'événement choisi
        QObject::connect(eventComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
                         this, &GestionManagerDialog::onEventComboBoxChanged);

        formLayout.addRow("Événement:", eventComboBox);
        formLayout.addRow("Stand:", standComboBox);
        formLayout.addRow("Nom du manager:", nomLineEdit);
        formLayout.addRow("ID du manager:", idLineEdit);
        formLayout.addRow("Numéro de téléphone du manager:", numLineEdit);

        // Appeler explicitement onEventComboBoxChanged pour charger les participants initialement
        onEventComboBoxChanged(0);

        auto *creerButton = new QPushButton("Créer", &creerDialog);
        formLayout.addRow("", creerButton);

        // Connectez le bouton "Créer" à une fonction de traitement
        QObject::connect(creerButton, &QPushButton::clicked, [&]() {
            // Récupérez les valeurs sélectionnées
            int eventIndex = eventComboBox->currentIndex();
            int standIndex = standComboBox->currentIndex();
            const json &selectedEvent = eventsJson[eventIndex];
            if (selectedEvent.find("stands") != selectedEvent.end()) {
                const auto &standsJson = selectedEvent["stands"];
                if (standIndex < standsJson.size()) {
                    const json &standJson = standsJson[standIndex];
                    QString nom = nomLineEdit->text();
                    QString num = numLineEdit->text();
                    if (nom.isEmpty() || num.isEmpty()) {
                        if (nom.isEmpty()) {
                            QMessageBox::warning(nullptr, "Attention !", "Le nom est vide");
                        }
                        if (num.isEmpty()) {
                            QMessageBox::warning(nullptr, "Attention !", "Le numéro est vide");
                        }
                    } else {
                        // Créez un objet Manager avec les valeurs récupérées
                        Manager manager(nom.toStdString(), 0, num.toStdString());
                        // Ajoutez le manager dans la base de données
                        ajouterManager(&manager, eventIndex, standIndex);

                        emit dataModified();

                        QMessageBox::information(nullptr, "Succès !", "Le manager a bien été créé.");
                        creerDialog.close();
                        return;
                    }
                }
            }
        });



        creerDialog.exec();
    }
}

void GestionManagerDialog::modifierManager() {
    QDialog modifierDialog(this);
    modifierDialog.setWindowTitle("Modifier un manager");

    std::vector<Stand> stands;
    json j;
    j = preloadData();
    const json &eventsJson = j["events"];
    if (getNbStands() == 0) {
        QMessageBox::warning(nullptr, "Attention !", "Aucun manager n'a été trouvé.");
        return; // Ajout d'un return pour éviter l'exécution du reste de la fonction
    } else {
        // Ajout d'un QFormLayout pour les champs de modification
        QFormLayout formLayout(&modifierDialog);

        // Ajoutez les champs nécessaires pour la modification d'un participant
        eventComboBox = new QComboBox(&modifierDialog);
        standComboBox = new QComboBox(&modifierDialog); // Créez la QComboBox ici
        managComboBox = new QComboBox(&modifierDialog);

        std::vector<Event> events;
        for (const auto &eventJson: eventsJson) {
            Event event(eventJson["nom"], eventJson["date"], eventJson["lieu"]);
            events.push_back(event);
        }
        for (const auto &event: events) {
            eventComboBox->addItem(QString::fromStdString(event.getEventNom()));
        }

        // Connectez le changement de l'événement à la mise à jour des participants
        QObject::connect(eventComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
                         this, &GestionManagerDialog::onEventComboBoxChanged);

        QObject::connect(standComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
                            this, &GestionManagerDialog::onStandComboBoxChanged);

        QLineEdit *nomLineEdit = new QLineEdit(&modifierDialog);
        QLineEdit *numLineEdit = new QLineEdit(&modifierDialog);

        formLayout.addRow("Événement:", eventComboBox);
        formLayout.addRow("Stand:", standComboBox);
        formLayout.addRow("Manager:", managComboBox);
        formLayout.addRow("Nouveau nom du manager:", nomLineEdit);
        formLayout.addRow("Nouveau numéro de téléphone du manager:", numLineEdit);

        // Appeler explicitement onEventComboBoxChanged pour charger les participants initialement
        onEventComboBoxChanged(0);
        onStandComboBoxChanged(0);

        auto *modifierButton = new QPushButton("Modifier", &modifierDialog);
        formLayout.addRow("", modifierButton);

        // Connectez le bouton "Modifier" à une fonction de traitement
        QObject::connect(modifierButton, &QPushButton::clicked, [&]() {
            // Récupérez les valeurs sélectionnées
            int eventIndex = eventComboBox->currentIndex();
            int standIndex = standComboBox->currentIndex();
            int managerIndex = managComboBox->currentIndex();

            const json &selectedEvent = eventsJson[eventIndex];
            if (selectedEvent.find("stands") != selectedEvent.end()) {
                const auto &standsJson = selectedEvent["stands"];
                if (standIndex < standsJson.size()) {
                    const json &standJson = standsJson[standIndex];
                    QString nom = nomLineEdit->text();
                    QString num = numLineEdit->text();
                    if (nom.isEmpty() || num.isEmpty()) {
                        if (nom.isEmpty()) {
                            QMessageBox::warning(nullptr, "Attention !", "Le nom est vide");
                        }
                        if (num.isEmpty()) {
                            QMessageBox::warning(nullptr, "Attention !", "Le numéro est vide");
                        }
                    } else {
                        // Créez un objet Manager avec les valeurs récupérées
                        Manager manager(nom.toStdString(), 0, num.toStdString());
                        // Modifiez le stand dans la base de données
                        modifierManag(&manager, eventIndex, managerIndex, standIndex);

                        QMessageBox::information(nullptr, "Succès !", "Le manager a bien été modifié.");
                        modifierDialog.close();
                        return;
                    }

                    QMessageBox::information(nullptr, "Succès !", "Le manager a bien été modifié.");
                    modifierDialog.close();
                    return;
                }
            }
        });

        modifierDialog.exec();
    }
}

void GestionManagerDialog::supprimerManager() {
    QDialog supprimerDialog(this);
    supprimerDialog.setWindowTitle("Supprimer un manager");

    std::vector<Stand> stands;
    json j;
    j = preloadData();
    const json &eventsJson = j["events"];
    if (getNbStands() == 0) {
        QMessageBox::warning(nullptr, "Attention !", "Aucun manager n'a été trouvé.");
        return;
    } else {
        // Ajout d'un QFormLayout pour les champs de modification
        QFormLayout formLayout(&supprimerDialog);

        // Ajoutez les champs nécessaires pour la modification d'un participant
        eventComboBox = new QComboBox(&supprimerDialog);
        standComboBox = new QComboBox(&supprimerDialog); // Créez la QComboBox ici
        managComboBox = new QComboBox(&supprimerDialog);

        std::vector<Event> events;
        for (const auto &eventJson: eventsJson) {
            Event event(eventJson["nom"], eventJson["date"], eventJson["lieu"]);
            events.push_back(event);
        }
        for (const auto &event: events) {
            eventComboBox->addItem(QString::fromStdString(event.getEventNom()));
        }

        // Connectez le changement de l'événement à la mise à jour des participants
        QObject::connect(eventComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
                         this, &GestionManagerDialog::onEventComboBoxChanged);

        QObject::connect(standComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
                         this, &GestionManagerDialog::onStandComboBoxChanged);

        formLayout.addRow("Événement:", eventComboBox);
        formLayout.addRow("Stand:", standComboBox);
        formLayout.addRow("Manager:", managComboBox);

        // Appeler explicitement onEventComboBoxChanged pour charger les participants initialement
        onEventComboBoxChanged(0);
        onStandComboBoxChanged(0);

        auto *supprimerButton = new QPushButton("Supprimer", &supprimerDialog);
        formLayout.addRow("", supprimerButton);

        // Connectez le bouton "Supprimer" à une fonction de traitement
        QObject::connect(supprimerButton, &QPushButton::clicked, [&]() {
            // Récupérez les valeurs sélectionnées
            int eventIndex = eventComboBox->currentIndex();
            int standIndex = standComboBox->currentIndex();
            int managerIndex = managComboBox->currentIndex();

            const json &selectedEvent = eventsJson[eventIndex];
            if (selectedEvent.find("stands") != selectedEvent.end()) {
                const auto &standsJson = selectedEvent["stands"];
                if (standIndex < standsJson.size()) {
                    const json &standJson = standsJson[standIndex];
                    if (standJson.find("managers") != standJson.end()) {
                        const auto &managersJson = standJson["managers"];
                        if (managerIndex < managersJson.size()) {
                            // Supprimer le manager du stand
                            supprimerManag(managerIndex, standIndex, eventIndex);
                            emit dataModified();
                            QMessageBox::information(nullptr, "Succès !", "Le manager a bien été supprimé du stand.");
                            supprimerDialog.close();
                            return;
                        }
                    }
                }
            }
        });

        supprimerDialog.exec();
    }
}



void GestionManagerDialog::onEventComboBoxChanged(int index) {
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

void GestionManagerDialog::onStandComboBoxChanged(int index) {

    // Effacez la QComboBox des managers
    managComboBox->clear();

    // Chargez les managers liés au stand sélectionné
    json data = preloadData(); // Assurez-vous de récupérer vos données de manière appropriée
    const auto &selectedEvent = data["events"][eventComboBox->currentIndex()];
    const auto &selectedStand = selectedEvent["stands"][index];

    if (selectedStand.find("managers") != selectedStand.end()) {
        const auto &managers = selectedStand["managers"];

        // Videz la QComboBox des managers avant d'ajouter les nouveaux managers
        // Ajoutez une option vide pour indiquer l'absence de manager (facultatif)

        for (const auto &manager : managers) {
            managComboBox->addItem(QString::fromStdString(manager["nom"])); // Ajoutez le manager à la QComboBox
        }
    }
}





