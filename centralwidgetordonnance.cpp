#include "centralwidgetordonnance.h"
#include "lineeditproduitdelegate.h"
#include "ComboBoxFrequenceDelegate.h"

CentralWidgetOrdonnance::CentralWidgetOrdonnance(MainWindow *parent)
{
    parent_t = parent;
    this->setParent(parent);
    listeProduit = new QStringList;
    listeCodePrdt = new QStringList;
    listeNomMedecin = new QStringList;
    renouvellement = 0;
    fillListeProduit();
    QGridLayout *VBL = new QGridLayout;
    this->setLayout(VBL);
    VBL->setMargin(3);
    VBL->addWidget(createInfoWidget(), 0, 0, 1, 1);
    VBL->addWidget(createListWidget(), 1, 0, 2, 1);
    VBL->addWidget(createHistoryWidget(), 3, 0, 2, 1);
}

QWidget *CentralWidgetOrdonnance::createInfoWidget()
{
    QStringList strlist = parent_t->getSelectedPatient(); // contient les infos du patient selectionné
    QWidget *infoOrdo = new QWidget(this);
    strDuree = "28";
    datePrescr = new QDate(QDate::currentDate());
    dateDebut = new QDate(QDate::currentDate());
    dateFin = new QDate(dateDebut->addDays(strDuree.toInt()));

    QHBoxLayout *HBL = new QHBoxLayout;
    infoOrdo->setLayout(HBL);
    HBL->setAlignment(Qt::AlignTop);
    QFrame *frame = new QFrame;
    QGridLayout *GL = new QGridLayout;
    HBL->addWidget(frame);
    frame->setLayout(GL);
    frame->setFrameShape(QFrame::Box);
    frame->setFrameShadow(QFrame::Sunken);
    frame->setAutoFillBackground(true);
    frame->setPalette(QPalette(Qt::lightGray));
    QPalette *pal = new QPalette;
    pal->setColor(QPalette::Background, Qt::white);
    this->setAutoFillBackground(true);
    this->setPalette(*pal);
    QLabel *image = new QLabel(infoOrdo);
    image->setPixmap(QPixmap("Data/Default-Profile-Male.jpg"));
    GL->addWidget(image, 0, 0, 8, 1);
    QLabel *label = new QLabel("Patient", infoOrdo);
    GL->addWidget(label, 0, 1);
    label = new QLabel("Nom", infoOrdo);
    GL->addWidget(label, 1, 1);
    label = new QLabel("Prénom", infoOrdo);
    GL->addWidget(label, 1, 2);
    label = new QLabel("N° INSEE", infoOrdo);
    GL->addWidget(label, 3, 1);
    QLineEdit *lineEdit = new QLineEdit(strlist.value(1));
    GL->addWidget(lineEdit, 2, 1);
    lineEdit = new QLineEdit(strlist.value(2));
    GL->addWidget(lineEdit, 2, 2);
    lineEdit = new QLineEdit(strlist.value(3));
    GL->addWidget(lineEdit, 4, 1);
    GL->setAlignment(Qt::AlignTop);

    GL = new QGridLayout;
    frame = new QFrame;
    HBL->addWidget(frame);
    frame->setLayout(GL);
    frame->setFrameShape(QFrame::Box);
    frame->setFrameShadow(QFrame::Sunken);
    frame->setAutoFillBackground(true);
    frame->setPalette(QPalette(Qt::lightGray));
    label = new QLabel("Médecin / info ordonnance", infoOrdo);
    GL->addWidget(label, 0, 0, 1, 4);
    label = new QLabel("Nom", infoOrdo);
    GL->addWidget(label, 1, 0);
    label = new QLabel("Date de préscription", infoOrdo);
    GL->addWidget(label, 1, 2);
    label = new QLabel("Date de début", infoOrdo);
    GL->addWidget(label, 3, 0);
    label = new QLabel("Durée", infoOrdo);
    GL->addWidget(label, 3, 1);
    label = new QLabel("Date de fin", infoOrdo);
    GL->addWidget(label, 3, 2);
    label = new QLabel("Renouvellable", infoOrdo);
    GL->addWidget(label, 3, 3, 1, 2);
    QLineEdit *lineEditNomMedecin = new QLineEdit;
    QCompleter *completer = new QCompleter(*listeNomMedecin, lineEditNomMedecin);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    lineEditNomMedecin->setCompleter(completer);
    GL->addWidget(lineEditNomMedecin, 2, 0);
    QDateEdit *dateEdit = new QDateEdit(*datePrescr);//date presc
    dateEdit->setDisplayFormat("dd/MM/yyyy");
    dateEdit->setCalendarPopup(true);
    QCalendarWidget *calendar = new QCalendarWidget;
    calendar->setGridVisible(true);
    dateEdit->setCalendarWidget(calendar);
    GL->addWidget(dateEdit, 2, 2);
    QDateEdit *dateEditDebut = new QDateEdit(*dateDebut);//debut
    dateEditDebut->setDisplayFormat("dd/MM/yyyy");
    dateEditDebut->setCalendarPopup(true);
    calendar = new QCalendarWidget;
    calendar->setGridVisible(true);
    dateEditDebut->setCalendarWidget(calendar);
    GL->addWidget(dateEditDebut, 4, 0);
    QSpinBox *spinBoxDuree = new QSpinBox();    //duree
    spinBoxDuree->setValue(strDuree.toInt());
    spinBoxDuree->setRange(0,9999);
    GL->addWidget(spinBoxDuree, 4, 1);
    lineEditDateFin = new QLineEdit(dateFin->toString(Qt::SystemLocaleShortDate));  //Fin
    GL->addWidget(lineEditDateFin, 4, 2);
    lineEditDateFin->setReadOnly(true);
    QSpinBox *spinbox = new QSpinBox(); //Renouvellement
    spinbox->setValue(0);
    GL->addWidget(spinbox, 4, 3, 1, 2);
    GL->setAlignment(Qt::AlignTop);

    connect(dateEditDebut, SIGNAL(dateChanged(const QDate &)), this, SLOT(saveDateDebut(const QDate &)));
    connect(spinBoxDuree, SIGNAL(valueChanged(const QString &)), this, SLOT(saveStrDuree(const QString &)));
    connect(spinBoxDuree, SIGNAL(valueChanged(QString)), this, SLOT(changeDateFin()));
    connect(spinbox, SIGNAL(valueChanged(int)), this, SLOT(saveRenouvellement(int)));
    connect(lineEditNomMedecin, SIGNAL(textChanged(const QString &)), this, SLOT(saveNomMedecin(const QString &)));
    connect(dateEditDebut, SIGNAL(dateChanged(QDate)), this, SLOT(changeDateFin()));
    return (infoOrdo);
}

