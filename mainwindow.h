#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow();
        QString getStrFile(QString filename);   //retourne le QString contenu dans le fichier "filename"
        QString getFilename(int n); //retourne le nom du fichier demandé. n : 0=groupe | 1=patient | 2=produits
        QStringList *getListeGroupe();  //retourne la liste des groupes
        QVector<QStringList> *getTabListeSecteur(); //retourne la liste des secteurs en fonction de leur groupe
        QVector<QVector<QStringList>> *getTabListePatient();    //retourne la liste des patients en fonction de leur groupe et secteur
        QStringList getSelectedPatient();   //retourne les infos du patient selectionné

    public slots:
        void actualiser();  //relis les fichiers et actualise l'affichage

    private slots:
        void save();
        void undo();
 //       void about();
        void changeListPatients();  //actualise la liste de patient affiché par rapport au groupe et au secteur sélectionné
        void changeListSecteur();   //actualise la liste de secteur par rapport au groupe selectionné
        void toggleFullscreen(bool);    //Mettre l'application en plein-écran ou non
        void createListes();    //creer les listes et les remplis
        void voirGroupe();  //creer une fenêtre permettant d'ajouter/supprimer des groupes
        void voirSecteur(); //creer une fenêtre permettant d'ajouter/supprimer des secteurs
        void voirPatient(); //creer une fenêtre permettant d'ajouter/modifier/supprimer des patients
        void voirProduit(); //creer une fenêtre permettant d'afficher la liste des produits
        void createOrdo();  //creer le widget ordonnance et le met en tant que widget central

    private:
        void createActions();
        void createMenus(); //creer les menu en haut de la fenêtre
        void createStatusBar();
        void createDockWindows(); //creer les docks sur le coté droit
        void readFileData();    //lis les fichier et remplis les listes
        void fillGroupeStringList(QString str); // remplis la liste des groupes et des secteurs
        void fillPatientStringList(QString line2);  // remplis la liste des patients

        QAction *actionQuitter;

        QListWidget *groupeList;
        QListWidget *secteurList;
        QListWidget *patientsList;

        QStringList *listeGroupe;
        QVector<QStringList> *tabListeSecteur;
        QVector<QVector<QStringList>> *tabListePatient;

        QMenu *viewMenu;

        QString filenameGroupe;
        QString filenamePatients;
        QString filenameProduits;
};

#endif // MAINWINDOW_H
