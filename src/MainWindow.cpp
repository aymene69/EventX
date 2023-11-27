#include "include/MainWindow.hpp"
#include "include/GestionEvenement.hpp"
#include "include/GestionParticipant.hpp"
#include "include/GestionStand.hpp"
#include "include/GestionManager.hpp"
#include "include/FonctionsJson.hpp"
#include "include/FonctionsDemarrage.hpp"
#include <QStandardPaths>
#include <QObject>
#include <QVBoxLayout>
#include <QPushButton>
#include <QStandardItemModel>
#include <QTreeView>
#include <QMessageBox>

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
    QObject::connect(pPushButtonViewData, &QPushButton::clicked, this, &MainWindow::viewData);
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

void MainWindow::viewData() {
    // Créer la fenêtre de visualisation des données
    QDialog viewDataDialog(this);
    viewDataDialog.setWindowTitle("EventX - Visualisation des donnees");
    viewDataDialog.setMinimumSize(500, 300);

    // Créer le modèle et la vue pour afficher les données en arbre
    QStandardItemModel* pStandardItemModelData = new QStandardItemModel(&viewDataDialog);
    QTreeView* pTreeViewData = new QTreeView(&viewDataDialog);
    pTreeViewData->setHeaderHidden(true);
    pTreeViewData->setModel(pStandardItemModelData);

    // Charger les données depuis le fichier JSON
    json jsonData = preloadData();

    // Check for events before trying to display data
    if (getNbEvents() == 0) {
        QMessageBox::warning(this, "Avertissement", "Aucun événement à afficher.");
        return;
    } else {
        // Browse events
        for (const auto &event : jsonData["events"]) {
            QStandardItem *pStandardItemEventItem = new QStandardItem(
                    QString("Evenement - Date: %1, Lieu: %2, Nom: %3")
                            .arg(QString::fromStdString(event["date"].get<std::string>()))
                            .arg(QString::fromStdString(event["lieu"].get<std::string>()))
                            .arg(QString::fromStdString(event["nom"].get<std::string>())));
            pStandardItemModelData->appendRow(pStandardItemEventItem);
            // Check for participants before browsing participants
            if (getNbParticipantsFromEvent(event) == 0) {
                QStandardItem *pStandardItemNoParticipants = new QStandardItem("Aucun participant");
                pStandardItemEventItem->appendRow(pStandardItemNoParticipants);
            } else {
                QStandardItem *pStandardItemParticipants = new QStandardItem("Participants");
                pStandardItemEventItem->appendRow(pStandardItemParticipants);
                for (const auto &participant: event["participants"]) {
                    QStandardItem *pStandardItemParticipant = new QStandardItem(
                            QString("Email: %1, Nom: %2, Numero: %3, VIP: %4")
                                    .arg(QString::fromStdString(participant["email"].get<std::string>()))
                                    .arg(QString::fromStdString(participant["nom"].get<std::string>()))
                                    .arg(QString::fromStdString(participant["numero"].get<std::string>()))
                                    .arg(participant["vip"].get<bool>() ? "Oui" : "Non"));
                    pStandardItemParticipants->appendRow(pStandardItemParticipant);
                }
            }
            // Check if there are any pits before going through them
            if (getNbStandsFromEvent(event) == 0) {
                QStandardItem *pStandardItemNoStands = new QStandardItem("Aucun stand");
                pStandardItemEventItem->appendRow(pStandardItemNoStands);
                QStandardItem *pStandardItemNoManagers = new QStandardItem("Aucun manager");
                pStandardItemNoStands->appendRow(pStandardItemNoManagers);
            } else {
                // Browse the event stands
                QStandardItem *pStandardItemStands = new QStandardItem("Stands");
                pStandardItemEventItem->appendRow(pStandardItemStands);
                for (const auto &stand: event["stands"]) {
                    QStandardItem *pStandardItemStand = new QStandardItem(QString("Nom: %1, Numero: %2, Surface: %3")
                                                                                  .arg(QString::fromStdString(
                                                                                          stand["nom"].get<std::string>()))
                                                                                  .arg(stand["numero"].get<int>())
                                                                                  .arg(QString::number(
                                                                                          stand["surface"].get<double>())));
                    pStandardItemStands->appendRow(pStandardItemStand);
                    if (getNbManagersFromStand(stand) == 0) {
                        QStandardItem *pStandardItemNoManagers = new QStandardItem("Aucun manager");
                        pStandardItemStand->appendRow(pStandardItemNoManagers);
                    } else {
                        // Browse stand managers
                        QStandardItem *pStandardItemManagers = new QStandardItem("Managers");
                        pStandardItemStand->appendRow(pStandardItemManagers);
                        for (const auto &manager: stand["managers"]) {
                            QStandardItem *pStandardItemManager = new QStandardItem(
                                    QString("ID: %1, Nom: %2, Numero: %3")
                                            .arg(manager["id"].get<int>())
                                            .arg(QString::fromStdString(manager["nom"].get<std::string>()))
                                            .arg(QString::fromStdString(manager["numero"].get<std::string>())));
                            pStandardItemManagers->appendRow(pStandardItemManager);
                        }
                    }
                }
            }
        }
        QVBoxLayout *pViewDataLayout = new QVBoxLayout(&viewDataDialog);
        pViewDataLayout->addWidget(pTreeViewData);
        viewDataDialog.setLayout(pViewDataLayout);

        // Afficher la fenêtre de visualisation des données (non bloquante)
        viewDataDialog.exec();
    }
}

void MainWindow::handleDataModified() {
    // Mettez à jour les statistiques ici
    pLabelNumberEvents->setText("Nombre d'événements : " + QString::number(getNbEvents()));
    pLabelNumberParticipants->setText("Nombre de participants : " + QString::number(getNbParticipants()));
    pLabelNumberStands->setText("Nombre de stands : " + QString::number(getNbStands()));
    pLabelNumberManagers->setText("Nombre de participants : " + QString::number(getNbManagers()));
}
