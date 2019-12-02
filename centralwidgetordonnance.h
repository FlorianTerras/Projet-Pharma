#ifndef CENTRALWIDGETORDONNANCE_H
#define CENTRALWIDGETORDONNANCE_H

#include "mainwindow.h"
#include "tablemodelordo.h"

class CentralWidgetOrdonnance : public QWidget
{
    Q_OBJECT
    public:
        CentralWidgetOrdonnance(MainWindow *parent);
        QWidget *createInfoWidget();    //creer la barre d'informations
        QWidget *createListWidget();    //creer la liste de produit de l'ordonnance
        QWidget *createHistoryWidget(); //creer l'historique d'ordonnance
        void fillListeProduit();    //remplit la liste de produit pour le QCompleter
        QStringList *getListeProduit(); //retourne listeProduit
        void writeFile(QString str);    //enregistre l'ordonnance que l'on vient de creer

    private slots:
        void addProduit();
        void actualiserList(const QModelIndex &index);  //actualise la liste affiché et rajoute une ligne si il faut
        void saveDateDebut(const QDate &date);  //enregistre la variable dateDebut
        void saveStrDuree(const QString &str);  //       [...]           saveDuree
        void changeDateFin();   //actualise la date de fin pour qu'elle corresponde à la date de début et à la durée
        void valider(); //valide l'ordonnance et l'enregistre

    private:

        QDate *datePrescr;
        QDate *dateDebut;
        QDate *dateFin;
        QString strDuree;

        QLineEdit *lineEditDateFin;

        QStringList *listeProduit;
        QStringList *listeCodePrdt;

        QTemporaryFile *tmpFile;
        TableModelOrdo *model;
        QTableView *tableView;
        MainWindow *parent_t;
};

#endif // CENTRALWIDGETORDONNANCE_H