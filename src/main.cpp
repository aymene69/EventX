#include <nlohmann/json.hpp>
#include <fstream>
#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QScreen>
#include <QDialog>
#include <QDebug>
#include <QLineEdit>
#include <QFormLayout>
#include "include/Event.hpp"
#include "include/Participant.hpp"
#include "include/Stand.hpp"
#include "include/Manager.hpp"

using json = nlohmann::json;

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

            // Utilisez ces valeurs pour créer votre événement (ou appelez une fonction de création)
            // ...
            Event* event = new Event(nom.toStdString(), date.toStdString(), "Lyon");
            updateJson("e", event);

            // Fermez la boîte de dialogue de création
            creerDialog.close();
        });

        creerDialog.exec();
    }

    // Ajoutez les slots pour modifierEvenement et supprimerEvenement si nécessaire

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
    QWidget window;

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
    QVBoxLayout *layout = new QVBoxLayout(&window);

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
