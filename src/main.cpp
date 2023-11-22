#include <nlohmann/json.hpp>
#include <fstream>
#include <regex>
#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QScreen>
#include <QDialog>
#include <QDebug>
#include <QLineEdit>
#include <QFormLayout>
#include <QComboBox>
#include <QMessageBox>
#include "include/Event.hpp"
#include "include/Participant.hpp"
#include "include/Stand.hpp"
#include "include/Manager.hpp"

using json = nlohmann::json;

bool verifDate(std::string date) {
    std::regex dateRegex("([0-9]{2})/([0-9]{2})/([0-9]{4})");
    return std::regex_match(date, dateRegex);
}

void updateJson(std::string type, void* object) {
    std::ifstream i("data.json");
    json j;
    i >> j;
    i.close();

    if (type == "e") {
        Event* event = (Event*) object;
        json eventJson;
        eventJson["nom"] = event->getEventNom();
        eventJson["date"] = event->getEventDate();
        eventJson["lieu"] = event->getEventLieu();
        j["events"].push_back(eventJson);
    } else if (type == "p") {
        Participant* participant = (Participant*) object;
        json participantJson;
        participantJson["nom"] = participant->getNomParticipant();
        participantJson["vip"] = participant->getVIPParticipant();
        participantJson["numero"] = participant->getNumParticipant();
        participantJson["email"] = participant->getEmailParticipant();
        j["participants"].push_back(participantJson);
    } else if (type == "s") {
        Stand* stand = (Stand*) object;
        json standJson;
        standJson["nom"] = stand->getStandNom();
        standJson["numero"] = stand->getStandNum();
        j["stands"].push_back(standJson);
    } else if (type == "m") {
        Manager* manager = (Manager*) object;
        json managerJson;
        managerJson["nom"] = manager->getManagerNom();
        managerJson["numero"] = manager->getManagerNum();
        j["managers"].push_back(managerJson);
    }

    std::ofstream o("data.json");
    o << std::setw(4) << j << std::endl;
    o.close();
}

void modifierJson(std::string type, void* object, int index) {
    std::ifstream i("data.json");
    json j;
    i >> j;
    i.close();

    if (type == "e") {
        Event* event = static_cast<Event*>(object);
        json eventJson;
        eventJson["nom"] = event->getEventNom();
        eventJson["date"] = event->getEventDate();
        eventJson["lieu"] = event->getEventLieu();
        j["events"][index] = eventJson;
    } else if (type == "p") {
        Participant* participant = static_cast<Participant*>(object);
        json participantJson;
        participantJson["nom"] = participant->getNomParticipant();
        participantJson["vip"] = participant->getVIPParticipant();
        participantJson["numero"] = participant->getNumParticipant();
        participantJson["email"] = participant->getEmailParticipant();
        j["participants"][index] = participantJson;
    } else if (type == "s") {
        Stand* stand = static_cast<Stand*>(object);
        json standJson;
        standJson["nom"] = stand->getStandNom();
        standJson["numero"] = stand->getStandNum();
        j["stands"][index] = standJson;
    } else if (type == "m") {
        Manager* manager = static_cast<Manager*>(object);
        json managerJson;
        managerJson["nom"] = manager->getManagerNom();
        managerJson["numero"] = manager->getManagerNum();
        j["managers"][index] = managerJson;
    }

    std::ofstream o("data.json");
    o << std::setw(4) << j << std::endl;
    o.close();
}

void supprimerJson(std::string type, void* object, int index) {
    std::ifstream i("data.json");
    json j;
    i >> j;
    i.close();

    if (type == "e") {
        j["events"].erase(index);
    } else if (type == "p") {
        j["participants"].erase(index);
    } else if (type == "s") {
        j["stands"].erase(index);
    } else if (type == "m") {
        j["managers"].erase(index);
    }

    std::ofstream o("data.json");
    o << std::setw(4) << j << std::endl;
    o.close();
}

