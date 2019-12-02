#include "windowviewpatient.h"

WindowViewPatient::WindowViewPatient(MainWindow *parent)
{
    parent_t = parent;
    this->setParent(parent);
    selectedTableRow = - 1;
    QVBoxLayout *VBL = new QVBoxLayout;
    view = new QTableView(this);
    this->setWindowFlag(Qt::Window);
    this->setWindowTitle("Patients");
    this->resize(1600, 850);
    model = new TableModelPatient();
    model->populateData(parent_t->getStrFile(parent_t->getFilename(1)));
    view->setModel(model);
    view->resizeColumnsToContents();
    view->setSelectionBehavior(QAbstractItemView::SelectRows);

    QHBoxLayout *HBL = new QHBoxLayout();
    QPushButton *button_ajouter = new QPushButton("Ajouter");
    HBL->addWidget(button_ajouter);
    QPushButton *button_modifier = new QPushButton("Modifier");
    HBL->addWidget(button_modifier);
    QPushButton *button_supprimer = new QPushButton("Supprimer");
    HBL->addWidget(button_supprimer);
    HBL->setAlignment(Qt::AlignBottom);
    VBL->addWidget(view);
    VBL->addLayout(HBL);
    this->setLayout(VBL);

    connect(view, SIGNAL(clicked(const QModelIndex &)), this, SLOT(getSelectedRow(const QModelIndex &)));
    connect(button_ajouter, SIGNAL(clicked()), this, SLOT(addPatient()));
    connect(button_modifier, SIGNAL(clicked()), this, SLOT(modifyPatient()));
    connect(button_supprimer, SIGNAL(clicked()), this, SLOT(supprPatient()));
}

