#ifndef TABLEMODELHISTORY_H
#define TABLEMODELHISTORY_H

#include <QAbstractTableModel>
#include <QColor>
#include "tablemodelordo.h"

class TableModelHistory : public QAbstractTableModel
{
    Q_OBJECT

    public:
        TableModelHistory(TableModelOrdo &modelO , QObject *parent = nullptr);
        void populateData(const QString &str);
        int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
        int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
        QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;

    public slots:
        void compare();

    private:
        QStringList tm_strList;
        TableModelOrdo *modelOrdo;
        QString strOrdo;
        bool allowColorChange;
};

#endif // TABLEMODELHISTORY_H