class GestionEvenementDialog : public QDialog {

public:
    GestionEvenementDialog(QWidget *parent = nullptr) : QDialog(parent) {
        setWindowTitle("EventX - Gestion des événements");

        QLabel *label = new QLabel("Gestion des événements.", this);
        label->setAlignment(Qt::AlignCenter);

        QPushButton *creer = new QPushButton("Créer un événement", this);
        QPushButton *modifier = new QPushButton("Modifier un événement", this);
        QPushButton *supprimer = new QPushButton("Supprimer un événement", this);
        QPushButton *retour = new QPushButton("Retour", this);
        QVBoxLayout *layout = new QVBoxLayout(this);

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
public slots:
    void creerEvenement() {
        QDialog creerDialog(this);
        creerDialog.setWindowTitle("Créer un événement");

        QFormLayout formLayout(&creerDialog);

        // Ajoutez les champs nécessaires pour la création d'un événement
        QLineEdit *nomLineEdit = new QLineEdit(&creerDialog);
        QLineEdit *dateLineEdit = new QLineEdit(&creerDialog);
        QLineEdit *lieuLineEdit = new QLineEdit(&creerDialog);

        formLayout.addRow("Nom de l'événement:", nomLineEdit);
        formLayout.addRow("Date de l'événement:", dateLineEdit);
        formLayout.addRow("Lieu de l'événement:", lieuLineEdit);

        QPushButton *creerButton = new QPushButton("Créer", &creerDialog);
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
                    Event *event = new Event(nom.toStdString(), date.toStdString(), lieu.toStdString());

                    // Utilisez l'événement créé pour modifier le JSON
                    updateJson("e", event);
                    QMessageBox::information(nullptr, "Succès !", "L'événement a bien été créé.");
                    // Fermez la boîte de dialogue de création
                    creerDialog.close();
                }
            }
            });
        creerDialog.exec();
    }


    void modifierEvenement() {
        QDialog modifierDialog(this);
        modifierDialog.setWindowTitle("Modifier un événement");

        std::vector<Event> events;
        json j;
        std::ifstream i("data.json");
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
            QComboBox *comboBox = new QComboBox(&modifierDialog);
            for (int i = 0; i < events.size(); i++) {
                comboBox->addItem(QString::fromStdString(events[i].getEventNom()));
            }

            QLineEdit *nomLineEdit = new QLineEdit(&modifierDialog);
            QLineEdit *dateLineEdit = new QLineEdit(&modifierDialog);
            QLineEdit *lieuLineEdit = new QLineEdit(&modifierDialog);

            formLayout.addRow("Nom de l'événement:", comboBox);
            formLayout.addRow("Nouveau nom de l'événement:", nomLineEdit);
            formLayout.addRow("Nouvelle date de l'événement:", dateLineEdit);
            formLayout.addRow("Nouveau lieu de l'événement:", lieuLineEdit);

            QPushButton *modifierButton = new QPushButton("Modifier", &modifierDialog);
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
                        Event *event = new Event(nom.toStdString(), date.toStdString(), lieu.toStdString());

                        // Utilisez l'événement créé pour modifier le JSON
                        modifierJson("e", event, index);
                        QMessageBox::information(nullptr, "Succès !", "L'événement a bien été modifié.");
                        // Fermez la boîte de dialogue de modification
                        modifierDialog.close();
                    }
                }
            });
            modifierDialog.exec();
        }
    }


    void supprimerEvenement() {
        QDialog supprimerDialog(this);
        supprimerDialog.setWindowTitle("Supprimer un événement");

        std::vector<Event> events;
        json j;
        std::ifstream i("data.json");
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
            QComboBox *comboBox = new QComboBox(&supprimerDialog);
            for (int i = 0; i < events.size(); i++) {
                comboBox->addItem(QString::fromStdString(events[i].getEventNom()));
            }

            formLayout.addRow("Nom de l'événement:", comboBox);

            QPushButton *supprimerButton = new QPushButton("Supprimer", &supprimerDialog);
            formLayout.addRow("", supprimerButton);

            // Connectez le bouton "Supprimer" à une fonction de traitement
            QObject::connect(supprimerButton, &QPushButton::clicked, [&]() {
                // Récupérez les valeurs saisies dans les champs
                int index = comboBox->currentIndex();

                // Utilisez l'objet Event existant pour modifier le JSON
                supprimerJson("e", &events[index], index);
                QMessageBox::information(nullptr, "Succès !", "L'événement a bien été supprimé.");
                // Fermez la boîte de dialogue de suppression
                supprimerDialog.close();
            });
            supprimerDialog.exec();
        }

    }

};

