#ifndef WINDOWVIEWMEDECIN_H
#define WINDOWVIEWMEDECIN_H

#include "mainwindow.h"
#include "tablemodelpatient.h"

class WindowViewMedecin : public QWidget
{
    Q_OBJECT

    public:
        WindowViewMedecin(MainWindow *parent);
        void saveAllInfosFromLine(int line);

    public slots:
        void addPatient();
        void addPatientOK();
        void modifyPatient();
        void modifyPatientOK();
        void supprPatient();
        void supprPatientOK();
        void actualiser();
        void saveTextNom(QString str);
        void saveTextPrenom(QString str);
        void saveTextSpec(QString str);
        void saveTextAM(QString str);
        void saveTextRPPS(QString str);
        void saveTextRue1(QString str);
        void saveTextRue2(QString str);
        void saveTextCodeP(QString str);
        void saveTextVille(QString str);
        void saveTextTel(QString str);
        void saveTextMail(QString str);
        void saveTextFax(QString str);
        void saveSelectedRow(const QModelIndex &index);

    private:
        TableModelPatient *model;
        QTableView *view;
        int _numFile;

        int selectedTableRow;
        MainWindow *parent_t;

        QString strNom;
        QString strPrenom;
        QString strSpec;
        QString strAM;
        QString strRPPS;
        QString strRue1;
        QString strRue2;
        QString strCodeP;
        QString strVille;
        QString strTel;
        QString strMail;
        QString strFax;
};

#endif // WINDOWVIEWMEDECIN_H
