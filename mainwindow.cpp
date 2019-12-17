#include "mainwindow.h"
#include "tablemodel.h"
#include "tablemodelpatient.h"
#include "windowviewgroupe.h"
#include "windowviewsecteur.h"
#include "windowviewpatient.h"
#include "windowviewproduit.h"
#include "centralwidgetordonnance.h"

MainWindow::MainWindow()
{
    filenameGroupe = "Data/groupes.txt";
    filenamePatients = "Data/Patient Baou.txt";
    filenameProduits = "Data/Produits.csv";

    QFrame *frame = new QFrame;
    frame->setAutoFillBackground(true);
    frame->setPalette(QColor(Qt::darkGray));
    setCentralWidget(frame);
    createMenus();
    createListes();
    createDockWindows();

    setWindowTitle(tr("Projet Pharmacie"));

    this->resize(1670, 900);
    this->showMaximized();
}

void MainWindow::createDockWindows()
{
    QDockWidget *dock = new QDockWidget(tr(""), this);
    dock->setFeatures(nullptr);
    QPushButton *button_actualiser = new QPushButton("Actualiser");
    dock->setWidget(button_actualiser);
    addDockWidget(Qt::RightDockWidgetArea, dock);

    dock = new QDockWidget(tr("Groupe"), this);
    dock->setFeatures(nullptr);
    groupeList = new QListWidget(dock);
    groupeList->addItems(*listeGroupe);
    dock->setWidget(groupeList);
    addDockWidget(Qt::RightDockWidgetArea, dock);

    dock = new QDockWidget(tr("Secteur"), this);
    dock->setFeatures(nullptr);
    secteurList = new QListWidget(dock);
    addDockWidget(Qt::RightDockWidgetArea, dock);
    dock->setWidget(secteurList);

    dock = new QDockWidget(tr("Patients"), this);
    dock->setFeatures(nullptr);
    patientsList = new QListWidget(dock);
    dock->setWidget(patientsList);
    addDockWidget(Qt::RightDockWidgetArea, dock);

    dock = new QDockWidget(tr("Action"), this);
    dock->setFeatures(nullptr);
    QWidget *widget1 = new QWidget;
    QHBoxLayout *HBL = new QHBoxLayout(widget1);
    QPushButton *button_ordonnance = new QPushButton("Ordonnance");
    QPushButton *button_blister = new QPushButton("Blistérisation");
    dock->setWidget(widget1);
    HBL->addWidget(button_ordonnance);
    HBL->addWidget(button_blister);

    widget1->setLayout(HBL);

    addDockWidget(Qt::RightDockWidgetArea, dock);

    connect(groupeList, &QListWidget::currentRowChanged, this, &MainWindow::changeListPatients);
    connect(secteurList, &QListWidget::currentRowChanged, this, &MainWindow::changeListPatients);
    connect(groupeList, &QListWidget::currentRowChanged, this, &MainWindow::changeListSecteur);
    connect(patientsList, &QListWidget::currentRowChanged, this, &MainWindow::getSelectedPatient);
    connect(button_actualiser, &QPushButton::clicked, this, &MainWindow::actualiser);
    connect(button_ordonnance, &QPushButton::clicked, this, &MainWindow::createOrdo);
}

void MainWindow::changeListSecteur()
{
    secteurList->clear();
    secteurList->addItems(tabListeSecteur->value(groupeList->currentRow()));
}

void MainWindow::changeListPatients()
{
    patientsList->clear();
    patientsList->addItems(tabListePatient->value(groupeList->currentRow()).value(secteurList->currentRow()));
}

QStringList MainWindow::getSelectedPatient()
{
    QString str = tabListePatient->value(groupeList->currentRow()).value(secteurList->currentRow()).value(patientsList->currentRow());
    QStringList strlist = getStrFile(filenamePatients).split("\n");
    for (int i = 0; i < strlist.length() - 1; i++)
    {
        if (strlist.value(i).split(";").value(1) == str.split(" ").value(0))
            return (strlist.value(i).split(";"));
    }
    return (QString("NULL;NULL;NULL;NULL;NULL;NULL;NULL;NULL;NULL;NULL;NULL;NULL;").split(";"));
}

