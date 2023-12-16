#include "include/GestionStand.hpp"

GestionStandDialog::GestionStandDialog(QWidget* pWidgetParent_in) : QDialog(pWidgetParent_in) {
    setWindowTitle("EventX - Gestion des stands");

    auto* pLabelManage = new QLabel("Gestion des stands", this);
    pLabelManage->setAlignment(Qt::AlignCenter);

    auto* pPushButtonCreate = new QPushButton("Créer un stand", this);
    auto* pPushButtonModify = new QPushButton("Modifier un stand", this);
    auto* pPushButtonDelete = new QPushButton("Supprimer un stand", this);
    auto* pPushButtonBack = new QPushButton("Retour", this);
    auto* VBoxLayoutDialog = new QVBoxLayout(this);

    VBoxLayoutDialog->addWidget(pLabelManage);
    VBoxLayoutDialog->addWidget(pPushButtonCreate);
    VBoxLayoutDialog->addWidget(pPushButtonModify);
    VBoxLayoutDialog->addWidget(pPushButtonDelete);
    VBoxLayoutDialog->addWidget(pPushButtonBack);

    QObject::connect(pPushButtonCreate, &QPushButton::clicked, this, &GestionStandDialog::CreateStandDialog);
    QObject::connect(pPushButtonModify, &QPushButton::clicked, this, &GestionStandDialog::ModifyStandDialog);
    QObject::connect(pPushButtonDelete, &QPushButton::clicked, this, &GestionStandDialog::DeleteStandDialog);
    QObject::connect(pPushButtonBack, &QPushButton::clicked, this, &GestionStandDialog::close);
}

void GestionStandDialog::CreateStandDialog() {
    unsigned int nNumberOfEvents = 0;
    json* jsonData = new json();
    *jsonData = PreloadData();
    nNumberOfEvents = GetNumberOfEvents();
    if (nNumberOfEvents == 0) {
        QMessageBox::warning(nullptr, "Attention !", "Aucun événement n'a été créé, aucun stand ne peut être créé");
        return;
    }
    else {
        QDialog dialogCreate(this);
        dialogCreate.setWindowTitle("Créer un stand");

        QFormLayout formLayoutDialog(&dialogCreate);

        // Add the fields required to create a participant
        auto* pComboBoxEvent = new QComboBox(&dialogCreate);
        auto* pLineEditName = new QLineEdit(&dialogCreate);
        auto* pLineEditSurface = new QLineEdit(&dialogCreate);
        auto* pRegularExpressionValidatorSurface = new QRegularExpressionValidator(QRegularExpression("(([1-9][0-9]*)|0)([.][0-9]*)?"));
        pLineEditSurface->setValidator(pRegularExpressionValidatorSurface);
        // Add a suffix to QLineEdit
        std::vector<Event> vecEventsAll;
        json jsonData;
        std::ifstream ifstreamData(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation).toStdString() + "/data.json");
        ifstreamData >> jsonData;
        ifstreamData.close();
        const json& jsonEventsAll = jsonData["events"];
        for (const auto& eventJson : jsonEventsAll) {
            Event eventActual(eventJson["nom"], eventJson["date"], eventJson["lieu"]);
            vecEventsAll.push_back(eventActual);
        }
        for (const auto& eventActual : vecEventsAll) {
            pComboBoxEvent->addItem(QString::fromStdString(eventActual.GetEventName()));
        }

        formLayoutDialog.addRow("Événement:", pComboBoxEvent);
        formLayoutDialog.addRow("Nom du stand:", pLineEditName);
        formLayoutDialog.addRow("Surface du stand:", pLineEditSurface);

        auto* pPushButtonCreate = new QPushButton("Créer", &dialogCreate);
        formLayoutDialog.addRow("", pPushButtonCreate);

        // Connect the "Create" button to a processing function
        QObject::connect(pPushButtonCreate, &QPushButton::clicked, [&]() {
            // Retrieve the values entered in the fields
            unsigned int nIndexEvent = pComboBoxEvent->currentIndex();
        QString sNameEvent = pLineEditName->text();
        QString sSurfaceEvent = pLineEditSurface->text();

        if (sNameEvent.isEmpty() || sSurfaceEvent.isEmpty()) {
            if (sNameEvent.isEmpty()) {
                QMessageBox::warning(nullptr, "Attention !", "Le nom est vide");
            }
            if (sSurfaceEvent.isEmpty()) {
                QMessageBox::warning(nullptr, "Attention !", "La surface est vide");
            }
        }
        else {
            // Create a Stand object with the retrieved values
            Stand stand(sNameEvent.toStdString(), sSurfaceEvent.toDouble());
            // Add the stand to the database
            AddStand(&stand, nIndexEvent);
            emit DataModified();
            QMessageBox::information(nullptr, "Succès !", "Le stand a bien été créé");
            dialogCreate.close();
        }
            });
        dialogCreate.exec();
    }
}

