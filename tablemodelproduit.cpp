#include "tablemodelproduit.h"
#include <QDebug>

TableModelProduit::TableModelProduit(QObject *parent) : QAbstractTableModel(parent)
{
}

// Create a method to populate the model with data:
void TableModelProduit::populateData(const QString &str)
{
    tm_strList = str.split("\n");
    return;
}

int TableModelProduit::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return (tm_strList.length() - 1);
}

int TableModelProduit::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return ((tm_strList.value(0)).split(";")).length();
}

QVariant TableModelProduit::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole) {
        return QVariant();
    }
    return (tm_strList.value(index.row())).split(";").value(index.column());
}

QVariant TableModelProduit::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        if (section == 0)
            return ("Prénom Nom du Patient");
        else if (section == 1)
            return ("Groupe (Maison de retraite)");
        else if (section == 2)
            return ("Secteur");
    }
    if (role == Qt::DisplayRole && orientation == Qt::Vertical) {
        return section;
    }
    return QVariant();
}
