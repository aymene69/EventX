#include "include/GestionManager.hpp"

using json = nlohmann::json;

GestionManagerDialog::GestionManagerDialog(QWidget *pWidgetParent_in) : QDialog(pWidgetParent_in) {
    setWindowTitle("EventX - Gestion des managers");

    auto *pLabelManage = new QLabel("Gestion des managers", this);
    pLabelManage->setAlignment(Qt::AlignCenter);
    auto *pPushButtonCreate = new QPushButton("Créer un manager", this);
    auto *pPushButtonModify = new QPushButton("Modifier un manager", this);
    auto *pPushButtonDelete = new QPushButton("Supprimer un manager", this);
    auto * pPushButtonBack = new QPushButton("Retour", this);
    auto *pVBoxLayoutMain = new QVBoxLayout(this);

    pVBoxLayoutMain->addWidget(pLabelManage);
    pVBoxLayoutMain->addWidget(pPushButtonCreate);
    pVBoxLayoutMain->addWidget(pPushButtonModify);
    pVBoxLayoutMain->addWidget(pPushButtonDelete);
    pVBoxLayoutMain->addWidget(pPushButtonBack);

    QObject::connect(pPushButtonCreate, &QPushButton::clicked, this, &GestionManagerDialog::CreateManagerDialog);
    QObject::connect(pPushButtonModify, &QPushButton::clicked, this, &GestionManagerDialog::ModifyManagerDialog);
    QObject::connect(pPushButtonDelete, &QPushButton::clicked, this, &GestionManagerDialog::DeleteManagerDialog);
    QObject::connect(pPushButtonBack, &QPushButton::clicked, this, &GestionManagerDialog::close);
}

void GestionManagerDialog::CreateManagerDialog() {
    json* jsonData = new json();
    *jsonData = PreloadData();
    unsigned int nNumberOfEvents = GetNumberOfEvents();
    unsigned int nNumberOfStands = GetNumberOfStands();
    if (nNumberOfEvents == 0) {
        QMessageBox::warning(nullptr, "Attention !", "Aucun événement n'a été créé, aucun manager ne peut être créé");
        return;
    } else if (nNumberOfStands == 0) {
        QMessageBox::warning(nullptr, "Attention !", "Aucun stand n'a été créé, aucun manager ne peut être créé");
        return;
    } else {
        QDialog dialogCreate(this);
        dialogCreate.setWindowTitle("Créer un Manager");

        QFormLayout formLayoutDialog(&dialogCreate);

        // Add the fields required to create a participant
        this->m_pComboBoxEvent = new QComboBox(&dialogCreate);
        this->m_pComboBoxStand = new QComboBox(&dialogCreate);
        auto *pLineEditName = new QLineEdit(&dialogCreate);
        auto *pLinetEditPhoneNumber = new QLineEdit(&dialogCreate);
        auto* pRegularExpressionValidatorPhoneNumber = new QRegularExpressionValidator(QRegularExpression("^[\+]?[(]?[0-9]{3}[)]?[-\s\.]?[0-9]{3}[-\s\.]?[0-9]{4,6}$"));
        pLinetEditPhoneNumber->setValidator(pRegularExpressionValidatorPhoneNumber);

        std::vector<Event> vecEventsAll;
        json jsonData;
        std::ifstream ifstreamData(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation).toStdString() + "/data.json");
        ifstreamData >> jsonData;
        ifstreamData.close();
        const json &jsonEventsAll = jsonData["events"];
        for (const auto &eventJsonActual: jsonEventsAll) {
            Event eventActual(eventJsonActual["nom"], eventJsonActual["date"], eventJsonActual["lieu"]);
            vecEventsAll.push_back(eventActual);
        }
        for (const auto &eventActual: vecEventsAll) {
            this->m_pComboBoxEvent->addItem(QString::fromStdString(eventActual.GetEventName()));
        }

        // Make a combobox of stands according to the chosen event
        QObject::connect(this->m_pComboBoxEvent, QOverload<int>::of(&QComboBox::currentIndexChanged),
                         this, &GestionManagerDialog::onEventComboBoxChanged);

        formLayoutDialog.addRow("Événement:", this->m_pComboBoxEvent);
        formLayoutDialog.addRow("Stand:", this->m_pComboBoxStand);
        formLayoutDialog.addRow("Nom du manager:", pLineEditName);
        formLayoutDialog.addRow("Numéro de téléphone du manager:", pLinetEditPhoneNumber);

        // explicitly call onEventComboBoxChanged to load participants initially
        onEventComboBoxChanged(0);

        auto *pPushButtonCreate = new QPushButton("Créer", &dialogCreate);
        formLayoutDialog.addRow("", pPushButtonCreate);

        // Connect the "Create" button to a processing function
        QObject::connect(pPushButtonCreate, &QPushButton::clicked, [&]() {
            // Retrieve selected values
            unsigned int nEventIndex = this->m_pComboBoxEvent->currentIndex();
            unsigned int nStandIndex = this->m_pComboBoxStand->currentIndex();
            const json &jsonSelectedEvent = jsonEventsAll[nEventIndex];
            if (jsonSelectedEvent.find("stands") != jsonSelectedEvent.end()) {
                const auto &standsJson = jsonSelectedEvent["stands"];
                if (nStandIndex < standsJson.size()) {
                    const json &standJson = standsJson[nStandIndex];
                    QString sName = pLineEditName->text();
                    QString sPhoneNumber = pLinetEditPhoneNumber->text();
                    if (sName.isEmpty() || sPhoneNumber.isEmpty()) {
                        if (sName.isEmpty()) {
                            QMessageBox::warning(nullptr, "Attention !", "Le nom est vide");
                        }
                        if (sPhoneNumber.isEmpty()) {
                            QMessageBox::warning(nullptr, "Attention !", "Le numéro est vide");
                        }
                    } else {
                        // Create a Manager object with the retrieved values
                        Manager manager(sName.toStdString(), sPhoneNumber.toStdString(), 0);
                        // Add the manager to the database
                        AddManager(&manager, nEventIndex, nStandIndex);

                        emit DataModified();

                        QMessageBox::information(nullptr, "Succès !", "Le manager a bien été créé.");
                        dialogCreate.close();
                        return;
                    }
                }
            }
        });
        dialogCreate.exec();
    }
}

