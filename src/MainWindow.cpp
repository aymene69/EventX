#include "include/MainWindow.hpp"

MainWindow::MainWindow(QWidget *pWidgetParent_in) : QMainWindow(pWidgetParent_in) {
    this->m_pPushButtonManageEvent = new QPushButton("Gérer les événement", this);
    this->m_pPushButtonManageParticipant = new QPushButton("Gérer les participants", this);
    this->m_pPushButtonManageStand = new QPushButton("Gérer les stands", this);
    this->m_pPushButtonManageManager = new QPushButton("Gérer les managers", this);
    this->m_pPushButtonViewData = new QPushButton("Visualiser les données", this);
    this->m_pPushButtonExit = new QPushButton("Quitter", this);
    CreateWidgets();
    CreateLayout();
    ConnectSignalsAndSlots();

    this->setWindowTitle("EventX 0.7.0");
    this->show();
}

void MainWindow::CreateWidgets() {
    // Create labels as members of class
    this->m_pLabelNumberEvents = new QLabel("Nombre d'événements : " + QString::number(GetNumberOfEvents()), this);
    this->m_pLabelNumberParticipants = new QLabel("Nombre de participants : " + QString::number(GetNumberOfParticipants()), this);
    this->m_pLabelNumberStands = new QLabel("Nombre de stands : " + QString::number(GetNumberOfStands()), this);
    this->m_pLabelNumberManagers = new QLabel("Nombre de managers : " + QString::number(GetNumberOfManagers()), this);
}

void MainWindow::CreateLayout() {
    auto *pWidgetCentral= new QWidget(this);
    setCentralWidget(pWidgetCentral);

    auto *pVBoxLayoutVertical = new QVBoxLayout(pWidgetCentral);

    auto *pLabelApplicationTitle = new QLabel("{ EventX }", this);
    pLabelApplicationTitle->setAlignment(Qt::AlignCenter);
    pLabelApplicationTitle->setStyleSheet("font-size: 50pt;");

    auto *pLabelCredits = new QLabel("par Aymene, Lucas B., Lucas J., Eren, Julien", this);
    pLabelCredits->setAlignment(Qt::AlignCenter);
    pLabelCredits->setStyleSheet("font-size: 10pt;");

    auto *pGroupBoxManage = new QGroupBox("Gérer", this);
    auto *pBoxLayoutManage = new QHBoxLayout(pGroupBoxManage);

    pBoxLayoutManage->addWidget(this->m_pPushButtonManageEvent);
    pBoxLayoutManage->addWidget(this->m_pPushButtonManageParticipant);
    pBoxLayoutManage->addWidget(this->m_pPushButtonManageStand);
    pBoxLayoutManage->addWidget(this->m_pPushButtonManageManager);
    pGroupBoxManage->setLayout(pBoxLayoutManage);

    auto *pGroupBoxView = new QGroupBox("Visualiser", this);
    auto *pBoxLayoutView = new QHBoxLayout(pGroupBoxView);

    this->m_pPushButtonViewData->setText("Visualiser les données");
    pBoxLayoutView->addWidget(this->m_pPushButtonViewData);
    pGroupBoxView->setLayout(pBoxLayoutView);

    auto *pGroupBoxStats = new QGroupBox("Statistiques", this);
    auto *pHBoxLayoutStats = new QHBoxLayout(pGroupBoxStats);

    pHBoxLayoutStats->addWidget(this->m_pLabelNumberEvents);
    pHBoxLayoutStats->addWidget(this->m_pLabelNumberParticipants);
    pHBoxLayoutStats->addWidget(this->m_pLabelNumberStands);
    pHBoxLayoutStats->addWidget(this->m_pLabelNumberManagers);
    pGroupBoxStats->setLayout(pHBoxLayoutStats);

    pVBoxLayoutVertical->addWidget(pLabelApplicationTitle);
    pVBoxLayoutVertical->addWidget(pLabelCredits);
    pVBoxLayoutVertical->addWidget(pGroupBoxManage);
    pVBoxLayoutVertical->addWidget(pGroupBoxView);
    pVBoxLayoutVertical->addWidget(pGroupBoxStats);
    pVBoxLayoutVertical->addWidget(this->m_pPushButtonExit);

    QObject::connect(this->m_pPushButtonManageEvent, &QPushButton::clicked, this, &MainWindow::HandleGestionEvenement);
    QObject::connect(this->m_pPushButtonManageParticipant, &QPushButton::clicked, this, &MainWindow::HandleGestionParticipant);
    QObject::connect(this->m_pPushButtonManageStand, &QPushButton::clicked, this, &MainWindow::HandleGestionStand);
    QObject::connect(this->m_pPushButtonManageManager, &QPushButton::clicked, this, &MainWindow::HandleGestionManager);
    QObject::connect(this->m_pPushButtonViewData, &QPushButton::clicked, this, &MainWindow::ViewData);
    QObject::connect(this->m_pPushButtonExit, &QPushButton::clicked, this, &MainWindow::close);
}