void WindowViewPatient::addPatient()
{
    QWidget *window = new QWidget(this, Qt::Dialog);
    window->setWindowTitle("Ajouter un patient");
    QVBoxLayout *VBL = new QVBoxLayout(window);
    QFormLayout *QFL = new QFormLayout;
    VBL->addLayout(QFL);
    QLineEdit *nom = new QLineEdit;
    QLineEdit *prenom = new QLineEdit;
    QLineEdit *DateN = new QLineEdit;
    QLineEdit *insee = new QLineEdit;
    QLineEdit *sexe = new QLineEdit;
    QLineEdit *DateD = new QLineEdit;
    QLineEdit *nomJF = new QLineEdit;
    QLineEdit *rue1 = new QLineEdit;
    QLineEdit *rue2 = new QLineEdit;
    QLineEdit *codeP = new QLineEdit;
    QLineEdit *ville = new QLineEdit;
    QFL->addRow("Nom :", nom);
    QFL->addRow("Prénom :", prenom);
    QFL->addRow("Date de naissance :", DateN);
    QFL->addRow("N° INSEE", insee);
    QFL->addRow("Sexe (M/F) :", sexe);
    QFL->addRow("Date de décès :", DateD);
    QFL->addRow("Nom de jeune fille", nomJF);
    QFL->addRow("Rue 1 :", rue1);
    QFL->addRow("Rue 2 :", rue2);
    QFL->addRow("Code Postal :", codeP);
    QFL->addRow("Ville :", ville);

    QComboBox *cboxGroupe = new QComboBox;
    cboxGroupe->addItems(*parent_t->getListeGroupe());
    QFL->addRow("Groupe :", cboxGroupe);

    cboxSecteur = new QComboBox;
    changeCboxSecteur();
    QFL->addRow("Secteur :", cboxSecteur);
    QHBoxLayout *HBL = new QHBoxLayout;
    VBL->addSpacing(20);
    VBL->addLayout(HBL);
    QPushButton *buttonOk = new QPushButton("OK");
    QPushButton *buttonAnnuler = new QPushButton("Annuler");
    buttonOk->setFixedSize(120, 30);
    buttonAnnuler->setFixedSize(120, 30);
    HBL->addWidget(buttonAnnuler);
    HBL->addWidget(buttonOk);
    HBL->setAlignment(Qt::AlignBottom | Qt::AlignRight);
    window->show();
    cboxIndex = 0;
    cboxIndex2 = 0;
    changeCboxSecteur();
    window->resize(600, 550);

    connect(cboxGroupe, SIGNAL(currentIndexChanged(int)), this, SLOT(saveCboxIndex(int)));
    connect(cboxSecteur, SIGNAL(currentIndexChanged(int)), this, SLOT(saveCboxIndex2(int)));
    connect(cboxGroupe, SIGNAL(currentIndexChanged(int)), this, SLOT(changeCboxSecteur()));
    connect(nom, SIGNAL(textChanged(QString)), this, SLOT(saveTextNom(QString)));
    connect(prenom, SIGNAL(textChanged(QString)), this, SLOT(saveTextPrenom(QString)));
    connect(insee, SIGNAL(textChanged(QString)), this, SLOT(saveTextInsee(QString)));
    connect(sexe, SIGNAL(textChanged(QString)), this, SLOT(saveTextSexe(QString)));
    connect(nomJF, SIGNAL(textChanged(QString)), this, SLOT(saveTextNomJF(QString)));
    connect(DateN, SIGNAL(textChanged(QString)), this, SLOT(saveTextDateN(QString)));
    connect(DateD, SIGNAL(textChanged(QString)), this, SLOT(saveTextDateD(QString)));
    connect(rue1, SIGNAL(textChanged(QString)), this, SLOT(saveTextRue1(QString)));
    connect(rue2, SIGNAL(textChanged(QString)), this, SLOT(saveTextRue2(QString)));
    connect(codeP, SIGNAL(textChanged(QString)), this, SLOT(saveTextCodeP(QString)));
    connect(ville, SIGNAL(textChanged(QString)), this, SLOT(saveTextVille(QString)));
    connect(buttonOk, SIGNAL(clicked()), this, SLOT(addPatientOK()));
    connect(buttonOk, &QPushButton::clicked, window, &QWidget::close);
    connect(buttonOk, SIGNAL(clicked()), parent_t, SLOT(actualiser()));
    connect(buttonOk, SIGNAL(clicked()), this, SLOT(actualiser()));
    connect(buttonAnnuler, &QPushButton::clicked, window, &QWidget::close);
}

