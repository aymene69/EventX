#ifndef GESTIONMANAGER_HPP
#define GESTIONMANAGER_HPP

#include <QDialog>
#include <fstream>
#include <QFormLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QMessageBox>
#include <QLabel>
#include <QCheckBox>
#include <QStandardPaths>
#include "nlohmann/json.hpp"
#include "include/Event.hpp"
#include "include/Stand.hpp"
#include "include/Manager.hpp"
#include "include/FonctionsJson.hpp"
#include "include/FonctionsDemarrage.hpp"

class GestionManagerDialog : public QDialog {
Q_OBJECT

public:
    GestionManagerDialog(QWidget *parent = nullptr);

signals:
    void DataModified();

public slots:
    void CreateManagerDialog();
    void ModifyManagerDialog();
    void DeleteManagerDialog();

private slots:
    void onEventComboBoxChanged(int index);
    void onStandComboBoxChanged(int index);

private:
    QComboBox *m_pComboBoxEvent;
    QComboBox *m_pComboBoxStand;
    QComboBox *m_pComboBoxManager;
};

#endif // GESTIONEVENEMENT_HPP
