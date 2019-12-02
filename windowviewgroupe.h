#ifndef WINDOWVIEWGROUPE_H
#define WINDOWVIEWGROUPE_H

#include "mainwindow.h"

class WindowViewGroupe : public QWidget
{
    Q_OBJECT

    public:
        WindowViewGroupe(MainWindow *parent);   //creer la fenêtre affichant la liste des groupes

    private slots:
        void addGroupe();   //ajouter un groupe
        void supprGroupe(); //supprimer un groupe (confirmation)
        void supprGroupeOK();   //apres confirmation
        void getSelectedRow(const QModelIndex &index);  //enregistre le numéro de la ligne sélectionnée dans la variable "selectedRow"
        void actualiser();  //relis le fichier et actualise le modele

    private:
        int selectedRow;
        MainWindow *parent_t;
        QStringListModel *model;
};

#endif // WINDOWVIEWGROUPE_H