class aucuneDataException : public QDialog {

public:
    aucuneDataException(QWidget *parent = nullptr) : QDialog(parent) {
        setWindowTitle("EventX - Préchargement des données");

        QLabel *label = new QLabel("Aucune donnée n'a été trouvée. Une base de donnée vide vous sera fournie.", this);
        QPushButton *bouton = new QPushButton("OK", this);
        label->setAlignment(Qt::AlignCenter);
        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addWidget(label);
        layout->addWidget(bouton);

        QObject::connect(bouton, &QPushButton::clicked, this, &aucuneDataException::close);
    }
};

json preloadData(json data) {
    std::ifstream i("data.json");

    if (!i.is_open()) {
        aucuneDataException aucuneDataException;
        aucuneDataException.exec();
        std::ofstream o("data.json");
        o << data;
        o.close();
        return data;
    }
    else {
        i >> data;
        return data;
    }
}

int main(int argc, char *argv[]) {
    QApplication eventX(argc, argv);
    QMainWindow window;

    window.setWindowTitle("EventX 1.0");

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int* nbEvents = new int(0);
    json* data = new json();
    *data = preloadData(*data);
    const json& events = (*data)["events"];

    *nbEvents = events.size();
    // Définir la taille de la fenêtre (1/3 de la largeur, 1/2 de la hauteur)
    int windowWidth = screenGeometry.width() / 6;
    int windowHeight = screenGeometry.height() / 4;
    window.resize(windowWidth, windowHeight);

    QLabel *titreApp = new QLabel("EventX", &window);
    titreApp->setAlignment(Qt::AlignCenter);  // Centrer le texte
    titreApp->setStyleSheet("font-size: 50pt;");  // Mettre la police en grand
    QLabel *credits = new QLabel("par Aymene, Lucas B., Lucas J., Eren, Julien", &window);
    credits->setAlignment(Qt::AlignCenter);  // Centrer le texte
    credits->setStyleSheet("font-size: 10pt;");  // Mettre la police en petit
    QLabel *nombreEvenements = new QLabel("Nombre d'événements : " + QString::number(*nbEvents), &window);

    // Création des boutons
    QPushButton gererEvent("Gérer les événement", &window);
    QPushButton gererParticipant("Gérer les participants", &window);
    QPushButton gererStand("Gérer les stands", &window);
    QPushButton gererManager("Gérer les gérants de stands", &window);
    QPushButton recharger("Recharger", &window);
    QPushButton quit("Quitter", &window);

    // Création d'un layout vertical
    QWidget *centralWidget = new QWidget(&window);
    window.setCentralWidget(centralWidget);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    // Ajout des boutons au layout
    layout->addWidget(titreApp);
    layout->addWidget(credits);
    layout->addWidget(&gererEvent);
    layout->addWidget(&gererParticipant);
    layout->addWidget(&gererStand);
    layout->addWidget(&gererManager);
    layout->addWidget(&recharger);
    layout->addWidget(&quit);
    layout->addWidget(nombreEvenements);
    // Affichage de la fenêtre
    window.show();

    // Connexion des boutons à leurs actions
    GestionEvenementDialog gestionEvenementDialog;
    QObject::connect(&gererEvent, &QPushButton::clicked, [&]() {
        qDebug() << "Bouton Gérer l'événement cliqué.";
        gestionEvenementDialog.exec();
    });
    QObject::connect(&recharger, &QPushButton::clicked, [&]() {
        qDebug() << "Bouton Recharger cliqué.";
        *data = preloadData(*data);
        *nbEvents = (*data)["events"].size();
        nombreEvenements->setText("Nombre d'événements : " + QString::number(*nbEvents));
    });
    QObject::connect(&quit, &QPushButton::clicked, &eventX, &QApplication::quit);

    return QApplication::exec();
}
