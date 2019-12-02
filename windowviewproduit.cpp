#include "windowviewproduit.h"

WindowViewProduit::WindowViewProduit(MainWindow *parent)
{
    parent_t = parent;
    this->setParent(parent);
    QVBoxLayout *VBL = new QVBoxLayout;
    QTableView *view = new QTableView(this);
    this->setWindowFlag(Qt::Window);
    this->setWindowTitle("Produits");
    this->resize(1700, 850);
    TableModelPatient *model = new TableModelPatient();
    model->populateData(parent_t->getStrFile(parent_t->getFilename(2)));
    view->setModel(model);
    view->resizeColumnsToContents();
    view->setSelectionBehavior(QAbstractItemView::SelectRows);

/*    QHBoxLayout *HBL = new QHBoxLayout();
    QPushButton *button_ajouter = new QPushButton("Ajouter");
    HBL->addWidget(button_ajouter);
    QPushButton *button_modifier = new QPushButton("Modifier");
    HBL->addWidget(button_modifier);
    QPushButton *button_supprimer = new QPushButton("Supprimer");
    HBL->addWidget(button_supprimer);
    HBL->setAlignment(Qt::AlignBottom);*/
    VBL->addWidget(view);
//    VBL->addLayout(HBL);
    this->setLayout(VBL);
}
