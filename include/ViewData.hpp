#ifndef VIEWDATA_HPP
#define VIEWDATA_HPP

#include <QFormLayout>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QTreeView>

#include "nlohmann/json.hpp"
#include "include/FonctionsDemarrage.hpp"

class ViewData : public QDialog {
    Q_OBJECT

public:
    ViewData(QWidget* parent = nullptr);

};

#endif // VIEWDATA_HPP
