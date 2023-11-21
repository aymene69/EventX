#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QScreen>
#include "include/Event.hpp"
#include "include/Participant.hpp"
#include "include/Stand.hpp"
#include "include/Manager.hpp"


int main(int argc, char *argv[]) {
    QApplication eventX(argc, argv);
    QWidget window;

    window.setWindowTitle("EventX 1.0");

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();

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

    // Création des boutons
    QPushButton gererEvent("Gérer l'événement", &window);
    QPushButton gererParticipant("Gérer les participants", &window);
    QPushButton gererStand("Gérer les stands", &window);
    QPushButton gererManager("Gérer les gérants de stands", &window);
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
    layout->addWidget(&quit);

    // Affichage de la fenêtre
    window.show();
    // Connexion des boutons à leurs actions
    QObject::connect(&quit, &QPushButton::clicked, &eventX, &QApplication::quit);

    return QApplication::exec();
}