void MainWindow::ConnectSignalsAndSlots() {
    QObject::connect(&this->m_gestionEvenementDialog, &GestionEvenementDialog::DataModified, this, &MainWindow::HandleDataModified);
    QObject::connect(&this->m_gestionParticipantDialog, &GestionParticipantDialog::dataModified, this, &MainWindow::HandleDataModified);
    QObject::connect(&this->m_gestionStandDialog, &GestionStandDialog::DataModified, this, &MainWindow::HandleDataModified);
    QObject::connect(&this->m_gestionManagerDialog, &GestionManagerDialog::DataModified, this, &MainWindow::HandleDataModified);
}

void MainWindow::HandleGestionEvenement() {
    // The event window is displayed
    this->m_gestionEvenementDialog.exec();
}

void MainWindow::HandleGestionParticipant() {
    // The participant window is displayed
    this->m_gestionParticipantDialog.exec();
}

void MainWindow::HandleGestionStand() {
    // The participant window is displayed
    this->m_gestionStandDialog.exec();
}

void MainWindow::HandleGestionManager() {
    // The participant window is displayed
    this->m_gestionManagerDialog.exec();
}

void MainWindow::ViewData() {
    // Create the data display window
    QDialog dialogViewData(this);
    dialogViewData.setWindowTitle("EventX - Visualisation des donnees");
    dialogViewData.setMinimumSize(500, 300);
    // Create the model and view to display tree data
    QStandardItemModel* pStandardItemModelData = new QStandardItemModel(&dialogViewData);
    QTreeView* pTreeViewData = new QTreeView(&dialogViewData);
    pTreeViewData->setHeaderHidden(true);
    pTreeViewData->setModel(pStandardItemModelData);
    // Load data from JSON file
    json jsonData = PreloadData();
    // Check for events before trying to display data
    if (GetNumberOfEvents() == 0) {     
        QMessageBox::warning(this, "Avertissement", "Aucun événement à afficher.");
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
            if (GetNumberOfParticipantsFromAEvent(event) == 0) {
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
            if (GetNumberOfStandsFromAEvent(event) == 0) {
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
                                                                                  .arg(QString::fromStdString(stand["nom"].get<std::string>()))
                                                                                  .arg(stand["id"].get<int>())
                                                                                  .arg(QString::number(stand["surface"].get<double>())));
                    pStandardItemStands->appendRow(pStandardItemStand);
                    if (GetNumberOfManagersFromAStand(stand) == 0) {
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
        QVBoxLayout *pViewDataLayout = new QVBoxLayout(&dialogViewData);
        pViewDataLayout->addWidget(pTreeViewData);
        dialogViewData.setLayout(pViewDataLayout);
        // Display data viewer
        dialogViewData.exec();
    }
}

void MainWindow::HandleDataModified() {
    // Update statistics here
    this->m_pLabelNumberEvents->setText("Nombre d'événements : " + QString::number(GetNumberOfEvents()));
    this->m_pLabelNumberParticipants->setText("Nombre de participants : " + QString::number(GetNumberOfParticipants()));
    this->m_pLabelNumberStands->setText("Nombre de stands : " + QString::number(GetNumberOfStands()));
    this->m_pLabelNumberManagers->setText("Nombre de participants : " + QString::number(GetNumberOfManagers()));
}