void GestionManagerDialog::ModifyManagerDialog() {
    QDialog dialogModify(this);
    dialogModify.setWindowTitle("Modifier un manager");

    json jsonData;
    jsonData = PreloadData();
    const json &jsonEventsAll = jsonData["events"];
    if (GetNumberOfStands() == 0) {
        QMessageBox::warning(nullptr, "Attention !", "Aucun manager n'a été trouvé.");
    } else {
        // Add a QFormLayout for edit fields
        QFormLayout formLayoutDialog(&dialogModify);

        // Add the fields required to modify a participant
        this->m_pComboBoxEvent = new QComboBox(&dialogModify);
        this->m_pComboBoxStand = new QComboBox(&dialogModify); // Créez la QComboBox ici
        this->m_pComboBoxManager = new QComboBox(&dialogModify);

        std::vector<Event> vecEventsAll;
        for (const auto &eventJson: jsonEventsAll) {
            Event eventActual(eventJson["nom"], eventJson["date"], eventJson["lieu"]);
            vecEventsAll.push_back(eventActual);
        }
        for (const auto &eventActual: vecEventsAll) {
            this->m_pComboBoxEvent->addItem(QString::fromStdString(eventActual.GetEventName()));
        }

        // Connect the event change to the participant update
        QObject::connect(this->m_pComboBoxEvent, QOverload<int>::of(&QComboBox::currentIndexChanged),
                         this, &GestionManagerDialog::onEventComboBoxChanged);

        QObject::connect(this->m_pComboBoxStand, QOverload<int>::of(&QComboBox::currentIndexChanged),
                            this, &GestionManagerDialog::onStandComboBoxChanged);

        QLineEdit *pLineEditName = new QLineEdit(&dialogModify);
        QLineEdit *pLineEditPhoneNumber = new QLineEdit(&dialogModify);
        auto* pRegularExpressionValidatorPhoneNumber = new QRegularExpressionValidator(QRegularExpression("^[\+]?[(]?[0-9]{3}[)]?[-\s\.]?[0-9]{3}[-\s\.]?[0-9]{4,6}$"));
        pLineEditPhoneNumber->setValidator(pRegularExpressionValidatorPhoneNumber);

        formLayoutDialog.addRow("Événement:", this->m_pComboBoxEvent);
        formLayoutDialog.addRow("Stand:", this->m_pComboBoxStand);
        formLayoutDialog.addRow("Manager:", this->m_pComboBoxManager);
        formLayoutDialog.addRow("Nouveau nom du manager:", pLineEditName);
        formLayoutDialog.addRow("Nouveau numéro de téléphone du manager:", pLineEditPhoneNumber);

        // Explicitly call onEventComboBoxChanged to load participants initially
        onEventComboBoxChanged(0);
        onStandComboBoxChanged(0);

        auto *pPushButtonModify = new QPushButton("Modifier", &dialogModify);
        formLayoutDialog.addRow("", pPushButtonModify);

        // Connect the "Modify" button to a processing function
        QObject::connect(pPushButtonModify, &QPushButton::clicked, [&]() {
            // Retrieve selected values
            unsigned int nIndexEvent = this->m_pComboBoxEvent->currentIndex();
            unsigned int nIndexStand = this->m_pComboBoxStand->currentIndex();
            unsigned int nIndexManager = this->m_pComboBoxManager->currentIndex();

            const json &selectedEvent = jsonEventsAll[nIndexEvent];
            if (selectedEvent.find("stands") != selectedEvent.end()) {
                const auto &standsJson = selectedEvent["stands"];
                if (nIndexStand < standsJson.size()) {
                    QString sName = pLineEditName->text();
                    QString sPhoneNumber = pLineEditPhoneNumber->text();
                    if (sName.isEmpty() || sPhoneNumber.isEmpty()) {
                        if (sName.isEmpty()) {
                            QMessageBox::warning(nullptr, "Attention !", "Le nom est vide");
                        }
                        if (sPhoneNumber.isEmpty()) {
                            QMessageBox::warning(nullptr, "Attention !", "Le numéro est vide");
                        }
                    } else {
                        // Create a Manager object with the retrieved values
                        Manager manager(sName.toStdString(), sPhoneNumber.toStdString(), 0);
                        // Modify the stand in the database
                        ModifyManager(&manager, nIndexEvent, nIndexStand, nIndexManager);

                        QMessageBox::information(nullptr, "Succès !", "Le manager a bien été modifié.");
                        dialogModify.close();
                        return;
                    }
                    QMessageBox::information(nullptr, "Succès !", "Le manager a bien été modifié.");
                    dialogModify.close();
                    return;
                }
            }
        });
        dialogModify.exec();
    }
}

