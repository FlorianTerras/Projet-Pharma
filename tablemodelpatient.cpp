#include "tablemodelpatient.h"

TableModelPatient::TableModelPatient(QObject *parent) : QAbstractTableModel(parent)
{
}

// Create a method to populate the model with data:
void TableModelPatient::populateData(const QString &str)
{
    tm_strList = str.split("\n");
    return;
}

int TableModelPatient::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return (tm_strList.length() - 2);
}

int TableModelPatient::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return (((tm_strList.value(0)).split(";")).length() - 1);
}

QVariant TableModelPatient::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole) {
        return QVariant();
    }
    return (tm_strList.value(index.row() + 1)).split(";").value(index.column());
}

QVariant TableModelPatient::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
            return (tm_strList.value(0)).split(";").value(section);
    }
    if (role == Qt::DisplayRole && orientation == Qt::Vertical) {
        return section;
    }
    return QVariant();
}
