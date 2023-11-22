#include <nlohmann/json.hpp>
#include <fstream>
#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QScreen>
#include <QDebug>
#include <QLineEdit>
#include <QComboBox>
#include <QMessageBox>
#include "include/FonctionsDemarrage.hpp"
#include "include/FonctionsJson.hpp"
#include "include/Event.hpp"
#include "include/Participant.hpp"
#include "include/Stand.hpp"
#include "include/Manager.hpp"
#include "include/GestionEvenement.hpp"
#include "include/GestionParticipant.hpp"

using json = nlohmann::json;

int main(int argc, char *argv[]) {
    QApplication eventX(argc, argv);
    QMainWindow window;

    window.setWindowTitle("EventX 1.0");

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    json* data = new json();
    *data = preloadData();
    int* nbEvents = new int(0);
    *nbEvents = getNbEvents(*data);
    // Définir la taille de la fenêtre (1/3 de la largeur, 1/2 de la hauteur)
    int windowWidth = screenGeometry.width() / 6;
    int windowHeight = screenGeometry.height() / 4;
    window.resize(windowWidth, windowHeight);

    auto *titreApp = new QLabel("EventX", &window);
    titreApp->setAlignment(Qt::AlignCenter);  // Centrer le texte
    titreApp->setStyleSheet("font-size: 50pt;");  // Mettre la police en grand
    auto *credits = new QLabel("par Aymene, Lucas B., Lucas J., Eren, Julien", &window);
    credits->setAlignment(Qt::AlignCenter);  // Centrer le texte
    credits->setStyleSheet("font-size: 10pt;");  // Mettre la police en petit
    auto *nombreEvenements = new QLabel("Nombre d'événements : " + QString::number(*nbEvents), &window);

    // Création des boutons
    QPushButton gererEvent("Gérer les événement", &window);
    QPushButton gererParticipant("Gérer les participants", &window);
    QPushButton gererStand("Gérer les stands", &window);
    QPushButton gererManager("Gérer les gérants de stands", &window);
    QPushButton recharger("Recharger", &window);
    QPushButton quit("Quitter", &window);

    // Création d'un layout vertical
    auto *centralWidget = new QWidget(&window);
    window.setCentralWidget(centralWidget);
    auto *layout = new QVBoxLayout(centralWidget);
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
    GestionParticipantDialog gestionParticipantDialog;
    QObject::connect(&gererEvent, &QPushButton::clicked, [&]() {
        qDebug() << "Bouton Gérer l'événement cliqué.";
        gestionEvenementDialog.exec();
    });

    QObject::connect(&gererParticipant, &QPushButton::clicked, [&]() {
        qDebug() << "Bouton Gérer les participants cliqué.";
        gestionParticipantDialog.exec();
    });

    QObject::connect(&recharger, &QPushButton::clicked, [&]() {
        qDebug() << "Bouton Recharger cliqué.";
        *data = preloadData();
        *nbEvents = (*data)["events"].size();
        nombreEvenements->setText("Nombre d'événements : " + QString::number(*nbEvents));
    });
    QObject::connect(&quit, &QPushButton::clicked, &eventX, &QApplication::quit);

    return QApplication::exec();
}
