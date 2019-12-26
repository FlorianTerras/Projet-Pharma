#include "windowviewgroupe.h"

WindowViewGroupe::WindowViewGroupe(MainWindow *parent)
{
    selectedRow = -1;
    parent_t = parent;
    this->setParent(parent);
    QVBoxLayout *VBL = new QVBoxLayout;
    QListView *view = new QListView();
    this->setWindowFlag(Qt::Dialog);
    this->setWindowTitle("Groupes");
    this->resize(500, 400);
    model = new QStringListModel();
    model->setStringList(*parent_t->getListeGroupe());
    view->setModel(model);
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
    connect(button_ajouter, SIGNAL(clicked()), this, SLOT(addGroupe()));
    connect(button_ajouter, SIGNAL(clicked()), parent_t, SLOT(actualiser()));
    connect(button_ajouter, SIGNAL(clicked()), this, SLOT(actualiser()));
    connect(button_supprimer, SIGNAL(clicked()), this, SLOT(supprGroupe()));
    connect(button_supprimer, SIGNAL(clicked()), parent_t, SLOT(actualiser()));
    connect(button_supprimer, SIGNAL(clicked()), this, SLOT(actualiser()));
}

void WindowViewGroupe::addGroupe()
{
    bool ok = false;
    QString strmdr = QInputDialog::getText(this, "Ajout groupe", "Entrez un nom :", QLineEdit::Normal, QString(), &ok);

    if (ok && strmdr.isEmpty())
    {
        QMessageBox::critical(this, "Erreur", "Spécifiez un nom.");
    }
    else if (ok && !strmdr.isEmpty())
    {
        QFile file(parent_t->getFilename(0));
           if (!file.open(QIODevice::WriteOnly | QIODevice::Append)) {
               QMessageBox::critical(this, "Erreur", "Impossible d'ouvrir " + file.fileName());
               return;
           }
        QTextStream out(&file);
            out << strmdr << ";" << "\n";
    }
}

void WindowViewGroupe::supprGroupe()
{
    QMessageBox msgBox(this);
    if (selectedRow >= 0)
    {
        msgBox.setText("Ce groupe va être supprimé : " + parent_t->getListeGroupe()->value(selectedRow));
        msgBox.setInformativeText("Etes vous sûr ?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);
        int ret = msgBox.exec();

        switch (ret) {
            case QMessageBox::Yes:
                supprGroupeOK();
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

void  WindowViewGroupe::supprGroupeOK()
{
    QString str = parent_t->getStrFile(parent_t->getFilename(0));
    QStringList strList = str.split("\n", QString::SkipEmptyParts);
    QString newstr;

    for (int i = 0; i < (strList.length()) ; i++) {
        if (i != selectedRow) {
            newstr.append(strList.value(i));
            newstr.append("\n");
        } else
            qDebug() << "Groupe supprimé : " << strList.value(i);
    }
    QFile file(parent_t->getFilename(0));
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Erreur", "Impossible d'ouvrir " + file.fileName());
        return;
    }
    QTextStream out(&file);
    out << newstr;
    qDebug() << newstr << endl;
//    row = 0;
    selectedRow = 0;
}

void WindowViewGroupe::getSelectedRow(const QModelIndex &index)
{
    selectedRow = index.row();
}

void WindowViewGroupe::actualiser()
{
    model->setStringList(*parent_t->getListeGroupe());
}