void WindowViewPatient::modifyPatient()
{
    QWidget *window = new QWidget(this, Qt::Dialog);
    QVBoxLayout *VBL = new QVBoxLayout(window);
    QFormLayout *QFL = new QFormLayout;
    QLineEdit *nom = new QLineEdit;
    QLineEdit *prenom = new QLineEdit;
    QLineEdit *DateN = new QLineEdit;
    QLineEdit *insee = new QLineEdit;
    QLineEdit *sexe = new QLineEdit;
    QLineEdit *DateD = new QLineEdit;
    QLineEdit *nomJF = new QLineEdit;
    QLineEdit *rue1 = new QLineEdit;
    QLineEdit *rue2 = new QLineEdit;
    QLineEdit *codeP = new QLineEdit;
    QLineEdit *ville = new QLineEdit;
    QComboBox *cboxGroupe = new QComboBox;
    QHBoxLayout *HBL = new QHBoxLayout;
    QPushButton *buttonOk = new QPushButton("OK");
    QPushButton *buttonAnnuler = new QPushButton("Annuler");

    if (selectedTableRow >= 0) {
        saveAllInfosFromLine(selectedTableRow + 1);
        window->setWindowTitle("Modifier un patient");
        nom->setText(strNom);
        QFL->addRow("Nom :",nom);
        prenom->setText(strPrenom);
        QFL->addRow("Prénom :", prenom);
        DateN->setText(strDateN);
        QFL->addRow("Date de naissance :", DateN);
        insee->setText(strInsee);
        QFL->addRow("N° Insee :", insee);
        sexe->setText(strSexe);
        QFL->addRow("Sexe :", sexe);
        DateD->setText(strDateD);
        QFL->addRow("Date de décès :", DateD);
        nomJF->setText(strNomJF);
        QFL->addRow("Nom de Jeune F. :", nomJF);
        rue1->setText(strRue1);
        QFL->addRow("Rue 1 :", rue1);
        rue2->setText(strRue2);
        QFL->addRow("Rue 2 :", rue2);
        codeP->setText(strCodeP);
        QFL->addRow("Code Postal :", codeP);
        ville->setText(strVille);
        QFL->addRow("Ville :", ville);
        cboxIndex = getIndex(parent_t->getStrFile(parent_t->getFilename(1)).split("\n").value(selectedTableRow+1).split(";").value(11));
        cboxIndex2 = getIndex2(parent_t->getStrFile(parent_t->getFilename(1)).split("\n").value(selectedTableRow+1).split(";").value(12));
        cboxGroupe->addItems(*parent_t->getListeGroupe());
        QFL->addRow("Groupe :", cboxGroupe);
        cboxSecteur = new QComboBox;
        changeCboxSecteur();
        cboxGroupe->setCurrentIndex(cboxIndex);
        QFL->addRow("Secteur :", cboxSecteur);
        cboxSecteur->setCurrentIndex(cboxIndex2);
        VBL->addLayout(QFL);
        VBL->addSpacing(20);
        VBL->addLayout(HBL);
        buttonOk->setFixedSize(120, 30);
        buttonAnnuler->setFixedSize(120, 30);
        HBL->addWidget(buttonAnnuler);
        HBL->addWidget(buttonOk);
        HBL->setAlignment(Qt::AlignBottom | Qt::AlignRight);
        window->resize(600, 550);
        window->show();
    } else {
        QMessageBox::warning(window, "Erreur", "Veuillez selectionner un patient");
        return;
    }
    connect(cboxGroupe, SIGNAL(currentIndexChanged(int)), this, SLOT(saveCboxIndex(int)));
    connect(cboxSecteur, SIGNAL(currentIndexChanged(int)), this, SLOT(saveCboxIndex2(int)));
    connect(nom, SIGNAL(textChanged(QString)), this, SLOT(saveTextNom(QString)));
    connect(prenom, SIGNAL(textChanged(QString)), this, SLOT(saveTextPrenom(QString)));
    connect(insee, SIGNAL(textChanged(QString)), this, SLOT(saveTextInsee(QString)));
    connect(sexe, SIGNAL(textChanged(QString)), this, SLOT(saveTextSexe(QString)));
    connect(DateN, SIGNAL(textChanged(QString)), this, SLOT(saveTextDateN(QString)));
    connect(DateD, SIGNAL(textChanged(QString)), this, SLOT(saveTextDateD(QString)));
    connect(nomJF, SIGNAL(textChanged(QString)), this, SLOT(saveTextNomJF(QString)));
    connect(rue1, SIGNAL(textChanged(QString)), this, SLOT(saveTextRue1(QString)));
    connect(rue2, SIGNAL(textChanged(QString)), this, SLOT(saveTextRue2(QString)));
    connect(codeP, SIGNAL(textChanged(QString)), this, SLOT(saveTextCodeP(QString)));
    connect(ville, SIGNAL(textChanged(QString)), this, SLOT(saveTextVille(QString)));
    connect(cboxGroupe, SIGNAL(currentIndexChanged(int)), this, SLOT(changeCboxSecteur()));
    connect(buttonOk, SIGNAL(clicked()), this, SLOT(modifyPatientOK()));
    connect(buttonOk, SIGNAL(clicked()), parent_t, SLOT(actualiser()));
    connect(buttonOk, SIGNAL(clicked()), this, SLOT(actualiser()));
    connect(buttonOk, &QPushButton::clicked, window, &QWidget::close);
    connect(buttonAnnuler, &QPushButton::clicked, window, &QWidget::close);
}

