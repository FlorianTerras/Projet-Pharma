#ifndef WINDOWVIEWPATIENT_H
#define WINDOWVIEWPATIENT_H

#include "mainwindow.h"
#include "tablemodelpatient.h"

class WindowViewPatient : public QWidget
{
    Q_OBJECT

    public:
        WindowViewPatient(MainWindow *parent, int numFile = 1);
        void saveAllInfosFromLine(int line);
        int getIndex(QString str);
        int getIndex2(QString str);

    public slots:
        void addPatient();
        void addPatientOK();
        void modifyPatient();
        void modifyPatientOK();
        void supprPatient();
        void supprPatientOK();
        void actualiser();
        void changeCboxSecteur();
        void saveCboxIndex(int currentRow);
        void saveCboxIndex2(int currentRow);
        void saveTextNom(QString str);
        void saveTextPrenom(QString str);
        void saveTextInsee(QString str);
        void saveTextSexe(QString str);
        void saveTextNomJF(QString str);
        void saveTextRue1(QString str);
        void saveTextRue2(QString str);
        void saveTextCodeP(QString str);
        void saveTextVille(QString str);
        void saveTextDateN(QString str);
        void saveTextDateD(QString str);
        void saveSelectedRow(const QModelIndex &index);
        int getSelectedTableRow();

    private:
        TableModelPatient *model;
        QTableView *view;
        int _numFile;

        int selectedTableRow;
        MainWindow *parent_t;

        QComboBox *cboxSecteur;

        int cboxIndex;
        int cboxIndex2;

        QString strDateN;
        QString strNom;
        QString strPrenom;
        QString strInsee;
        QString strSexe;
        QString strDateD;
        QString strNomJF;
        QString strRue1;
        QString strRue2;
        QString strCodeP;
        QString strVille;
};
#endif // WINDOWVIEWPATIENT_H
