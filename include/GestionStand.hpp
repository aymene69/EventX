#ifndef GESTIONSTAND_HPP
#define GESTIONSTAND_HPP

#include <QDialog>
#include <QComboBox>

class GestionStandDialog : public QDialog {
Q_OBJECT

public:
    GestionStandDialog(QWidget *parent = nullptr);

signals:
    void dataModified();

public slots:
    void creerStand();
    void modifierStand();
    void supprimerStand();

private slots:
    void onEventComboBoxChanged(int index);

private:
    QComboBox *eventComboBox;
    QComboBox *standComboBox;
};

#endif // GESTIONEVENEMENT_HPP