void MainWindow::actualiser()
{
    createListes();
    groupeList->clear();
    groupeList->addItems(*listeGroupe);
    patientsList->clear();
    patientsList->addItems(tabListePatient->value(groupeList->currentRow()).value(secteurList->currentRow()));
}

void MainWindow::save()
{
/*    QMimeDatabase mimeDatabase;
    QString fileName = QFileDialog::getSaveFileName(this,
                        tr("Choose a file name"), ".",
                        mimeDatabase.mimeTypeForName("text/html").filterString());
    if (fileName.isEmpty())
        return;
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Dock Widgets"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(QDir::toNativeSeparators(fileName), file.errorString()));
        return;
    }

    QTextStream out(&file);
    QGuiApplication::setOverrideCursor(Qt::WaitCursor);
    out << textEdit->toHtml();
    QGuiApplication::restoreOverrideCursor();

    statusBar()->showMessage(tr("Saved '%1'").arg(fileName), 2000);*/
}

void MainWindow::undo()
{
/*    QTextDocument *document = textEdit->document();
    document->undo();*/
}

void MainWindow::createMenus()
{
    QMenu *menuFichier = menuBar()->addMenu("&Fichier");
    QFileIconProvider *fileIconProv = new QFileIconProvider;

    QMenu *fichiersOuvrir = menuFichier->addMenu("Ouvrir");
/*    QAction *actionOuvrirGroupe =*/ fichiersOuvrir->addAction("Fichier groupe");
/*    QAction *actionOuvrirPatient =*/ fichiersOuvrir->addAction("Fichier patient");
    fichiersOuvrir->addAction("Fichier produit");
    actionQuitter = new QAction("&Quitter", this);
    menuFichier->addAction(actionQuitter);

    QMenu *menuEdition = menuBar()->addMenu("&Edition");
    Q_UNUSED(menuEdition)
/*    QAction *actionGras = menuEdition->addAction("Gras");
    actionGras->setCheckable(true);*/

    QMenu *menuAffichage = menuBar()->addMenu("&Affichage");
    QAction *actionFullscreen = menuAffichage->addAction("Plein écran");
    actionFullscreen->setCheckable(true);

    QMenu *menuDonnees = menuBar()->addMenu("&Données");
    QAction *actionVoirGroupe = menuDonnees->addAction("Groupes");
    QAction *actionVoirSecteur = menuDonnees->addAction("Secteurs");
    QAction *actionVoirPatient = menuDonnees->addAction("Patients");
    QAction *actionVoirProduit = menuDonnees->addAction("Produits");

    actionQuitter->setShortcut(QKeySequence("Ctrl+Q"));
    actionFullscreen->setShortcut(QKeySequence("F11"));
    fichiersOuvrir->setIcon(fileIconProv->icon(QFileIconProvider::File));
    actionQuitter->setIcon(QIcon("/usr/share/icons/gnome/48x48/actions/gtk-quit.png"));
    actionFullscreen->setIcon(QIcon("/usr/share/icons/gnome/48x48/actions/gtk-fullscreen.png"));

    connect(actionFullscreen, SIGNAL(toggled(bool)), this, SLOT(toggleFullscreen(bool)));
    connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(actionVoirGroupe, SIGNAL(triggered()), this, SLOT(voirGroupe()));
    connect(actionVoirSecteur, SIGNAL(triggered()), this, SLOT(voirSecteur()));
    connect(actionVoirPatient, SIGNAL(triggered()), this, SLOT(voirPatient()));
    connect(actionVoirProduit, SIGNAL(triggered()), this, SLOT(voirProduit()));
}

