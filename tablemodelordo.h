//Modèle pour affichage de la liste des produits de l'ordonnance

#ifndef TABLEMODELORDO_H
#define TABLEMODELORDO_H

#include <QAbstractTableModel>

class TableModelOrdo : public QAbstractTableModel
{
    Q_OBJECT

     public:
         TableModelOrdo(QObject *parent = nullptr);

         void populateData(const QString &str);
         int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
         int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;

         QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
         QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
         Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
         bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) Q_DECL_OVERRIDE;
    public slots:
         QString getData();

    private:
         QStringList tm_strList;
         QList<int> *checkState;
};

#endif // TABLEMODELORDO_H
