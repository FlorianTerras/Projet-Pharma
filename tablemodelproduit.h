#ifndef TABLEMODELPRODUIT_H
#define TABLEMODELPRODUIT_H


#include <QAbstractTableModel>

class TableModelProduit : public QAbstractTableModel
{
    Q_OBJECT

     public:
         TableModelProduit(QObject *parent = nullptr);

         void populateData(const QString &str);

         int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
         int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;

         QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
         QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;

     private:
         QStringList tm_strList;
         QVector<QStringList> tm_vectorList;
};

#endif // TABLEMODELPRODUIT_H
