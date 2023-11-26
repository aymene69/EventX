#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QGroupBox>
#include "include/GestionEvenement.hpp"
#include "include/GestionParticipant.hpp"
#include "include/GestionStand.hpp"
#include "include/GestionManager.hpp"
#include "include/ViewData.hpp"

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void handleGestionEvenement();
    void handleGestionParticipant();
    void handleGestionStand();
    void handleGestionManager();
    void handleDataModified();
    void visualiser();

private:
    void createWidgets();
    void createLayout();
    void connectSignalsAndSlots();

    GestionEvenementDialog gestionEvenementDialog;
    GestionParticipantDialog gestionParticipantDialog;
    GestionStandDialog gestionStandDialog;
    GestionManagerDialog gestionManagerDialog;
    ViewData viewDataDialog;


    QLabel *nombreEvenementsLabel;
    QLabel *nombreParticipantsLabel;
    QLabel *nombreStandsLabel;
    QLabel *nombreManagersLabel;
    QPushButton *gererEvent;  // Déclaration des boutons ici
    QPushButton *gererParticipant;
    QPushButton *gererStand;
    QPushButton *gererManager;


    QPushButton *viewData;
    QPushButton *quitter;
};

#endif // MAINWINDOW_HPP
