#include "centralwidgetordonnance.h"
#include "lineeditproduitdelegate.h"

CentralWidgetOrdonnance::CentralWidgetOrdonnance(MainWindow *parent)
{
    parent_t = parent;
    this->setParent(parent);
    listeProduit = new QStringList;
    listeCodePrdt = new QStringList;
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
//    VBL->addWidget(infoOrdo);
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
    label = new QLabel("Prénom", infoOrdo);
    GL->addWidget(label, 1, 1);
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
    lineEdit = new QLineEdit;
    GL->addWidget(lineEdit, 2, 0);
    lineEdit = new QLineEdit;
    GL->addWidget(lineEdit, 2, 1);
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
    QSpinBox *lineEditDuree = new QSpinBox();                 //duree
    lineEditDuree->setValue(strDuree.toInt());
//    lineEditDuree->setSuffix(" jours");
    lineEditDuree->setRange(0,9999);
    GL->addWidget(lineEditDuree, 4, 1);
    lineEditDateFin = new QLineEdit(dateFin->toString(Qt::SystemLocaleShortDate));  //Fin
    GL->addWidget(lineEditDateFin, 4, 2);
    lineEditDateFin->setReadOnly(true);
    QSpinBox *spinbox = new QSpinBox();                                 //Renouvellement
    spinbox->setValue(0);
    GL->addWidget(spinbox, 4, 3, 1, 2);
    GL->setAlignment(Qt::AlignTop);

    connect(dateEditDebut, SIGNAL(dateChanged(const QDate &)), this, SLOT(saveDateDebut(const QDate &)));
    connect(lineEditDuree, SIGNAL(valueChanged(const QString &)), this, SLOT(saveStrDuree(const QString &)));
    connect(lineEditDuree, SIGNAL(valueChanged(QString)), this, SLOT(changeDateFin()));
    connect(dateEditDebut, SIGNAL(dateChanged(QDate)), this, SLOT(changeDateFin()));
    return (infoOrdo);
}

QWidget *CentralWidgetOrdonnance::createListWidget()
{
    tmpFile = new QTemporaryFile;
    if (!tmpFile->open()) {
        QMessageBox::critical(this, "Erreur", "Impossible d'ouvrir " + tmpFile->fileName());
        return(nullptr);
    }
    QTextStream in(tmpFile);
    in << QString("Code;Produit;Matin;Midi;Soir;Couché;??H;??H;Fréquence;Durée;Si besoin;commentaire;\n;;;;;;;;;;;;\n");
    in.flush();
    in.seek(0);
    QString str = in.readAll();
    tmpFile->close();
    QWidget *list = new QWidget(this);
    list->setAutoFillBackground(true);
    list->setPalette(Qt::lightGray);
    QHBoxLayout *layout = new QHBoxLayout(list);
    tableView = new QTableView(list);
    layout->setMargin(2);
    layout->addWidget(tableView);
    model = new TableModelOrdo();
    model->populateData(str);
    tableView->setModel(model);
    tableView->resizeColumnsToContents();
    for (int i = 0; tableView->columnAt(i) != -1; i++)
        tableView->setColumnWidth(i, tableView->columnWidth(i) + 30);
    tableView->setColumnWidth(1, tableView->columnWidth(1) + 180);
    tableView->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::AnyKeyPressed);
    tableView->setItemDelegateForColumn(1,  new LineEditProduitDelegate(this, tableView));
    QVBoxLayout *VBL = new QVBoxLayout;
    layout->addLayout(VBL);
    QPushButton *buttonAdd = new QPushButton("+");
    QPushButton *buttonSuppr = new QPushButton("-");
    buttonAdd->setAutoFillBackground(true);
    buttonAdd->setPalette(QPalette(Qt::blue));
    buttonSuppr->setAutoFillBackground(true);
    buttonSuppr->setPalette(QPalette(Qt::red));
    VBL->addWidget(buttonAdd);
    VBL->addWidget(buttonSuppr);
    VBL->setAlignment(Qt::AlignTop);

    connect(model, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(actualiserList(const QModelIndex &)));
    connect(buttonAdd, SIGNAL(clicked()), this, SLOT(addProduit()));
    connect(buttonSuppr, SIGNAL(clicked()), model, SLOT(getData()));
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
    TableModelOrdo *model = new TableModelOrdo();
    tableView->setModel(model);
    tableView->resizeColumnsToContents();
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QHBoxLayout *HBL = new QHBoxLayout;
    layout->addLayout(HBL);
    QPushButton *buttonVal = new QPushButton("Valider");
    buttonVal->setAutoFillBackground(true);
    buttonVal->setPalette(QPalette(Qt::green));
    QPushButton *buttonSuppr = new QPushButton("Annuler");
    HBL->addWidget(buttonVal);
    HBL->addWidget(buttonSuppr);
    HBL->setAlignment(Qt::AlignLeft);

    connect(buttonVal, SIGNAL(clicked()), this, SLOT(valider()));

    return history;
}

