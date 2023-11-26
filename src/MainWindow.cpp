#include "include/MainWindow.hpp"
#include "include/GestionEvenement.hpp"
#include "include/GestionParticipant.hpp"
#include "include/GestionStand.hpp"
#include "include/GestionManager.hpp"
#include "include/FonctionsJson.hpp"
#include "include/FonctionsDemarrage.hpp"
#include "include/ViewData.hpp"
#include <QStandardPaths>
#include <QObject>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    gererEvent = new QPushButton("Gérer l'événement", this);
    gererParticipant = new QPushButton("Gérer les participants", this);
    gererStand = new QPushButton("Gérer les stands", this);
    gererManager = new QPushButton("Gérer les managers", this);
    viewData = new QPushButton("Visualiser les données", this);
    quitter = new QPushButton("Quitter", this);
    createWidgets();
    createLayout();
    connectSignalsAndSlots();
}

void MainWindow::createWidgets() {
    // Créez les labels en tant que membres de la classe
    nombreEvenementsLabel = new QLabel("Nombre d'événements : " + QString::number(getNbEvents()), this);
    nombreParticipantsLabel = new QLabel("Nombre de participants : " + QString::number(getNbParticipants()), this);
    nombreStandsLabel = new QLabel("Nombre de stands : " + QString::number(getNbStands()), this);
    nombreManagersLabel = new QLabel("Nombre de managers : " + QString::number(getNbManagers()), this);
}

void MainWindow::createLayout() {
    auto *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    auto *layout = new QVBoxLayout(centralWidget);

    auto *titreApp = new QLabel("{ EventX }", this);
    titreApp->setAlignment(Qt::AlignCenter);
    titreApp->setStyleSheet("font-size: 50pt;");

    auto *credits = new QLabel("par Aymene, Lucas B., Lucas J., Eren, Julien", this);
    credits->setAlignment(Qt::AlignCenter);
    credits->setStyleSheet("font-size: 10pt;");

    auto *buttonGroup = new QGroupBox("Gérer", this);
    auto *buttonGroupLayout = new QHBoxLayout(buttonGroup);

    this->gererEvent->setText("Gérer l'événement");
    this->gererParticipant->setText("Gérer les participants");
    this->gererStand->setText("Gérer les stands");
    this->gererManager->setText("Gérer les managers");
    this->viewData->setText("Visualiser les données");
    this->quitter->setText("Quitter");

    buttonGroupLayout->addWidget(gererEvent);
    buttonGroupLayout->addWidget(gererParticipant);
    buttonGroupLayout->addWidget(gererStand);
    buttonGroupLayout->addWidget(gererManager);
    buttonGroup->setLayout(buttonGroupLayout);

    auto *visualiserGroup = new QGroupBox("Visualiser", this);
    auto *visualiserGroupLayout = new QHBoxLayout(visualiserGroup);


    this->viewData->setText("Visualiser les données");
    visualiserGroupLayout->addWidget(viewData);
    visualiserGroup->setLayout(visualiserGroupLayout);

    auto *statsGroup = new QGroupBox("Statistiques", this);
    auto *statsGroupLayout = new QHBoxLayout(statsGroup);

    statsGroupLayout->addWidget(nombreEvenementsLabel);
    statsGroupLayout->addWidget(nombreParticipantsLabel);
    statsGroupLayout->addWidget(nombreStandsLabel);
    statsGroupLayout->addWidget(nombreManagersLabel);
    statsGroup->setLayout(statsGroupLayout);

    layout->addWidget(titreApp);
    layout->addWidget(credits);
    layout->addWidget(buttonGroup);
    layout->addWidget(visualiserGroup);
    layout->addWidget(statsGroup);
    layout->addWidget(quitter);


    QObject::connect(gererEvent, &QPushButton::clicked, this, &MainWindow::handleGestionEvenement);
    QObject::connect(gererParticipant, &QPushButton::clicked, this, &MainWindow::handleGestionParticipant);
    QObject::connect(gererStand, &QPushButton::clicked, this, &MainWindow::handleGestionStand);
    QObject::connect(gererManager, &QPushButton::clicked, this, &MainWindow::handleGestionManager);
    QObject::connect(viewData, &QPushButton::clicked, this, &MainWindow::visualiser);
    QObject::connect(quitter, &QPushButton::clicked, this, &MainWindow::close);
}

void MainWindow::connectSignalsAndSlots() {

    QObject::connect(&gestionEvenementDialog, &GestionEvenementDialog::dataModified, this, &MainWindow::handleDataModified);
    QObject::connect(&gestionParticipantDialog, &GestionParticipantDialog::dataModified, this, &MainWindow::handleDataModified);
    QObject::connect(&gestionStandDialog, &GestionStandDialog::dataModified, this, &MainWindow::handleDataModified);
    QObject::connect(&gestionManagerDialog, &GestionManagerDialog::dataModified, this, &MainWindow::handleDataModified);
}

void MainWindow::handleGestionEvenement() {
    // On affiche la fenêtre événement
    gestionEvenementDialog.exec();
}

void MainWindow::handleGestionParticipant() {
    // On affiche la fenêtre participant
    gestionParticipantDialog.exec();
}

void MainWindow::handleGestionStand() {
    // On affiche la fenêtre participant
    gestionStandDialog.exec();
}

void MainWindow::handleGestionManager() {
    // On affiche la fenêtre participant
    gestionManagerDialog.exec();
}

void MainWindow::visualiser() {
    // On affiche la fenêtre de visualisation des données
    viewDataDialog.exec();
}

void MainWindow::handleDataModified() {
    // Mettez à jour les statistiques ici
    nombreEvenementsLabel->setText("Nombre d'événements : " + QString::number(getNbEvents()));
    nombreParticipantsLabel->setText("Nombre de participants : " + QString::number(getNbParticipants()));
    nombreStandsLabel->setText("Nombre de stands : " + QString::number(getNbStands()));
    nombreManagersLabel->setText("Nombre de participants : " + QString::number(getNbManagers()));
}
