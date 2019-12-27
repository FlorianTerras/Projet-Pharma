#include "windowviewmedecin.h"

WindowViewMedecin::WindowViewMedecin(MainWindow *parent)
{
    parent_t = parent;
    this->setParent(parent);
    _numFile = 3;
    selectedTableRow = - 1;
    QVBoxLayout *VBL = new QVBoxLayout();
    view = new QTableView(this);
    this->setWindowFlag(Qt::Window);
    this->setWindowTitle("Médecins");
    this->resize(1600, 850);
    model = new TableModelPatient();
    model->populateData(parent_t->getStrFile(parent_t->getFilename(_numFile)));
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

    connect(view, SIGNAL(clicked(const QModelIndex &)), this, SLOT(saveSelectedRow(const QModelIndex &)));
    connect(button_ajouter, SIGNAL(clicked()), this, SLOT(addPatient()));
    connect(button_modifier, SIGNAL(clicked()), this, SLOT(modifyPatient()));
    connect(button_supprimer, SIGNAL(clicked()), this, SLOT(supprPatient()));
}

void WindowViewMedecin::addPatient()
{
    QWidget *window = new QWidget(this, Qt::Dialog);
    window->setWindowTitle("Ajouter un médecin");
    QVBoxLayout *VBL = new QVBoxLayout(window);
    QFormLayout *QFL = new QFormLayout;
    VBL->addLayout(QFL);
    QLineEdit *nom = new QLineEdit;
    QLineEdit *prenom = new QLineEdit;
    QLineEdit *spec = new QLineEdit;
    QLineEdit *AM = new QLineEdit;
    QLineEdit *RPPS = new QLineEdit;
    QLineEdit *rue1 = new QLineEdit;
    QLineEdit *rue2 = new QLineEdit;
    QLineEdit *codeP = new QLineEdit;
    QLineEdit *ville = new QLineEdit;
    QLineEdit *tel = new QLineEdit;
    QLineEdit *mail = new QLineEdit;
    QLineEdit *fax = new QLineEdit;

    QFL->addRow("Nom :", nom);
    QFL->addRow("Prénom :", prenom);
    QFL->addRow("Spécialité :", spec);
    QFL->addRow("N° d'AM", AM);
    QFL->addRow("RPPS :", RPPS);
    QFL->addRow("Rue 1 :", rue1);
    QFL->addRow("Rue 2 :", rue2);
    QFL->addRow("Code Postal :", codeP);
    QFL->addRow("Ville :", ville);
    QFL->addRow("Téléphone :", tel);
    QFL->addRow("Mail :", mail);
    QFL->addRow("Fax :", fax);

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
    window->resize(600, 550);

    connect(nom, SIGNAL(textChanged(QString)), this, SLOT(saveTextNom(QString)));
    connect(prenom, SIGNAL(textChanged(QString)), this, SLOT(saveTextPrenom(QString)));
    connect(spec, SIGNAL(textChanged(QString)), this, SLOT(saveTextSpec(QString)));
    connect(AM, SIGNAL(textChanged(QString)), this, SLOT(saveTextAM(QString)));
    connect(RPPS, SIGNAL(textChanged(QString)), this, SLOT(saveTextRPPS(QString)));
    connect(rue1, SIGNAL(textChanged(QString)), this, SLOT(saveTextRue1(QString)));
    connect(rue2, SIGNAL(textChanged(QString)), this, SLOT(saveTextRue2(QString)));
    connect(codeP, SIGNAL(textChanged(QString)), this, SLOT(saveTextCodeP(QString)));
    connect(ville, SIGNAL(textChanged(QString)), this, SLOT(saveTextVille(QString)));
    connect(tel, SIGNAL(textChanged(QString)), this, SLOT(saveTextTel(QString)));
    connect(mail, SIGNAL(textChanged(QString)), this, SLOT(saveTextMail(QString)));
    connect(fax, SIGNAL(textChanged(QString)), this, SLOT(saveTextFax(QString)));
    connect(buttonOk, SIGNAL(clicked()), this, SLOT(addPatientOK()));
    connect(buttonOk, &QPushButton::clicked, window, &QWidget::close);
    connect(buttonOk, SIGNAL(clicked()), parent_t, SLOT(actualiser()));
    connect(buttonOk, SIGNAL(clicked()), this, SLOT(actualiser()));
    connect(buttonAnnuler, &QPushButton::clicked, window, &QWidget::close);
}