void GestionManagerDialog::DeleteManagerDialog() {
    QDialog dialogDelete(this);
    dialogDelete.setWindowTitle("Supprimer un manager");

    std::vector<Stand> vecStandsAll;
    json jsonData;
    jsonData = PreloadData();
    const json &eventsJson = jsonData["events"];
    if (GetNumberOfStands() == 0) {
        QMessageBox::warning(nullptr, "Attention !", "Aucun manager n'a été trouvé.");
        return;
    } else {
        // Add a QFormLayout for edit fields
        QFormLayout formLayoutDialog(&dialogDelete);

        // Add the fields required to modify a participant
        this->m_pComboBoxEvent = new QComboBox(&dialogDelete);
        this->m_pComboBoxStand = new QComboBox(&dialogDelete);
        this->m_pComboBoxManager = new QComboBox(&dialogDelete);

        std::vector<Event> vecEventsAll;
        for (const auto &eventJson: eventsJson) {
            Event eventActual(eventJson["nom"], eventJson["date"], eventJson["lieu"]);
            vecEventsAll.push_back(eventActual);
        }
        for (const auto &eventActual: vecEventsAll) {
            this->m_pComboBoxEvent->addItem(QString::fromStdString(eventActual.GetEventName()));
        }

        // Connect the event change to the participant update
        QObject::connect(this->m_pComboBoxEvent, QOverload<int>::of(&QComboBox::currentIndexChanged),
                         this, &GestionManagerDialog::onEventComboBoxChanged);

        QObject::connect(this->m_pComboBoxEvent, QOverload<int>::of(&QComboBox::currentIndexChanged),
                         this, &GestionManagerDialog::onStandComboBoxChanged);

        formLayoutDialog.addRow("Événement:", this->m_pComboBoxEvent);
        formLayoutDialog.addRow("Stand:", this->m_pComboBoxStand);
        formLayoutDialog.addRow("Manager:", this->m_pComboBoxManager);

        // Explicitly call onEventComboBoxChanged to load participants initially
        onEventComboBoxChanged(0);
        onStandComboBoxChanged(0);

        auto *pPushButtonDelete = new QPushButton("Supprimer", &dialogDelete);
        formLayoutDialog.addRow("", pPushButtonDelete);

        // Connect the "Delete" button to a processing function
        QObject::connect(pPushButtonDelete, &QPushButton::clicked, [&]() {
            // Retrieve selected values
            unsigned int nIndexEvent = this->m_pComboBoxEvent->currentIndex();
            unsigned int nIndexStand = this->m_pComboBoxStand->currentIndex();
            unsigned int nIndexManager = this->m_pComboBoxManager->currentIndex();

            const json &jsonSelectedEvent = eventsJson[nIndexEvent];
            if (jsonSelectedEvent.find("stands") != jsonSelectedEvent.end()) {
                const auto &standsJson = jsonSelectedEvent["stands"];
                if (nIndexStand < standsJson.size()) {
                    const json &jsonStandOfManagerToDelete = standsJson[nIndexStand];
                    if (jsonStandOfManagerToDelete.find("managers") != jsonStandOfManagerToDelete.end()) {
                        const auto &managersJson = jsonStandOfManagerToDelete["managers"];
                        if (nIndexManager < managersJson.size()) {
                            // Supprimer le manager du stand
                            DeleteManager(nIndexEvent, nIndexStand, nIndexManager);
                            emit DataModified();
                            QMessageBox::information(nullptr, "Succès !", "Le manager a bien été supprimé du stand.");
                            dialogDelete.close();
                            return;
                        }
                    }
                }
            }
        });
        dialogDelete.exec();
    }
}