QWidget *CentralWidgetOrdonnance::createListWidget()
{
    tmpString = new QString;
    *tmpString = "Code;Produit;Matin;Midi;Soir;Couché;??H;??H;Fréquence;Durée;Si besoin;commentaire;\n;;;;;;;;;;;;\n";
    QString str = *tmpString;
    QWidget *list = new QWidget(this);
    list->setAutoFillBackground(true);
    list->setPalette(Qt::lightGray);
    QHBoxLayout *layout = new QHBoxLayout(list);
    tableView = new QTableView(list);
    layout->setMargin(2);
    layout->addWidget(tableView);
    modelO = new TableModelOrdo();
    modelO->populateData(str);
    tableView->setModel(modelO);
    tableView->resizeColumnsToContents();
    for (int i = 0; tableView->columnAt(i) != -1; i++)
        tableView->setColumnWidth(i, tableView->columnWidth(i) + 30);
    tableView->setColumnWidth(1, tableView->columnWidth(1) + 180);
    tableView->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::AnyKeyPressed);
    tableView->setItemDelegateForColumn(1, new LineEditProduitDelegate(this, tableView));
    tableView->setItemDelegateForColumn(8, new ComboBoxFrequenceDelegate(this, tableView));

    connect(modelO, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(actualiserList(const QModelIndex &)));
    return list;
}

