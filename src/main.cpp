/********************************************************************
    created:	2023-11-W.I.P.
    file path:	src/main.cpp
    author:		W.I.P.
    copyright:	UNLICENSE

    purpose: Call the main window
*********************************************************************/

#include <QApplication>
#include "include/MainWindow.hpp"

#ifdef Q_OS_WIN
int WinMain(int argc, char *argv[]) {
#else
int main(int argc, char *argv[]) {
#endif
    QApplication eventX(argc, argv);
    MainWindow mainWindow;
    mainWindow.setWindowTitle("EventX 1.0");
    mainWindow.show();
    return QApplication::exec();
}