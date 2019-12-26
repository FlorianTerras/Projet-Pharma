#include "tablemodelhistory.h"
#include <QDebug>

TableModelHistory::TableModelHistory(TableModelOrdo &modelO, QObject *parent) : QAbstractTableModel(parent)
{
    modelOrdo = &modelO;
    strOrdo = modelO.getData();
    allowColorChange = false;
}

// Create a method to populate the model with data:
void TableModelHistory::populateData(const QString &str)
{
    tm_strList = str.split("\n");
    return;
}

int TableModelHistory::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return (tm_strList.length() - 1);
}

int TableModelHistory::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return (((tm_strList.value(0)).split(";")).length() - 1);
}

QVariant TableModelHistory::data(const QModelIndex &index, int role) const
{
    if (role == Qt::BackgroundRole)
    {
        QStringList strlo = modelOrdo->getData().split("\n");
        QStringList strloSplit;
        QStringList strliSplit;

        for (int i = 1; i < strlo.length(); i++) {
            strloSplit = strlo.value(i).split(";");
            strliSplit.clear();
            strliSplit = tm_strList.value(index.row()).split(";");

            if (strloSplit.value(index.column() - 4) == strliSplit.value(index.column()) && (index.column() >= 4 && index.column() <= 5)) {
                return (QColor(137,255,102));
            } else if (strloSplit.value(index.column() - 4) == strliSplit.value(index.column()) && (index.column() >= 6 && index.column() <= 13)) {
                if (strloSplit.value(1) == strliSplit.value(5))
                    return (QColor(137,255,102));
            } else if (!strloSplit.value(index.column() - 4).isEmpty() && (index.column() >= 6 && index.column() <= 13)) {
                if (strloSplit.value(1) == strliSplit.value(5))
                   return (QColor(255,102,102));
            }
        }
        return (QColor(123,209,255));
    }
    if (!index.isValid() || role != Qt::DisplayRole) {
        return QVariant();
    }
    return (tm_strList.value(index.row())).split(";").value(index.column());
}

QVariant TableModelHistory::headerData(int section, Qt::Orientation orientation, int role) const
{
    QStringList strList;
    strList << "Médecin" << "Date préscr." << "Durée" << "Date fin"
            << "Code Produit" << "Nom Produit" << "Matin" << "Midi"
            << "Soir" << "Couché" << "??H" << "??H" << "Fréquence"
            << "Duree" << "Si Bes." << "Commentaire";
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        return (strList.value(section));
    }
    if (role == Qt::DisplayRole && orientation == Qt::Vertical) {
        return section;
    }
    return QVariant();
}

void TableModelHistory::compare()
{
    emit layoutAboutToBeChanged();
    emit layoutChanged();
}