void GestionStandDialog::ModifyStandDialog() {
    QDialog dialogModify(this);
    dialogModify.setWindowTitle("Modifier un stand");

    json jsonData;
    jsonData = PreloadData();
    if (GetNumberOfStands() == 0) {
        QMessageBox::warning(nullptr, "Attention !", "Aucun stand n'a été trouvé.");
    }
    else {
        // Add a QFormLayout for edit fields
        QFormLayout formLayout(&dialogModify);

        // Add the fields required to modify a participant
        m_pComboBoxEvent = new QComboBox(&dialogModify);
        m_pComboBoxStand = new QComboBox(&dialogModify);

        std::vector<Event> vecEventsAll;
        const json& jsonEventsAll = jsonData["events"];
        for (const auto& eventJson : jsonEventsAll) {
            Event event(eventJson["nom"], eventJson["date"], eventJson["lieu"]);
            vecEventsAll.push_back(event);
        }
        for (const auto& eventActual : vecEventsAll) {
            m_pComboBoxEvent->addItem(QString::fromStdString(eventActual.GetEventName()));
        }
        // Connect the event change to the participant update
        QObject::connect(m_pComboBoxEvent, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &GestionStandDialog::onEventComboBoxChanged);
        auto* pLineEditName = new QLineEdit(&dialogModify);
        auto* pLineEditSurface = new QLineEdit(&dialogModify);
        auto* pRegularExpressionValidatorSurface = new QRegularExpressionValidator(QRegularExpression("(([1-9][0-9]*)|0)([.][0-9]*)?"));
        pLineEditSurface->setValidator(pRegularExpressionValidatorSurface);

        formLayout.addRow("Événement:", m_pComboBoxEvent);
        formLayout.addRow("Stand:", m_pComboBoxStand);
        formLayout.addRow("Nom du stand:", pLineEditName);
        formLayout.addRow("Surface du stand:", pLineEditSurface);

        auto* pLabelNoStand = new QLabel("L'évènement séléctionné n'as pas de stand. \r\nVeuillez lui créer un stand ou bien séléctionnez un autre évènement.", &dialogModify);
        formLayout.addRow("", pLabelNoStand);
        auto* pPushButtonModify = new QPushButton("Modifier", &dialogModify);
        formLayout.addRow("", pPushButtonModify);


        QObject::connect(m_pComboBoxStand, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), [&] {
            unsigned int nIndexEvent = m_pComboBoxEvent->currentIndex();
            unsigned int standIndex = m_pComboBoxStand->currentIndex();
            const json& jsonSelectedEvent = jsonEventsAll[nIndexEvent]; //Get the actual event
            if (GetNumberOfStandsFromAEvent(jsonSelectedEvent) != 0) {
                const auto& jsonStandsAll = jsonSelectedEvent["stands"]; //Get all stands of the event
                const json& standJsonActual = jsonStandsAll[standIndex]; //Get the actual stand
                pLineEditName->setText(QString::fromStdString(standJsonActual["nom"]));
                double surface = standJsonActual["surface"];
                pLineEditSurface->setText(QString::number(surface));
            }
            else {
                pLineEditName->setText("");
                pLineEditSurface->setText("");
            }
        });

        // explicitly call onEventComboBoxChanged to load participants initially
        onEventComboBoxChanged(0);

        // Connect the "Modify" button to a processing function
        QObject::connect(pPushButtonModify, &QPushButton::clicked, [&]() {
            // Retrieve selected values
            unsigned int nIndexEvent = m_pComboBoxEvent->currentIndex();
            unsigned int nIndexStand = m_pComboBoxStand->currentIndex();
            const json& selectedEvent = jsonEventsAll[nIndexEvent];
            if (selectedEvent.find("stands") != selectedEvent.end()) {
                const auto& standsJson = selectedEvent["stands"];
                if (nIndexStand < standsJson.size()) {
                    QString sNameStand = pLineEditName->text();
                    QString sSurface = pLineEditSurface->text();

                    if (sNameStand.isEmpty() || sSurface.isEmpty()) {
                        if (sNameStand.isEmpty()) {
                            QMessageBox::warning(nullptr, "Attention !", "Le nom est vide");
                        }
                        if (sSurface.isEmpty()) {
                            QMessageBox::warning(nullptr, "Attention !", "La surface est vide");
                        }
                    }
                    else {
                        // Create a Stand object with the retrieved values
                        Stand standWithNewValues(sNameStand.toStdString(), sSurface.toDouble());
                        // Modify the stand in the database
                        ModifyStand(&standWithNewValues, nIndexEvent, nIndexStand);

                        QMessageBox::information(nullptr, "Succès !", "Le stand a bien été modifié.");
                        dialogModify.close();
                        return;
                    }

                    QMessageBox::information(nullptr, "Succès !", "Le stand a bien été modifié.");
                    dialogModify.close();
                    return;
                }
            }
        });
        dialogModify.exec();
    }
}

