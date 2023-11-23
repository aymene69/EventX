#ifndef GESTIONPARTICIPANT_HPP
#define GESTIONPARTICIPANT_HPP

#include <QDialog>
#include <QComboBox>

class GestionParticipantDialog : public QDialog {
Q_OBJECT

signals:
    void dataModified();

public:
    GestionParticipantDialog(QWidget *parent = nullptr);

public slots:
    void creerParticipant();
    void modifierParticipant();
    void supprimerParticipant();

private slots:
    void onEventComboBoxChanged(int index);

private:
    QComboBox *eventComboBox;
    QComboBox *participantComboBox;
};

#endif
