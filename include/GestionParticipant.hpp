#ifndef GESTIONPARTICIPANT_HPP
#define GESTIONPARTICIPANT_HPP

#include <QDialog>
#include "include/FonctionsJson.hpp"

class GestionParticipantDialog : public QDialog {
Q_OBJECT

public:
    GestionParticipantDialog(QWidget *parent = nullptr);

public slots:
    void creerParticipant();
    void modifierParticipant();
};

#endif
