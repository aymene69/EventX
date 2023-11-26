/********************************************************************
    created:	2023-11-22
    file path:	include/GestionEvenement.hpp
    author:		W.I.P.
    copyright:	UNLICENSE

    purpose: W.I.P.
*********************************************************************/

#ifndef GESTIONEVENEMENT_HPP
#define GESTIONEVENEMENT_HPP

#include <QDialog>
#include "include/FonctionsJson.hpp"

class GestionEvenementDialog : public QDialog {
Q_OBJECT

public:
    GestionEvenementDialog(QWidget *parent = nullptr);

signals:
    void dataModified();

public slots:
    void creerEvenement();
    void modifierEvenement();
    void supprimerEvenement();
};

#endif // GESTIONEVENEMENT_HPP
