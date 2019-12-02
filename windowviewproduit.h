#ifndef WINDOWVIEWPRODUIT_H
#define WINDOWVIEWPRODUIT_H

#include "mainwindow.h"
#include "tablemodelpatient.h"

class WindowViewProduit : public QWidget
{
    public:
        WindowViewProduit(MainWindow *parent);

    private:
        MainWindow *parent_t;
};

#endif // WINDOWVIEWPRODUIT_H
