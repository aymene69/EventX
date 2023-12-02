#ifndef GESTIONEVENEMENT_HPP
#define GESTIONEVENEMENT_HPP
#include <QDialog>
#include <fstream>
#include <QFormLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QMessageBox>
#include <QLabel>
#include <QDateEdit>
#include <QStandardPaths>
#include "nlohmann/json.hpp"
#include "include/Event.hpp"
#include "include/Participant.hpp"
#include "include/Stand.hpp"
#include "include/Manager.hpp"
#include "include/FonctionsJson.hpp"

using json = nlohmann::json;

class GestionEvenementDialog : public QDialog {
Q_OBJECT

public:
    GestionEvenementDialog(QWidget *parent = nullptr);

signals:
    void DataModified();

public slots:
    void CreateEventDialog();
    void ModifyEventDialog();
    void DeleteEventDialog();
};

#endif // GESTIONEVENEMENT_HPP
