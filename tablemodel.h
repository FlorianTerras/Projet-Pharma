//Modèle pour affichage de la liste des groupes

#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>

class TableModel : public QAbstractTableModel
{
   Q_OBJECT

    public:
        TableModel(QObject *parent = nullptr);
        void populateData(const QStringList &listeGroupe, const QVector<QStringList> &tabListeSecteur);
        int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
        int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
        QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;

    private:
        QStringList tm_listeGroupe;
        QVector<QStringList> tm_tabListeSecteur;
};

#endif // TABLEMODEL_H
