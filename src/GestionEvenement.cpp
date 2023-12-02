#include "include/GestionEvenement.hpp"

GestionEvenementDialog::GestionEvenementDialog(QWidget *pWidgetParent_in): QDialog(pWidgetParent_in) {
    setWindowTitle("EventX - Gestion des événements");
    setFixedSize(250, 175);

    auto *pPushButtonCreate = new QPushButton("Créer un événement", this);
    auto *pPushButtonModify = new QPushButton("Modifier un événement", this);
    auto *pPushButtonDelete = new QPushButton("Supprimer un événement", this);
    auto *pPushButtonBack = new QPushButton("Retour", this);
    auto *pVBoxLayoutMain = new QVBoxLayout(this);

    pVBoxLayoutMain->addWidget(pPushButtonCreate);
    pVBoxLayoutMain->addWidget(pPushButtonModify);
    pVBoxLayoutMain->addWidget(pPushButtonDelete);
    pVBoxLayoutMain->addWidget(pPushButtonBack);

    QObject::connect(pPushButtonCreate, &QPushButton::clicked, this, &GestionEvenementDialog::CreateEventDialog);
    QObject::connect(pPushButtonModify, &QPushButton::clicked, this, &GestionEvenementDialog::ModifyEventDialog);
    QObject::connect(pPushButtonDelete, &QPushButton::clicked, this, &GestionEvenementDialog::DeleteEventDialog);
    QObject::connect(pPushButtonBack, &QPushButton::clicked, this, &GestionEvenementDialog::close);
}

void GestionEvenementDialog::CreateEventDialog() {
    QDialog dialogCreate(this);
    dialogCreate.setWindowTitle("Créer un événement");

    QFormLayout formLayoutDialog(&dialogCreate);

    // Add the fields required to create an event
    auto* pLineEditName = new QLineEdit(&dialogCreate);
    auto* pDateEditEvent = new QDateEdit(&dialogCreate);
    auto* pLineEditLocation = new QLineEdit(&dialogCreate);
    auto* pPushButtonCreate = new QPushButton("Créer", &dialogCreate);

    pDateEditEvent->setDate(QDate::currentDate());

    formLayoutDialog.addRow("Nom de l'événement:", pLineEditName);
    formLayoutDialog.addRow("Date de l'événement:", pDateEditEvent);
    formLayoutDialog.addRow("Lieu de l'événement:", pLineEditLocation);
    formLayoutDialog.addRow("", pPushButtonCreate);

    // Connect the "Create" button to a processing function
    QObject::connect(pPushButtonCreate, &QPushButton::clicked, [&]() {
        // Retrieve the values entered in the fields
        QString sName = pLineEditName->text();
        QString sDate = pDateEditEvent->date().toString("dd/MM/yyyy");
        QString sLocation = pLineEditLocation->text();

        if (sName.isEmpty() || sLocation.isEmpty()) {
            if (sName.isEmpty()) {
                QMessageBox::warning(nullptr, "Attention !", "Le nom est vide");
            }
            if (sLocation.isEmpty()) {
                QMessageBox::warning(nullptr, "Attention !", "Le lieu est vide");
            }
        }
        else {
                // Créez un nouvel événement avec les valeurs récupérées
                auto* pEventToAdd = new Event(sName.toStdString(), sDate.toStdString(), sLocation.toStdString());

                // Utilisez l'événement créé pour modifier le JSON
                AddEvent(pEventToAdd);

                emit DataModified();

                QMessageBox::information(nullptr, "Succès !", "L'événement a bien été créé.");
                // Fermez la boîte de dialogue de création
                dialogCreate.close();
        }
    });
    dialogCreate.exec();
}