void GestionStandDialog::DeleteStandDialog() {
    QDialog dialogDelete(this);
    dialogDelete.setWindowTitle("Supprimer un stand");

    json jsonData;
    jsonData = PreloadData();
    if (GetNumberOfStands() == 0) {
        QMessageBox::warning(nullptr, "Attention !", "Aucun stand n'a été trouvé.");
    }
    else {
        // Add a QFormLayout for deletion fields
        QFormLayout formLayoutDialog(&dialogDelete);

        // Ajoutez les champs nécessaires pour la suppression d'un participant
        m_pComboBoxEvent = new QComboBox(&dialogDelete);
        m_pComboBoxStand = new QComboBox(&dialogDelete); // Créez la QComboBox ici

        std::vector<Event> vecEventsAll;
        const json& jsonEventsAll = jsonData["events"];
        for (const auto& jsonActualEvent : jsonEventsAll) {
            Event EventToAddToVec(jsonActualEvent["nom"], jsonActualEvent["date"], jsonActualEvent["lieu"]);
            vecEventsAll.push_back(EventToAddToVec);
        }
        for (const auto& eventActual : vecEventsAll) {
            m_pComboBoxEvent->addItem(QString::fromStdString(eventActual.GetEventName()));
        }

        QObject::connect(m_pComboBoxEvent, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &GestionStandDialog::onEventComboBoxChanged);

        formLayoutDialog.addRow("Événement:", m_pComboBoxEvent);
        formLayoutDialog.addRow("Stand:", m_pComboBoxStand);
        auto* pLabelNoStand = new QLabel("L'évènement séléctionné n'as pas de stand. \r\nVeuillez séléctionnez un autre évènement.", &dialogDelete);
        formLayoutDialog.addRow("", pLabelNoStand);
        auto* pPushButtonDelete = new QPushButton("Supprimer", &dialogDelete);
        formLayoutDialog.addRow("", pPushButtonDelete);
        // explicitly call onEventComboBoxChanged to load participants initially
        onEventComboBoxChanged(0);

        // Connect the "Delete" button to a processing function
        QObject::connect(pPushButtonDelete, &QPushButton::clicked, [&]() {
            // Retrieve selected values
            int nIndexEvent = m_pComboBoxEvent->currentIndex();
            int nIndexStand = m_pComboBoxStand->currentIndex();

            const json& jsonSelectedEvent = jsonEventsAll[nIndexEvent];
            if (jsonSelectedEvent.find("stands") != jsonSelectedEvent.end()) {
                const auto& standsJson = jsonSelectedEvent["stands"];
                if (nIndexStand < standsJson.size()) {
                    const json& standJson = standsJson[nIndexStand];
                    DeleteStand(nIndexEvent, nIndexStand);
                    emit DataModified();
                    QMessageBox::information(nullptr, "Succès !", "Le stand a bien été supprimé.");
                    dialogDelete.close();
                    return;
                }
            }
        });
        dialogDelete.exec();
    }
}

void GestionStandDialog::onEventComboBoxChanged(int index) {
    // Delete participants' QComboBoxes
    m_pComboBoxStand->clear();

    // Load participants linked to the selected event
    json jsonData = PreloadData(); // Make sure you recover your data properly
    const auto& jsonSelectedEvent = jsonData["events"][index];
    QFormLayout* pFormLayoutDialog = qobject_cast<QFormLayout*>(m_pComboBoxStand->parentWidget()->layout());
    QDialog* dialogParent = qobject_cast<QDialog*>(pFormLayoutDialog->parent());

    if (jsonSelectedEvent.find("stands") != jsonSelectedEvent.end()) {
        if (pFormLayoutDialog->rowCount() == 6) {

            dialogParent->setFixedSize(252, 158);
        }
        else if (pFormLayoutDialog->rowCount() == 4) { //Delete stand

            dialogParent->setFixedSize(180, 102);
        }

        const auto& jsonAllStandsOfSelectedEvent = jsonSelectedEvent["stands"];
        for (const auto& jsonActualStand : jsonAllStandsOfSelectedEvent) {
            m_pComboBoxStand->addItem(QString::fromStdString(jsonActualStand["nom"])); // Ajoutez le participant à la QComboBox
        }
    }
    else {
        if (pFormLayoutDialog->rowCount() == 6) { //Modify stand

            dialogParent->setFixedSize(452, 158);
        }
        else if (pFormLayoutDialog->rowCount() == 4) { //Delete stand

            dialogParent->setFixedSize(265, 102);
        }
    }
}