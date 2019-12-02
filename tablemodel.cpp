#include "tablemodel.h"

TableModel::TableModel(QObject *parent) : QAbstractTableModel(parent)
{
}

// Create a method to populate the model with data:
void TableModel::populateData(const QStringList &listeGroupe, const QVector<QStringList> &tabListeSecteur)
{
    tm_listeGroupe.clear();
    tm_listeGroupe = listeGroupe;
    tm_tabListeSecteur.clear();
    tm_tabListeSecteur = tabListeSecteur;
    return;
}

int TableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    int maxLength = 0;
    for(int i = 0; i < tm_listeGroupe.length();i++) {
        if (maxLength < tm_tabListeSecteur.value(i).length())
            maxLength = tm_tabListeSecteur.value(i).length();
    }
    return maxLength;
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return tm_listeGroupe.length();
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole) {
        return QVariant();
    }
    return tm_tabListeSecteur.value(index.column()).value(index.row());
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        return tm_listeGroupe.value(section);
    }
    return QVariant();
}