void GestionManagerDialog::onEventComboBoxChanged(int nIndex_in) {
    // Clear the QComboBox of participants    
    this->m_pComboBoxStand->clear();
    // Load participants linked to the selected event
    json jsonData = PreloadData(); // Make sure you recover your data properly
    const auto &selectedEvent = jsonData["events"][nIndex_in];

    if (selectedEvent.find("stands") != selectedEvent.end()) {
        const auto &stands = selectedEvent["stands"];
        for (const auto &stand : stands) {
            this->m_pComboBoxStand->addItem(QString::fromStdString(stand["nom"])); // Ajoutez le participant à la QComboBox
        }
    }
}

void GestionManagerDialog::onStandComboBoxChanged(int index) {

    // Clear the QComboBox of managers   
    this->m_pComboBoxManager->clear();

    // Load managers linked to the selected stand
    json jsonData = PreloadData(); // Make sure you recover your data properly
    const auto &selectedEvent = jsonData["events"][this->m_pComboBoxEvent->currentIndex()];
    const auto &selectedStand = selectedEvent["stands"][index];

    if (selectedStand.find("managers") != selectedStand.end()) {
        const auto &managers = selectedStand["managers"];
        // Empty the managers' QComboBox before adding new managers
        // Add an empty option to indicate the absence of a manager (optional)
        for (const auto &manager : managers) {
            this->m_pComboBoxManager->addItem(QString::fromStdString(manager["nom"])); // Ajoutez le manager à la QComboBox
        }
    }
}