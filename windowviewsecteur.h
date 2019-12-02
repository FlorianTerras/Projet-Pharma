#ifndef WINDOWVIEWSECTEUR_H
#define WINDOWVIEWSECTEUR_H


#include "mainwindow.h"
#include "tablemodel.h"

class WindowViewSecteur : public QWidget
{
    Q_OBJECT

    public:
        WindowViewSecteur(MainWindow *parent);

    private slots:
        void addSecteur();
        void addSecteurOK();
        void supprSecteur();
        void supprSecteurOK();
        void saveCboxIndex(int index);
        void saveTextNom(QString str);
        void getSelectedRow(const QModelIndex &index);
        void getSelectedCol(const QModelIndex &index);
        void actualiser();

    private:
        int selectedTableRow;
        int selectedTableCol;
        TableModel *model;
        QTableView *view;

        int cboxIndex;
        QString strNom;

        MainWindow *parent_t;
};


#endif // WINDOWVIEWSECTEUR_H