void CentralWidgetOrdonnance::actualiserList(const QModelIndex &index)
{
    QString mlo = model->getData();
    QStringList mloSplit = mlo.split("\n");

    if (index.column() == 1) {
        QString data = index.data().toString();
        QStringList splitSplit = mloSplit.value(index.row() + 1).split(";");
        for(int i = 0; i < listeProduit->length(); i++)
            if (listeProduit->value(i) == data) {
                splitSplit.replace(0, listeCodePrdt->value(i));
                qDebug() << "Code produit n°" << i << " : " << listeCodePrdt->value(i);
                QString lkj;
                for (int j = 0; j < splitSplit.length() - 1; j++)
                {
                    lkj.append(splitSplit.value(j));
                    lkj.append(";");
                }
                mloSplit.replace(index.row() + 1, lkj);
                mlo.clear();
                for (int j = 0; j < mloSplit.length() && !mloSplit.value(j).isEmpty(); j++)
                {
                    mlo.append(mloSplit.value(j));
                    mlo.append("\n");
                }
                qDebug() << "mlo : " << mlo;
                break;
            }
    } else if (index.column() == 0) {
        QString data = index.data().toString();
        QStringList splitSplit = mloSplit.value(index.row() + 1).split(";");
        for(int i = 0; i < listeCodePrdt->length(); i++)
            if (listeCodePrdt->value(i) == data) {
                splitSplit.replace(1, listeProduit->value(i));
                qDebug() << "liste produit n°" << i << " : " << listeProduit->value(i);
                QString lkj;
                for (int j = 0; j < splitSplit.length() - 1; j++)
                {
                    lkj.append(splitSplit.value(j));
                    lkj.append(";");
                }
                mloSplit.replace(index.row() + 1, lkj);
                mlo.clear();
                for (int j = 0; j < mloSplit.length() && !mloSplit.value(j).isEmpty(); j++) {
                    mlo.append(mloSplit.value(j));
                    mlo.append("\n");
                }
                qDebug() << "mlo : " << mlo;
                break;
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
            model->removeRow(i);
        }
    }
    if (mloSplit.value(mloSplit.length() - 2) != ";;;;;;;;;;;;") {
        mlo.append(";;;;;;;;;;;;\n");
    }
    model->populateData(mlo);
    model->insertRow(model->rowCount(QModelIndex()));
    tableView->resizeColumnsToContents();
    for (int i = 0; tableView->columnAt(i) != -1; i++)
        tableView->setColumnWidth(i, tableView->columnWidth(i) + 30);
    if (!tmpFile->open()) {
        QMessageBox::critical(this, "Erreur", "Impossible d'ouvrir " + tmpFile->fileName());
        return;
    }
    QTextStream tmpio(tmpFile);
    tmpio << mlo;
    tmpFile->close();
}