void WindowViewMedecin::modifyPatient()
{
    QWidget *window = new QWidget(this, Qt::Dialog);
    QVBoxLayout *VBL = new QVBoxLayout(window);
    QFormLayout *QFL = new QFormLayout;
    QLineEdit *nom = new QLineEdit;
    QLineEdit *prenom = new QLineEdit;
    QLineEdit *spec = new QLineEdit;
    QLineEdit *AM = new QLineEdit;
    QLineEdit *RPPS = new QLineEdit;
    QLineEdit *rue1 = new QLineEdit;
    QLineEdit *rue2 = new QLineEdit;
    QLineEdit *codeP = new QLineEdit;
    QLineEdit *ville = new QLineEdit;
    QLineEdit *tel = new QLineEdit;
    QLineEdit *mail = new QLineEdit;
    QLineEdit *fax = new QLineEdit;
    QHBoxLayout *HBL = new QHBoxLayout;
    QPushButton *buttonOk = new QPushButton("OK");
    QPushButton *buttonAnnuler = new QPushButton("Annuler");

    if (selectedTableRow >= 0) {
        saveAllInfosFromLine(selectedTableRow + 1);
        window->setWindowTitle("Modifier un médecin");
        nom->setText(strNom);
        QFL->addRow("Nom :",nom);
        prenom->setText(strPrenom);
        QFL->addRow("Prénom :", prenom);
        spec->setText(strSpec);
        QFL->addRow("Spécialité:", spec);
        AM->setText(strAM);
        QFL->addRow("N° d'AM :", AM);
        RPPS->setText(strRPPS);
        QFL->addRow("RPPS :", RPPS);
        rue1->setText(strRue1);
        QFL->addRow("Rue 1 :", rue1);
        rue2->setText(strRue2);
        QFL->addRow("Rue 2 :", rue2);
        codeP->setText(strCodeP);
        QFL->addRow("Code postal :", codeP);
        ville->setText(strVille);
        QFL->addRow("Ville :", ville);
        tel->setText(strTel);
        QFL->addRow("Téléphone :", tel);
        mail->setText(strMail);
        QFL->addRow("Mail :", mail);
        fax->setText(strFax);
        QFL->addRow("Fax :", fax);
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
        QMessageBox::warning(window, "Erreur", "Veuillez selectionner un médecin");
        return;
    }
    connect(nom, SIGNAL(textChanged(QString)), this, SLOT(saveTextNom(QString)));
    connect(prenom, SIGNAL(textChanged(QString)), this, SLOT(saveTextPrenom(QString)));
    connect(spec, SIGNAL(textChanged(QString)), this, SLOT(saveTextSpec(QString)));
    connect(AM, SIGNAL(textChanged(QString)), this, SLOT(saveTextAM(QString)));
    connect(RPPS, SIGNAL(textChanged(QString)), this, SLOT(saveTextRPPS(QString)));
    connect(rue1, SIGNAL(textChanged(QString)), this, SLOT(saveTextRue1(QString)));
    connect(rue2, SIGNAL(textChanged(QString)), this, SLOT(saveTextRue2(QString)));
    connect(codeP, SIGNAL(textChanged(QString)), this, SLOT(saveTextCodeP(QString)));
    connect(ville, SIGNAL(textChanged(QString)), this, SLOT(saveTextVille(QString)));
    connect(tel, SIGNAL(textChanged(QString)), this, SLOT(saveTextTel(QString)));
    connect(mail, SIGNAL(textChanged(QString)), this, SLOT(saveTextMail(QString)));
    connect(fax, SIGNAL(textChanged(QString)), this, SLOT(saveTextFax(QString)));
    connect(buttonOk, SIGNAL(clicked()), this, SLOT(modifyPatientOK()));
    connect(buttonOk, SIGNAL(clicked()), parent_t, SLOT(actualiser()));
    connect(buttonOk, SIGNAL(clicked()), this, SLOT(actualiser()));
    connect(buttonOk, &QPushButton::clicked, window, &QWidget::close);
    connect(buttonAnnuler, &QPushButton::clicked, window, &QWidget::close);
}

void WindowViewMedecin::supprPatient()
{
    QMessageBox msgBox(this);
    if (selectedTableRow >= 0)
    {
        msgBox.setText("Ce médecin va être supprimé : "
                       + parent_t->getStrFile(parent_t->getFilename(_numFile)).split("\n").value(selectedTableRow+1).split(";").value(0)
                       + " " + parent_t->getStrFile(parent_t->getFilename(_numFile)).split("\n").value(selectedTableRow+1).split(";").value(1));
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
        QMessageBox::warning(this, "Erreur", "Veuillez selectionner un médecin");
        return;
    }
}

