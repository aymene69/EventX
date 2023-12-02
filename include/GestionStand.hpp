#ifndef GESTIONSTAND_HPP
#define GESTIONSTAND_HPP

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

using json = nlohmann::json;

class GestionStandDialog : public QDialog {
    Q_OBJECT

public:
    GestionStandDialog(QWidget* parent = nullptr);

signals:
    void DataModified();

public slots:
    void CreateStandDialog();
    void ModifyStandDialog();
    void DeleteStandDialog();

private slots:
    void onEventComboBoxChanged(int index);

private:
    QComboBox* m_pComboBoxEvent;
    QComboBox* m_pComboBoxStand;
};

#endif // GESTIONEVENEMENT_HPP
