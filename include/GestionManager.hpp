#ifndef GESTIONMANAGER_HPP
#define GESTIONMANAGER_HPP

#include <QDialog>
#include <QComboBox>

class GestionManagerDialog : public QDialog {
Q_OBJECT

public:
    GestionManagerDialog(QWidget *parent = nullptr);

signals:
    void dataModified();

public slots:
    void creerManager();
    void modifierManager();
    void supprimerManager();

private slots:
    void onEventComboBoxChanged(int index);
    void onStandComboBoxChanged(int index);

private:
    QComboBox *eventComboBox;
    QComboBox *standComboBox;
    QComboBox *managComboBox;
};

#endif // GESTIONEVENEMENT_HPP
