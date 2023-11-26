/********************************************************************
    created:	2023-11-23
    file path:	src/MainWindow.cpp
    author:		W.I.P.
    copyright:	UNLICENSE

    purpose: W.I.P.
*********************************************************************/

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
    pPushButtonManageEvent = new QPushButton("Gérer l'événement", this);
    pPushButtonManageParticipant = new QPushButton("Gérer les participants", this);
    pPushButtonManageStand = new QPushButton("Gérer les stands", this);
    pPushButtonManageManager = new QPushButton("Gérer les managers", this);
    pPushButtonViewData = new QPushButton("Visualiser les données", this);
    pPushButtonExit = new QPushButton("Quitter", this);
    createWidgets();
    createLayout();
    connectSignalsAndSlots();
}

void MainWindow::createWidgets() {
    // Créez les labels en tant que membres de la classe
    pLabelNumberEvents = new QLabel("Nombre d'événements : " + QString::number(getNbEvents()), this);
    pLabelNumberParticipants = new QLabel("Nombre de participants : " + QString::number(getNbParticipants()), this);
    pLabelNumberStands = new QLabel("Nombre de stands : " + QString::number(getNbStands()), this);
    pLabelNumberManagers = new QLabel("Nombre de managers : " + QString::number(getNbManagers()), this);
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

    this->pPushButtonManageEvent->setText("Gérer l'événement");
    this->pPushButtonManageParticipant->setText("Gérer les participants");
    this->pPushButtonManageStand->setText("Gérer les stands");
    this->pPushButtonManageManager->setText("Gérer les managers");
    this->pPushButtonViewData->setText("Visualiser les données");
    this->pPushButtonExit->setText("Quitter");

    buttonGroupLayout->addWidget(pPushButtonManageEvent);
    buttonGroupLayout->addWidget(pPushButtonManageParticipant);
    buttonGroupLayout->addWidget(pPushButtonManageStand);
    buttonGroupLayout->addWidget(pPushButtonManageManager);
    buttonGroup->setLayout(buttonGroupLayout);

    auto *visualiserGroup = new QGroupBox("Visualiser", this);
    auto *visualiserGroupLayout = new QHBoxLayout(visualiserGroup);


    this->pPushButtonViewData->setText("Visualiser les données");
    visualiserGroupLayout->addWidget(pPushButtonViewData);
    visualiserGroup->setLayout(visualiserGroupLayout);

    auto *statsGroup = new QGroupBox("Statistiques", this);
    auto *statsGroupLayout = new QHBoxLayout(statsGroup);

    statsGroupLayout->addWidget(pLabelNumberEvents);
    statsGroupLayout->addWidget(pLabelNumberParticipants);
    statsGroupLayout->addWidget(pLabelNumberStands);
    statsGroupLayout->addWidget(pLabelNumberManagers);
    statsGroup->setLayout(statsGroupLayout);

    layout->addWidget(titreApp);
    layout->addWidget(credits);
    layout->addWidget(buttonGroup);
    layout->addWidget(visualiserGroup);
    layout->addWidget(statsGroup);
    layout->addWidget(pPushButtonExit);


    QObject::connect(pPushButtonManageEvent, &QPushButton::clicked, this, &MainWindow::handleGestionEvenement);
    QObject::connect(pPushButtonManageParticipant, &QPushButton::clicked, this, &MainWindow::handleGestionParticipant);
    QObject::connect(pPushButtonManageStand, &QPushButton::clicked, this, &MainWindow::handleGestionStand);
    QObject::connect(pPushButtonManageManager, &QPushButton::clicked, this, &MainWindow::handleGestionManager);
    QObject::connect(pPushButtonViewData, &QPushButton::clicked, this, &MainWindow::visualiser);
    QObject::connect(pPushButtonExit, &QPushButton::clicked, this, &MainWindow::close);
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
    pLabelNumberEvents->setText("Nombre d'événements : " + QString::number(getNbEvents()));
    pLabelNumberParticipants->setText("Nombre de participants : " + QString::number(getNbParticipants()));
    pLabelNumberStands->setText("Nombre de stands : " + QString::number(getNbStands()));
    pLabelNumberManagers->setText("Nombre de participants : " + QString::number(getNbManagers()));
}