void GestionEvenementDialog::ModifyEventDialog() {
    QDialog* pDialogModify = new QDialog(this);
    pDialogModify->setWindowTitle("Modifier un événement");
    std::vector<Event*> pVecEventAll;
    json jsonData;
    std::ifstream ifstreamJsonStream(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation).toStdString() + "/data.json");
    ifstreamJsonStream >> jsonData;
    ifstreamJsonStream.close();
    const json& eventsJson = jsonData["events"];
    if (eventsJson.size() == 0) {
        QMessageBox::warning(nullptr, "Attention !", "Aucun événement n'a été trouvé.");
        delete pDialogModify;
    }
    else {
        for (json::const_iterator it = eventsJson.begin(); it != eventsJson.end(); ++it) {
            Event* pEventSingle = new Event(it.value()["nom"], it.value()["date"], it.value()["lieu"]);
            pVecEventAll.push_back(pEventSingle);
        }
        QFormLayout* pFormLayoutDialog = new QFormLayout(pDialogModify);
        // Add the fields needed to modify an event
        auto* pComboBoxEvent = new QComboBox(pDialogModify);
        for (int i = 0; i < pVecEventAll.size(); i++) {
            pComboBoxEvent->addItem(QString::fromStdString(pVecEventAll[i]->GetEventName()));
        }
        auto* pLineEditName = new QLineEdit(pDialogModify);
        auto* pLineEditDate = new QLineEdit(pDialogModify);
        auto* pLineEditLocation = new QLineEdit(pDialogModify);
        // Connect the combobox's currentTextChanged signal
        QObject::connect(pComboBoxEvent, static_cast<void(QComboBox::*)(const QString&)>(&QComboBox::currentTextChanged), [&](const QString& _insSelectedText) {
                // Find the corresponding event in the events vector
                for (const Event* pEventWanted : pVecEventAll) {
                    if (QString::fromStdString(pEventWanted->GetEventName()) == _insSelectedText) {
                        // Update input fields with the values of the selected event
                        pLineEditName->setText(_insSelectedText);
                        pLineEditDate->setText(QString::fromStdString(pEventWanted->GetEventDate()));
                        pLineEditLocation->setText(QString::fromStdString(pEventWanted->GetEventLocation()));
                        break;
                    }
                }
            });
            emit pComboBoxEvent->currentTextChanged(pComboBoxEvent->currentText());
            pFormLayoutDialog->addRow("Nom de l'événement:", pComboBoxEvent);
            pFormLayoutDialog->addRow("Nouveau nom de l'événement:", pLineEditName);
            pFormLayoutDialog->addRow("Nouvelle date de l'événement:", pLineEditDate);
            pFormLayoutDialog->addRow("Nouveau lieu de l'événement:", pLineEditLocation);
            auto* pPushButtonModify = new QPushButton("Modifier", pDialogModify);
            pFormLayoutDialog->addRow("", pPushButtonModify);
            // Connect the "Modify" button to a processing function
            QObject::connect(pPushButtonModify, &QPushButton::clicked, [&]() {
            // Retrieve the values entered in the fields
            unsigned int nIndexOfTheEventToModify = pComboBoxEvent->currentIndex();
            QString sName = pLineEditName->text();
            QString sDate = pLineEditDate->text();
            QString sLocation = pLineEditLocation->text();
            if (sName.isEmpty() || sLocation.isEmpty()) {
                QMessageBox::warning(nullptr, "Attention !", "Veuillez remplir tous les champs.");
            }
            else {
                // Create a new event with the retrieved values
                Event* pEventModify = new Event(sName.toStdString(), sDate.toStdString(), sLocation.toStdString());

                // Use the created event to modify the JSON
                ModifyEvent(pEventModify, nIndexOfTheEventToModify);
                QMessageBox::information(nullptr, "Succès !", "L'événement a bien été modifié.");
                // Close the edit dialog box
                pDialogModify->close();
                delete pDialogModify;
            }
        });
        pDialogModify->exec();
    }
}

void GestionEvenementDialog::DeleteEventDialog() {
    QDialog pDialogDelete(this);
    pDialogDelete.setWindowTitle("Supprimer un événement");

    std::vector<Event> vecEvents;
    json jsonData;
    std::ifstream ifstreamData(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation).toStdString() + "/data.json");
    ifstreamData >> jsonData;
    ifstreamData.close();
    const json& eventsJson = jsonData["events"];
    if (eventsJson.size() == 0) {
        QMessageBox::warning(nullptr, "Attention !", "Aucun événement n'a été trouvé.");
    }
    else {
        for (json::const_iterator it = eventsJson.begin(); it != eventsJson.end(); ++it) {
            Event event(it.value()["nom"], it.value()["date"], it.value()["lieu"]);
            vecEvents.push_back(event);
        }

        QFormLayout formLayoutMain(&pDialogDelete);

        // Add the fields required to delete an event
        auto *pComboBoxEvent = new QComboBox(&pDialogDelete);
        for (int i = 0; i < vecEvents.size(); i++) {
            pComboBoxEvent->addItem(QString::fromStdString(vecEvents[i].GetEventName()));
        }

        formLayoutMain.addRow("Nom de l'événement:", pComboBoxEvent);

        auto *supprimerButton = new QPushButton("Supprimer", &pDialogDelete);
        formLayoutMain.addRow("", supprimerButton);

        // Connect the "Delete" button to a processing function
        QObject::connect(supprimerButton, &QPushButton::clicked, [&]() {
            // Retrieve the values entered in the fields
            unsigned int nIndexOfTheEventToDelete = pComboBoxEvent->currentIndex();
            // Use the existing Event object to modify the JSON
            DeleteEvent(&vecEvents[nIndexOfTheEventToDelete], nIndexOfTheEventToDelete);
            emit DataModified();
            QMessageBox::information(nullptr, "Succès !", "L'événement a bien été supprimé.");
            // Close the delete dialog box
            pDialogDelete.close();
        });
        pDialogDelete.exec();
    }
}