void WindowViewPatient::supprPatient()
{
    QMessageBox msgBox(this);
    if (selectedTableRow >= 0)
    {
        msgBox.setText("Ce patient va être supprimé : "
                       + parent_t->getStrFile(parent_t->getFilename(1)).split("\n").value(selectedTableRow+1).split(";").value(1)
                       + " " + parent_t->getStrFile(parent_t->getFilename(1)).split("\n").value(selectedTableRow+1).split(";").value(2));
        msgBox.setInformativeText("Etes vous sûr ?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);
        int ret = msgBox.exec();

        switch (ret) {
            case QMessageBox::Yes:
                supprPatientOK();
                parent_t->actualiser();
                actualiser();
                break;
            case QMessageBox::No:
                msgBox.close();
                return;
            default:
                return;
        }
    } else {
        QMessageBox::warning(this, "Erreur", "Veuillez selectionner un patient");
        return;
    }
}

void WindowViewPatient::addPatientOK()
{
    QString str = parent_t->getStrFile(parent_t->getFilename(1));
    if (!strNom.isEmpty() && !strPrenom.isEmpty())
    {
        str.append(strDateN +";");// Date de naissance
        str.append(strNom + ";"); // Nom
        str.append(strPrenom + ";"); // Prénom
        str.append(strInsee + ";");//N° INSEE
        str.append(strSexe + ";");//Sexe
        str.append(strDateD + ";");//Date Deces
        str.append(strNomJF + ";");//Nom de jeune fille
        str.append(strRue1 + ";");//Rue1
        str.append(strRue2 + ";");//Rue2
        str.append(strCodeP + ";");//Code Postal
        str.append(strVille + ";");//Ville
        str.append (parent_t->getListeGroupe()->value(cboxIndex) + ";"); //Groupe
        str.append(parent_t->getTabListeSecteur()->value(cboxIndex).value(cboxIndex2) + ";"); //Secteur
        str.append(";");//Etat
        str.append(";");//Photo
        str.append(";");//Broyage
        str.append("\n");
//        qDebug() << str;
        QFile file(parent_t->getFilename(1));
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::critical(this, "Erreur", "Impossible d'ouvrir " + file.fileName());
            return;
        }
        QTextStream out(&file);
        out << str;
        strNom.clear();
        strPrenom.clear();
        strInsee.clear();
        strSexe.clear();
        strNomJF.clear();
        strRue1.clear();
        strRue2.clear();
        strCodeP.clear();
        strVille.clear();
        cboxIndex = 0;
        cboxIndex2 = 0;
    }
    else
    {
        QMessageBox::warning(this, "Erreur", "Veuillez indiquer un nom");
    }
}

void WindowViewPatient::modifyPatientOK()
{
    QString str = parent_t->getStrFile(parent_t->getFilename(1));

    if (!strNom.isEmpty())
    {
        QStringList strList = str.split("\n", QString::SkipEmptyParts);
        QString newStr;
        newStr.append(strDateN + ";");
        newStr.append(strNom + ";");
        newStr.append(strPrenom + ";");
        newStr.append(strInsee + ";");
        newStr.append(strSexe + ";");
        newStr.append(strDateD + ";");
        newStr.append(strNomJF + ";");
        newStr.append(strRue1 + ";");
        newStr.append(strRue2 + ";");
        newStr.append(strCodeP + ";");
        newStr.append(strVille + ";");
        newStr.append(parent_t->getListeGroupe()->value(cboxIndex) + ";");
        newStr.append(parent_t->getTabListeSecteur()->value(cboxIndex)[cboxIndex2] + ";");
        newStr.append(";;;");
        strList.replace(selectedTableRow + 1, newStr);
        newStr.clear();
        for (int i = 0; i < strList.length(); i++) {
            newStr.append(strList[i]);
            newStr.append("\n");
        }

        QFile file(parent_t->getFilename(1));
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::critical(this, "Erreur", "Impossible d'ouvrir " + file.fileName());
            return;
        }
        QTextStream out(&file);
        out << newStr;
        cboxIndex = 0;
        cboxIndex2 = 0;
    }
    else
    {
        QMessageBox::warning(this, "Erreur", "Veuillez indiquer un nom");
    }
}

