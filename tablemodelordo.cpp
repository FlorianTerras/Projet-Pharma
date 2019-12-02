#include "tablemodelordo.h"

#include <QDebug>

TableModelOrdo::TableModelOrdo(QObject *parent) : QAbstractTableModel(parent)
{
    checkState = new QList<int>;
}

// Create a method to populate the model with data:
void TableModelOrdo::populateData(const QString &str)
{
    tm_strList = str.split("\n");
    for (int i = 0; i < tm_strList.length(); i++)
    {
        checkState->append(Qt::Unchecked);
    }
    return;
}

int TableModelOrdo::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return (tm_strList.length() - 2);
}

int TableModelOrdo::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return (((tm_strList.value(0)).split(";")).length() - 1);
}

QVariant TableModelOrdo::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.column() == 10 && role == Qt::CheckStateRole)
    {
        return (checkState->value(index.row()));
    }
    if (index.column() != 10 && (role == Qt::DisplayRole || role == Qt::EditRole)) {
        return (tm_strList.value(index.row() + 1)).split(";").value(index.column());
    }
    return QVariant();
}

QVariant TableModelOrdo::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
            return (tm_strList.value(0)).split(";").value(section);
    }
    if (role == Qt::DisplayRole && orientation == Qt::Vertical) {
        return section;
    }
    return QVariant();
}

bool TableModelOrdo::setData(const QModelIndex &index, const QVariant &value, int role)
{
    QString str = tm_strList.value(index.row() + 1);
    QStringList strlist = str.split(";");
    if (!index.isValid())
        return (false);
    if (role == Qt::EditRole) {
        strlist.replace(index.column(), value.toString());
        str.clear();
        for (int i = 0; i < strlist.length(); i++)
        {
            if (i < columnCount()) {
                str.append(strlist.value(i));
                str.append(";");
            }
        }
        tm_strList.replace(index.row() + 1, str);
        emit dataChanged(index, index);
        emit layoutChanged();
        return true;
    }
    else if(role == Qt::CheckStateRole)
    {
        if (checkState->value(index.row()) == Qt::Checked) {
            checkState->replace(index.row(), Qt::Unchecked);
        } else if (checkState->value(index.row()) == Qt::Unchecked) {
            checkState->replace(index.row(), Qt::Checked);
        }
        emit dataChanged(index,index);
        return true;
    }
    return false;
}

Qt::ItemFlags TableModelOrdo::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;
    if (index.column() == 10)
        return QAbstractItemModel::flags(index) | Qt::ItemIsUserCheckable;
    else
        return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

QString TableModelOrdo::getData()
{
    QString str;

    for (int i = 0; i < tm_strList.length() - 1; i++)
    {
        str.append(tm_strList.value(i));
        str.append("\n");
    }
    return (str);
}
