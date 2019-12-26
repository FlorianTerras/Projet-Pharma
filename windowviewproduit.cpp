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
    VBL->addWidget(view);
    this->setLayout(VBL);
}