void MainWindow::toggleFullscreen(bool b)
{
    if (b == true) {
         this->showFullScreen();
    } else {
        this->showNormal();
        this->showMaximized();
    }
}

void MainWindow::fillGroupeStringList(QString str)
{
    QStringList tab = str.split(";"/*, QString::SkipEmptyParts*/);
    QStringList subtab = tab[1].split(",", QString::SkipEmptyParts);
    *listeGroupe << tab[0];
    *tabListeSecteur << subtab;
}

void MainWindow::fillPatientStringList(QString str)
{
    int mdr = 0;
    int sect = 0;
    bool etape1 = 0;
    bool etape2 = 0;

    QStringList tab = str.split(";"/*, QString::SkipEmptyParts*/);
    for (int i = 0; i < listeGroupe->length(); i++) {
        if (listeGroupe->value(i) == tab[11]) {
            mdr = i;
            etape1 = 1;
        }
    }
    for (int i = 0; i < tabListeSecteur->at(mdr).length(); i++)
        if (tabListeSecteur->value(mdr)[i] == tab[12]) {
            sect = i;
            etape2 = 1;
        }
    if (etape1 && etape2)
        tabListePatient->data()[mdr].data()[sect].push_back(tab[1] + " " + tab[2]);
}

void MainWindow::readFileData()
{
    QFile file(filenameGroupe);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Erreur", "Impossible d'ouvrir " + file.fileName());
        return;
    }
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (line != "") {
            fillGroupeStringList(line);
        } else
            qDebug() << "line empty";
    }
    for (int i = 0; i < listeGroupe->length(); i++)
    {
        QVector<QStringList> v;
        for (int j = 0; j < tabListeSecteur->value(i).length(); j++)
        {
            QStringList b;
            v.push_back(b);
        }
        tabListePatient->push_back(v);
    }
    QFile file2(filenamePatients);
    if (!file2.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Erreur", "Impossible d'ouvrir " + file2.fileName());
        return;
    }
    QTextStream in2(&file2);
    while (!in2.atEnd()) {
        QString line2 = in2.readLine();
        if (line2 != "")
            fillPatientStringList(line2);
        else
            qDebug() << "line2 empty";
    }
}

void MainWindow::createListes()
{
    tabListeSecteur = new QVector<QStringList>;
    tabListePatient = new QVector<QVector<QStringList>>;
    listeGroupe = new QStringList();
    readFileData();
}

QString MainWindow::getStrFile(QString filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Erreur", "Impossible d'ouvrir " + file.fileName());
        return(nullptr);
    }
    QTextStream in(&file);
    QString str = in.readAll();
    return (str);
}

QString MainWindow::getFilename(int n)
{
    switch (n) {
        case 0:
            return filenameGroupe;
        case 1:
            return filenamePatients;
        case 2:
            return filenameProduits;
        default:
            return nullptr;
    }
}

QStringList *MainWindow::getListeGroupe()
{
    return listeGroupe;
}

QVector<QStringList> *MainWindow::getTabListeSecteur()
{
    return tabListeSecteur;
}

QVector<QVector<QStringList>> *MainWindow::getTabListePatient()
{
    return tabListePatient;
}

void MainWindow::voirGroupe()
{
    WindowViewGroupe *viewGroupe = new WindowViewGroupe(this);
    viewGroupe->show();
}

void MainWindow::voirSecteur()
{
    WindowViewSecteur *viewSecteur = new WindowViewSecteur(this);
    viewSecteur->show();
}

void MainWindow::voirPatient()
{
    WindowViewPatient *viewPatient = new WindowViewPatient(this);
    viewPatient->show();
}

void MainWindow::voirProduit()
{
    WindowViewProduit *viewProduit = new WindowViewProduit(this);
    viewProduit->show();
}

void MainWindow::createOrdo()
{
    CentralWidgetOrdonnance *cwo = new CentralWidgetOrdonnance(this);
    setCentralWidget(cwo);
}
