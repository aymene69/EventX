#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QGroupBox>
#include "include/GestionEvenement.hpp"
#include "include/GestionParticipant.hpp"

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void handleGestionEvenement();
    void handleGestionParticipant();
    void handleDataModified();

private:
    void createWidgets();
    void createLayout();
    void connectSignalsAndSlots();

    GestionEvenementDialog gestionEvenementDialog;
    GestionParticipantDialog gestionParticipantDialog;
    QLabel *nombreEvenementsLabel;
    QLabel *nombreParticipantsLabel;
    QPushButton *gererEvent;  // Déclaration des boutons ici
    QPushButton *gererParticipant;
    QPushButton *gererStand;
    QPushButton *gererManager;

    QPushButton *visualiser;
    QPushButton *quitter;
};

#endif // MAINWINDOW_HPP
