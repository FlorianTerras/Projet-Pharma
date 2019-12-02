//Modèle pour affichage de la liste des patients

#ifndef TABLEMODELPATIENT_H
#define TABLEMODELPATIENT_H

#include <QAbstractTableModel>

class TableModelPatient : public QAbstractTableModel
{
    Q_OBJECT

     public:
         TableModelPatient(QObject *parent = nullptr);

         void populateData(const QString &str);

         int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
         int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;

         QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
         QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;

     private:
         QStringList tm_strList;
};

#endif // TABLEMODELPATIENT_H
