#ifndef GESTIONEVENEMENT_HPP
#define GESTIONEVENEMENT_HPP

#include <QDialog>
#include "include/FonctionsJson.hpp"

class GestionEvenementDialog : public QDialog {
Q_OBJECT

public:
    GestionEvenementDialog(QWidget *parent = nullptr);

public slots:
    void creerEvenement();
    void modifierEvenement();
    void supprimerEvenement();
};

#endif // GESTIONEVENEMENT_HPP
