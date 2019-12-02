#include "windowviewsecteur.h"

WindowViewSecteur::WindowViewSecteur(MainWindow *parent)
{
    selectedTableCol = -1;
    parent_t = parent;
    this->setParent(parent);
    QVBoxLayout *VBL = new QVBoxLayout;
    view = new QTableView(this);
    this->setWindowFlag(Qt::Dialog);
    this->setWindowTitle("Secteur");
    this->resize(900, 400);
    model = new TableModel();
    model->populateData(*parent_t->getListeGroupe(), *parent_t->getTabListeSecteur());
    view->setModel(model);
    view->resizeColumnsToContents();
    this->setLayout(VBL);
    VBL->addWidget(view);

    QHBoxLayout *HBL = new QHBoxLayout();
    QPushButton *button_ajouter = new QPushButton("Ajouter");
    HBL->addWidget(button_ajouter);
    QPushButton *button_supprimer = new QPushButton("Supprimer");
    HBL->addWidget(button_supprimer);
    HBL->setAlignment(Qt::AlignBottom);
    VBL->addLayout(HBL);

    connect(view, SIGNAL(clicked(const QModelIndex &)), this, SLOT(getSelectedRow(const QModelIndex &)));
    connect(view, SIGNAL(clicked(const QModelIndex &)), this, SLOT(getSelectedCol(const QModelIndex &)));
    connect(button_ajouter, SIGNAL(clicked()), this, SLOT(addSecteur()));
    connect(button_supprimer, SIGNAL(clicked()), this, SLOT(supprSecteur()));
}

void WindowViewSecteur::addSecteur()
{
    QWidget *window = new QWidget(this, Qt::Dialog);
    window->setWindowTitle("Ajouter un secteur");
    QVBoxLayout *VBL = new QVBoxLayout(window);
    QFormLayout *QFL = new QFormLayout;
    VBL->addLayout(QFL);
    QComboBox *cbox = new QComboBox;
    cbox->addItems(*parent_t->getListeGroupe());
    QFL->addRow("Sélectionnez un groupe :", cbox);
    QLineEdit *nom = new QLineEdit;
    QFL->addRow("Entrez le nom du groupe", nom);
    QHBoxLayout *HBL = new QHBoxLayout;
    VBL->addSpacing(20);
    VBL->addLayout(HBL);
    QPushButton *buttonOk = new QPushButton("OK");
    QPushButton *buttonAnnuler = new QPushButton("Annuler");
    buttonOk->setFixedSize(120, 30);
    buttonAnnuler->setFixedSize(120, 30);
    HBL->setAlignment(Qt::AlignBottom | Qt::AlignRight);
    HBL->addWidget(buttonAnnuler);
    HBL->addWidget(buttonOk);
    window->show();
    cboxIndex = 0;

    connect(cbox, SIGNAL(currentIndexChanged(int)), this, SLOT(saveCboxIndex(int)));
    connect(nom, SIGNAL(textChanged(QString)), this, SLOT(saveTextNom(QString)));
    connect(buttonOk, &QPushButton::clicked, this, &WindowViewSecteur::addSecteurOK);
    connect(buttonOk, &QPushButton::clicked, window, &QWidget::close);
    connect(buttonOk, SIGNAL(clicked()), parent_t, SLOT(actualiser()));
    connect(buttonOk, SIGNAL(clicked()), this, SLOT(actualiser()));
    connect(buttonAnnuler, &QPushButton::clicked, window, &QWidget::close);
}

void WindowViewSecteur::addSecteurOK()
{
    if (!strNom.isEmpty())
    {
        QString str = parent_t->getStrFile(parent_t->getFilename(0));
        QStringList splitLine = str.split("\n");
        splitLine[cboxIndex].append(strNom);
        splitLine[cboxIndex].append(",");
        QString newstr;
        for(int i = 0; i < (splitLine.length()); i++)
        {
            newstr.push_back(splitLine[i]);
            newstr.push_back("\n");
        }
        int pos = newstr.lastIndexOf(QChar('\n'));
        newstr = newstr.left(pos);
        QFile file(parent_t->getFilename(0));
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::critical(this, "Erreur", "Impossible d'ouvrir " + file.fileName());
            return;
        }
        QTextStream out(&file);
        out << newstr;
        strNom.clear();
        cboxIndex = 0;
    }
    else
    {
        QMessageBox::warning(this, "Erreur", "Veuillez indiquer un nom");
    }
}

void WindowViewSecteur::supprSecteur()
{
    QMessageBox msgBox(this);
    if (selectedTableCol >= 0)
    {
        msgBox.setText("Ce secteur va être supprimé : " + parent_t->getTabListeSecteur()->value(selectedTableCol).value(selectedTableRow));
        msgBox.setInformativeText("Etes vous sûr ?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);
        int ret = msgBox.exec();

        switch (ret) {
            case QMessageBox::Yes:
                supprSecteurOK();
                parent_t->actualiser();
                this->actualiser();
                break;
            case QMessageBox::No:
                msgBox.close();
                return;
            default:
                return;
        }
    } else {
        QMessageBox::warning(this, "Erreur", "Veuillez selectionner un groupe");
        return;
    }
}

void WindowViewSecteur::supprSecteurOK()
{
    QString str = parent_t->getStrFile(parent_t->getFilename(0));
    QStringList strListGroupe = str.split("\n", QString::SkipEmptyParts);
    QStringList strListSecteur = strListGroupe.value(selectedTableCol).split(";").value(1).split(",", QString::SkipEmptyParts);
    QString newstr;
    QString newstrSecteur;
    for (int i = 0; i < strListSecteur.length(); i++)
        if (i != selectedTableRow) {
            newstrSecteur.append(strListSecteur.value(i));
            newstrSecteur.append(",");
         } else
            qDebug() << "Secteur supprimé : " << strListSecteur.value(i) << endl;

    strListSecteur.value(selectedTableRow) = newstrSecteur;

    for (int i = 0; i < (strListGroupe.length()) ; i++) {
       if (i != selectedTableCol) {
           newstr.append(strListGroupe.value(i));
           newstr.append("\n");
       } else {
           newstr.append(strListGroupe.value(selectedTableCol).split(";").value(0));
           newstr.append(";");
           newstr.append(newstrSecteur + "\n");
       }
    }

    QFile file(parent_t->getFilename(0));
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Erreur", "Impossible d'ouvrir " + file.fileName());
        return;
    }
    QTextStream out(&file);
    out << newstr;
}

void WindowViewSecteur::saveCboxIndex(int index)
{
    cboxIndex = index;
}

void WindowViewSecteur::saveTextNom(QString str)
{
    strNom = str;
}

void WindowViewSecteur::getSelectedCol(const QModelIndex &index)
{
    selectedTableCol = index.column();
}

void WindowViewSecteur::getSelectedRow(const QModelIndex &index)
{
    selectedTableRow = index.row();
}

void WindowViewSecteur::actualiser()
{
    model = new TableModel();
    model->populateData(*parent_t->getListeGroupe(), *parent_t->getTabListeSecteur());
    view->setModel(model);
}