void WindowViewPatient::supprPatientOK()
{
    QString str = parent_t->getStrFile(parent_t->getFilename(1));
    QStringList strList = str.split("\n", QString::SkipEmptyParts);
    QString newstr;

    for (int i = 0; i < (strList.length()) ; i++) {
        if (i != selectedTableRow + 1) {
            newstr.append(strList.value(i));
            newstr.append("\n");
        } else
            qDebug() << "Patient supprimé : " << strList.value(i);
    }
    QFile file(parent_t->getFilename(1));
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Erreur", "Impossible d'ouvrir " + file.fileName());
        return;
    }
    QTextStream out(&file);
    out << newstr;
    cboxIndex = 0;
    selectedTableRow = 0;
    parent_t->actualiser();
}

void WindowViewPatient::getSelectedRow(const QModelIndex &index)
{
    selectedTableRow = index.row();
}

void WindowViewPatient::saveCboxIndex(int currentRow)
{
    cboxIndex = currentRow;
}

void WindowViewPatient::saveCboxIndex2(int currentRow)
{
    cboxIndex2 = currentRow;
}

void WindowViewPatient::changeCboxSecteur()
{
    cboxSecteur->clear();
    cboxSecteur->addItems(parent_t->getTabListeSecteur()->value(cboxIndex));
}

void WindowViewPatient::saveTextNom(QString nom)
{
    strNom = nom;
}

void WindowViewPatient::saveTextPrenom(QString str)
{
    strPrenom = str;
}

void WindowViewPatient::saveTextInsee(QString str)
{
    strInsee = str;
}

void WindowViewPatient::saveTextSexe(QString str)
{
    strSexe = str;
}

void WindowViewPatient::saveTextNomJF(QString str)
{
    strNomJF = str;
}

void WindowViewPatient::saveTextRue1(QString str)
{
    strRue1 = str;
}

void WindowViewPatient::saveTextRue2(QString str)
{
    strRue2 = str;
}

void WindowViewPatient::saveTextCodeP(QString str)
{
    strCodeP = str;
}

void WindowViewPatient::saveTextVille(QString str)
{
    strVille = str;
}

void WindowViewPatient::saveTextDateN(QString str)
{
    strDateN = str;
}

void WindowViewPatient::saveTextDateD(QString str)
{
    strDateD = str;
}

void WindowViewPatient::saveAllInfosFromLine(int nbline)
{
    QString str = parent_t->getStrFile(parent_t->getFilename(1));
    QStringList strList = str.split("\n", QString::SkipEmptyParts).value(nbline).split(";");

    strDateN = strList[0];
    strNom = strList[1];
    strPrenom = strList[2];
    strInsee = strList[3];
    strSexe = strList[4];
    strDateD = strList[5];
    strNomJF = strList[6];
    strRue1 = strList[7];
    strRue2 = strList[8];
    strCodeP = strList[9];
    strVille = strList[10];
}

void WindowViewPatient::actualiser()
{
    model = new TableModelPatient();
    model->populateData(parent_t->getStrFile(parent_t->getFilename(1)));
    view->setModel(model);
}

int WindowViewPatient::getIndex(QString str)
{
    int i;
    for (i = 0; i < parent_t->getListeGroupe()->length(); i++)
    {
        if (parent_t->getListeGroupe()->value(i) == str)
            return (i);
    }
    return (0);
}

int WindowViewPatient::getIndex2(QString str)
{
    int j = 0;
    for (int i = 0; i <= parent_t->getListeGroupe()->length(); i++)
    {
        for(j = 0; j <= parent_t->getTabListeSecteur()->value(i).length(); j++)
        {
            if (parent_t->getTabListeSecteur()->value(i).value(j) == str)
                return (j);
        }
    }
    return (j);
}