QWidget *CentralWidgetOrdonnance::createHistoryWidget()
{
    QWidget *history = new QWidget(this);
    history->setAutoFillBackground(true);
    history->setPalette(Qt::lightGray);
    QVBoxLayout *layout = new QVBoxLayout(history);
    QTableView *tableView = new QTableView(history);
    layout->setMargin(2);
    layout->addWidget(tableView);
    modelH = new TableModelHistory(*modelO, this);

    QHBoxLayout *HBL = new QHBoxLayout;
    layout->addLayout(HBL);
    QPushButton *buttonVal = new QPushButton("Valider");
    buttonVal->setAutoFillBackground(true);
    buttonVal->setPalette(QPalette(Qt::green));
    QPushButton *buttonAnnul = new QPushButton("Annuler");
    HBL->addWidget(buttonVal);
    HBL->addWidget(buttonAnnul);
    HBL->setAlignment(Qt::AlignLeft);

    QStringList strlist = parent_t->getSelectedPatient();
    QString filename = strlist.value(1) + "-" + strlist.value(2) + "-" + strlist.value(3);
    filename = "Data/ordonnances/" + filename + ".txt";
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        modelH->populateData(";;;;;;;;;;;;;;;;");
    } else {
        QTextStream out(&file);
        QString data = out .readAll();
        modelH->populateData(data);
    }
    QSortFilterProxyModel *m=new QSortFilterProxyModel(tableView);
    m->setDynamicSortFilter(true);
    m->setSourceModel(modelH);
    tableView->setModel(m);
    tableView->setSortingEnabled(true);
    tableView->sortByColumn(1, Qt::DescendingOrder);
/*    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setFocusPolicy(Qt::NoFocus);*/
    tableView->setSelectionMode(QAbstractItemView::NoSelection);
    tableView->resizeColumnsToContents();

    connect(modelO, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), modelH, SLOT(compare()));
    connect(buttonVal, SIGNAL(clicked()), this, SLOT(valider()));
    connect(buttonAnnul, SIGNAL(clicked()), this, SLOT(annuler()));
    return history;
}

void CentralWidgetOrdonnance::actualiserList(const QModelIndex &index)
{
    QString mlo = modelO->getData();
    QStringList mloSplit = mlo.split("\n");

    // gère l'autoremplissage du code produit ou du nom produit selon la colonne remplie
    if (index.column() == 1) {
        QString data = index.data().toString();
        QStringList splitSplit = mloSplit.value(index.row() + 1).split(";");
        for(int i = 0; i < listeProduit->length(); i++)
            if (listeProduit->value(i) == data && !data.isEmpty()) {
                splitSplit.replace(0, listeCodePrdt->value(i));
                QString lkj;
                for (int j = 0; j < splitSplit.length() - 1; j++) {
                    if (j >= 2 && j <= 7 && splitSplit.value(j) == "")
                        lkj.append("0");
                    else if (j == 9 && splitSplit.value(j) == "") {
                        int bd = strDuree.toInt() * (1 + renouvellement);
                        lkj.append(QString::number(bd));
                    } else
                        lkj.append(splitSplit.value(j));
                    lkj.append(";");
                }
                mloSplit.replace(index.row() + 1, lkj);
                mlo.clear();
                for (int j = 0; j < mloSplit.length() && !mloSplit.value(j).isEmpty(); j++) {
                    mlo.append(mloSplit.value(j));
                    mlo.append("\n");
                }
                break;
            }
    } else if (index.column() == 0) {
        QString data = index.data().toString();
        QStringList splitSplit = mloSplit.value(index.row() + 1).split(";");
        for(int i = 0; i < listeCodePrdt->length(); i++) {
            if (listeCodePrdt->value(i) == data && !data.isEmpty()) {
                splitSplit.replace(1, listeProduit->value(i));
                QString lkj;
                for (int j = 0; j < splitSplit.length() - 1; j++) {
                    if (j >= 2 && j <= 7 && splitSplit.value(j) == "")
                        lkj.append("0");
                    else if (j == 9 && splitSplit.value(j) == "")
                        lkj.append(strDuree);
                    else
                        lkj.append(splitSplit.value(j));
                    lkj.append(";");
                }
                mloSplit.replace(index.row() + 1, lkj);
                mlo.clear();
                for (int j = 0; j < mloSplit.length() && !mloSplit.value(j).isEmpty(); j++) {
                    mlo.append(mloSplit.value(j));
                    mlo.append("\n");
                }
                break;
            }
        }
    }
    for(int i = 0; i < mloSplit.length() - 2; i++) {
        if (mloSplit.value(i) == ";;;;;;;;;;;;") {
            mloSplit.removeAt(i);
            mlo.clear();
            for (int j = 0; j < mloSplit.length() && !mloSplit.value(j).isEmpty(); j++) {
                mlo.append(mloSplit.value(j));
                mlo.append("\n");
            }
            modelO->removeRow(i);
        }
    }
    if (mloSplit.value(mloSplit.length() - 2) != ";;;;;;;;;;;;") {
        mlo.append(";;;;;;;;;;;;\n");
    }
    modelO->populateData(mlo);
    tableView->resizeColumnsToContents();
    for (int i = 0; tableView->columnAt(i) != -1; i++)
        tableView->setColumnWidth(i, tableView->columnWidth(i) + 30);
    *tmpString = mlo;
}