void WindowViewMedecin::addPatientOK()
{
    QString str = parent_t->getStrFile(parent_t->getFilename(_numFile));
    if (!strNom.isEmpty() && !strPrenom.isEmpty()) {
        str.append(strNom +";");
        str.append(strPrenom + ";");
        str.append(strSpec + ";");
        str.append(strAM + ";");
        str.append(strRPPS + ";");
        str.append(strRue1 + ";");
        str.append(strRue2 + ";");
        str.append(strCodeP + ";");
        str.append(strVille + ";");
        str.append(strTel + ";");
        str.append(strMail + ";");
        str.append(strFax + ";");
        str.append("\n");
        QFile file(parent_t->getFilename(_numFile));
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::critical(this, "Erreur", "Impossible d'ouvrir " + file.fileName());
            return;
        }
        QTextStream out(&file);
        out << str;
        strNom.clear();
        strPrenom.clear();
        strSpec.clear();
        strAM.clear();
        strRPPS.clear();
        strRue1.clear();
        strRue2.clear();
        strCodeP.clear();
        strVille.clear();
        strTel.clear();
        strMail.clear();
        strFax.clear();
    } else {
        QMessageBox::warning(this, "Erreur", "Veuillez indiquer un nom");
    }
}

void WindowViewMedecin::modifyPatientOK()
{
    QString str = parent_t->getStrFile(parent_t->getFilename(_numFile));

    if (!strNom.isEmpty()) {
        QStringList strList = str.split("\n", QString::SkipEmptyParts);
        QString newStr;
        newStr.append(strNom +";");
        newStr.append(strPrenom + ";");
        newStr.append(strSpec + ";");
        newStr.append(strAM + ";");
        newStr.append(strRPPS + ";");
        newStr.append(strRue1 + ";");
        newStr.append(strRue2 + ";");
        newStr.append(strCodeP + ";");
        newStr.append(strVille + ";");
        newStr.append(strTel + ";");
        newStr.append(strMail + ";");
        newStr.append(strFax + ";");
        strList.replace(selectedTableRow + 1, newStr);
        newStr.clear();
        for (int i = 0; i < strList.length(); i++) {
            newStr.append(strList[i]);
            newStr.append("\n");
        }

        QFile file(parent_t->getFilename(_numFile));
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::critical(this, "Erreur", "Impossible d'ouvrir " + file.fileName());
            return;
        }
        QTextStream out(&file);
        out << newStr;
    } else {
        QMessageBox::warning(this, "Erreur", "Veuillez indiquer un nom");
    }
}

void WindowViewMedecin::supprPatientOK()
{
    QString str = parent_t->getStrFile(parent_t->getFilename(_numFile));
    QStringList strList = str.split("\n", QString::SkipEmptyParts);
    QString newstr;

    for (int i = 0; i < (strList.length()) ; i++) {
        if (i != selectedTableRow + 1) {
            newstr.append(strList.value(i));
            newstr.append("\n");
        } else
            qDebug() << "Médecin supprimé : " << strList.value(i);
    }
    QFile file(parent_t->getFilename(_numFile));
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Erreur", "Impossible d'ouvrir " + file.fileName());
        return;
    }
    QTextStream out(&file);
    out << newstr;
    selectedTableRow = 0;
    parent_t->actualiser();
}

void WindowViewMedecin::saveSelectedRow(const QModelIndex &index)
{
    selectedTableRow = index.row();
}

void WindowViewMedecin::saveTextNom(QString nom)
{
    strNom = nom;
}

void WindowViewMedecin::saveTextPrenom(QString str)
{
    strPrenom = str;
}

void WindowViewMedecin::saveTextSpec(QString str)
{
    strSpec = str;
}

void WindowViewMedecin::saveTextAM(QString str)
{
    strAM = str;
}

void WindowViewMedecin::saveTextRPPS(QString str)
{
    strRPPS = str;
}

void WindowViewMedecin::saveTextRue1(QString str)
{
    strRue1 = str;
}

void WindowViewMedecin::saveTextRue2(QString str)
{
    strRue2 = str;
}

void WindowViewMedecin::saveTextCodeP(QString str)
{
    strCodeP = str;
}

void WindowViewMedecin::saveTextVille(QString str)
{
    strVille = str;
}

void WindowViewMedecin::saveTextTel(QString str)
{
    strTel = str;
}

void WindowViewMedecin::saveTextMail(QString str)
{
    strMail = str;
}

void WindowViewMedecin::saveTextFax(QString str)
{
    strFax = str;
}

void WindowViewMedecin::saveAllInfosFromLine(int nbline)
{
    QString str = parent_t->getStrFile(parent_t->getFilename(_numFile));
    QStringList strList = str.split("\n", QString::SkipEmptyParts).value(nbline).split(";");

    strNom = strList[0];
    strPrenom = strList[1];
    strSpec = strList[2];
    strAM = strList[3];
    strRPPS = strList[4];
    strRue1 = strList[5];
    strRue2 = strList[6];
    strCodeP = strList[7];
    strVille = strList[8];
    strTel = strList[9];
    strMail = strList[10];
    strFax = strList[11];
}

void WindowViewMedecin::actualiser()
{
    model = new TableModelPatient();
    model->populateData(parent_t->getStrFile(parent_t->getFilename(_numFile)));
    view->setModel(model);
}