void CentralWidgetOrdonnance::addProduit()
{
/*    if (!tmpFile->open()) {
        QMessageBox::critical(this, "Erreur", "Impossible d'ouvrir " + tmpFile->fileName());
        return;
    }
    QTextStream in(tmpFile);
    QString str = in.readAll();
    in << str << "Medecin;Nom;Matin;Midi;Soir;Couché;??H;??H;\nTANNYERES;EFFERALGAN 500MG;1;0;0;1;0;0;\n"; // mettre le produit a ajouter

    in.flush();
    in.seek(0);*/

    QWidget *window = new QWidget(this, Qt::Dialog);
    window->setWindowTitle("Ajouter un produit");
    QVBoxLayout *VBL = new QVBoxLayout(window);
    QGridLayout *QGL = new QGridLayout;
    VBL->addLayout(QGL);
    QGL->setAlignment(Qt::AlignTop);
    QLineEdit *code = new QLineEdit;
    QLineEdit *nomProduit = new QLineEdit;
    QLineEdit *matin = new QLineEdit;
    QLineEdit *midi = new QLineEdit;
    QLineEdit *soir = new QLineEdit;
    QLineEdit *heure1 = new QLineEdit;
    QLineEdit *heure2 = new QLineEdit;
    QLineEdit *duree = new QLineEdit;
    QLabel *label = new QLabel("Code :");
    QGL->addWidget(label, 0, 0);
    QGL->addWidget(code, 1, 0, 1, 3);
    label = new QLabel("Produit :");
    QGL->addWidget(label, 2, 0);
    QGL->addWidget(nomProduit, 3, 0, 1, 3);
    nomProduit->setFocus();
    fillListeProduit();
    QCompleter *completer = new QCompleter(*listeProduit, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    nomProduit->setCompleter(completer);
    label = new QLabel("Matin :");
    QGL->addWidget(label, 4, 0);
    QGL->addWidget(matin, 5, 0);
    label = new QLabel("Midi :");
    QGL->addWidget(label, 4, 1);
    QGL->addWidget(midi, 5, 1);
    label = new QLabel("Soir :");
    QGL->addWidget(label, 4, 2);
    QGL->addWidget(soir, 5, 2);
    label = new QLabel("Heure 1 :");
    QGL->addWidget(label, 4, 3);
    QGL->addWidget(heure1, 5, 3);
    label = new QLabel("Heure 2 :");
    QGL->addWidget(label, 4, 4);
    QGL->addWidget(heure2, 5, 4);
    label = new QLabel("Durée (jours) :");
    QGL->addWidget(label, 6, 0);
    QGL->addWidget(duree, 7, 0);
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

    connect(buttonAnnuler, &QPushButton::clicked, window, &QWidget::close);
}

void CentralWidgetOrdonnance::fillListeProduit()
{
    QStringList newlist;
    QStringList strlist = parent_t->getStrFile(parent_t->getFilename(2)).split("\n");
    for (int i = 1; i < strlist.length(); i++)
    {
        newlist.append(strlist.value(i).split(";").value(0));
    }
    listeProduit->clear();
    *listeProduit = newlist;
    newlist.clear();
    for (int i = 1; i < strlist.length(); i++)
    {
        newlist.append(strlist.value(i).split(";").value(1));
    }
    listeCodePrdt->clear();
    *listeCodePrdt = newlist;
}

void CentralWidgetOrdonnance::saveDateDebut(const QDate &date)
{
    *dateDebut = date;
}

void CentralWidgetOrdonnance::saveStrDuree(const QString &str)
{
    strDuree = str;
}

void CentralWidgetOrdonnance::changeDateFin()
{
    QDate date = dateDebut->addDays(strDuree.toInt());
    lineEditDateFin->setText(date.toString(Qt::SystemLocaleShortDate));
}


void CentralWidgetOrdonnance::valider()
{
    if (!tmpFile->open()) {
        QMessageBox::critical(this, "Erreur", "Impossible d'ouvrir " + tmpFile->fileName());
        return;
    }
    QTextStream tmpio(tmpFile);
    tmpio.seek(0);
    writeFile(tmpio.readAll());
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
    in << str;

    qDebug() << "Write : " << str;

    QMessageBox::information(this, "", "Ordonnance enregistrée\n\nChemin d'accès :" + filename);
}

QStringList *CentralWidgetOrdonnance::getListeProduit()
{
    return listeProduit;
}
