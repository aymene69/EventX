#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QGroupBox>
#include <QVBoxLayout>
#include "include/GestionEvenement.hpp"
#include "include/GestionParticipant.hpp"
#include "include/GestionStand.hpp"
#include "include/GestionManager.hpp"

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

signals:
    void dataModified();

private slots:
    void handleGestionEvenement();
    void handleGestionParticipant();
    void handleGestionStand();
    void handleGestionManager();
    void handleDataModified();

private:
    void createWidgets();
    void createLayout();
    void connectSignalsAndSlots();

    GestionEvenementDialog gestionEvenementDialog;
    GestionParticipantDialog gestionParticipantDialog;
    GestionStandDialog gestionStandDialog;
    GestionManagerDialog gestionManagerDialog;

    QLabel* pLabelNumberEvents;
    QLabel* pLabelNumberParticipants;
    QLabel* pLabelNumberStands;
    QLabel* pLabelNumberManagers;
    QPushButton* pPushButtonManageEvent;
    QPushButton* pPushButtonManageParticipant;
    QPushButton* pPushButtonManageStand;
    QPushButton* pPushButtonManageManager;
    QPushButton* pPushButtonViewData;
    QPushButton* pPushButtonExit;
    QVBoxLayout* pViewDataLayout;

public slots:
    void viewData();
};

#endif // MAINWINDOW_HPP
