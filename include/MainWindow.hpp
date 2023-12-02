#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QStandardPaths>
#include <QObject>
#include <QStandardItemModel>
#include <QTreeView>
#include <QMessageBox>
#include "include/GestionEvenement.hpp"
#include "include/GestionParticipant.hpp"
#include "include/GestionStand.hpp"
#include "include/GestionManager.hpp"
#include "include/FonctionsJson.hpp"
#include "include/FonctionsDemarrage.hpp"


class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

signals:
    void DataModified();

private slots:
    void HandleGestionEvenement();
    void HandleGestionParticipant();
    void HandleGestionStand();
    void HandleGestionManager();
    void HandleDataModified();

private:
    void CreateWidgets();
    void CreateLayout();
    void ConnectSignalsAndSlots();

    GestionEvenementDialog m_gestionEvenementDialog;
    GestionParticipantDialog m_gestionParticipantDialog;
    GestionStandDialog m_gestionStandDialog;
    GestionManagerDialog m_gestionManagerDialog;

    QLabel* m_pLabelNumberEvents;
    QLabel* m_pLabelNumberParticipants;
    QLabel* m_pLabelNumberStands;
    QLabel* m_pLabelNumberManagers;
    QPushButton* m_pPushButtonManageEvent;
    QPushButton* m_pPushButtonManageParticipant;
    QPushButton* m_pPushButtonManageStand;
    QPushButton* m_pPushButtonManageManager;
    QPushButton* m_pPushButtonViewData;
    QPushButton* m_pPushButtonExit;
    QVBoxLayout* m_pViewDataLayout;

public slots:
    void ViewData();
};

#endif // MAINWINDOW_HPP