void CentralWidgetOrdonnance::fillListeProduit()
{
    QStringList newlist;
    QStringList strlist = parent_t->getStrFile(parent_t->getFilename(2)).split("\n");
    for (int i = 1; i < strlist.length(); i++) {
        newlist.append(strlist.value(i).split(";").value(0));
    }
    listeProduit->clear();
    *listeProduit = newlist;
    newlist.clear();
    for (int i = 1; i < strlist.length(); i++) {
        newlist.append(strlist.value(i).split(";").value(1));
    }
    listeCodePrdt->clear();
    *listeCodePrdt = newlist;
    newlist.clear();
    strlist = parent_t->getStrFile(parent_t->getFilename(3)).split("\n");
    for (int i = 1; i < strlist.length(); i++) {
        newlist.append(strlist.value(i).split(";").value(0));
    }
    listeNomMedecin->clear();
    *listeNomMedecin = newlist;
}

void CentralWidgetOrdonnance::saveDateDebut(const QDate &date)
{
    *dateDebut = date;
}

void CentralWidgetOrdonnance::saveStrDuree(const QString &str)
{
    strDuree = str;
}

void CentralWidgetOrdonnance::saveRenouvellement(int ren)
{
    renouvellement = ren;
    qDebug() << "save renouvellement =" << ren;
}

void CentralWidgetOrdonnance::changeDateFin()
{
    QDate date = dateDebut->addDays(strDuree.toInt());
    lineEditDateFin->setText(date.toString(Qt::SystemLocaleShortDate));
}

void CentralWidgetOrdonnance::saveNomMedecin(const QString &str)
{
    strNomMedecin = str;
}

void CentralWidgetOrdonnance::valider()
{
    writeFile(*tmpString);
    this->close();
    parent_t->setCentralWidget(new CentralWidgetOrdonnance(parent_t));
}

void CentralWidgetOrdonnance::annuler()
{
    this->close();
    QFrame *frame = new QFrame;
    frame->setAutoFillBackground(true);
    frame->setPalette(QColor(Qt::darkGray));
    parent_t->setCentralWidget(frame);
}

void CentralWidgetOrdonnance::writeFile(QString str)
{
    QStringList strlist = parent_t->getSelectedPatient();
    QString filename = strlist.value(1) + "-" + strlist.value(2) + "-" + strlist.value(3);
    filename = "Data/ordonnances/" + filename + ".txt";
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)) {
        QMessageBox::critical(this, "Erreur", "Impossible d'ouvrir " + file.fileName());
        return;
    }
    QTextStream in(&file);
    QStringList sList = str.split("\n");
    for(int i = 1; i < sList.length() - 2; i++) {
        in << strNomMedecin + ";";
        in << datePrescr->toString(Qt::SystemLocaleShortDate) + ";";
        in << strDuree + ";";
        in << dateFin->toString(Qt::SystemLocaleShortDate) + ";";
        in << sList.value(i);
        in << "\n";
    }
    QMessageBox::information(this, "", "Ordonnance enregistrée\n\nChemin d'accès :" + filename);
}

QStringList *CentralWidgetOrdonnance::getListeProduit()
{
    return listeProduit;
}

