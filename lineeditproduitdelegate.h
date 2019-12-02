#ifndef LINEEDITPRODUITDELEGATE_H
#define LINEEDITPRODUITDELEGATE_H

#include "mainwindow.h"
#include "centralwidgetordonnance.h"
#include <QDebug>

class LineEditProduitDelegate : public QStyledItemDelegate
{
    Q_OBJECT
    Q_DISABLE_COPY(LineEditProduitDelegate)
    public:
        explicit LineEditProduitDelegate(CentralWidgetOrdonnance *cwo, QObject* parent = Q_NULLPTR) : QStyledItemDelegate(parent)
        {
            cwo_ = cwo;
        }

        QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &/* option */, const QModelIndex &/* index */) const
        {
            QLineEdit *editor = new QLineEdit(parent);
            QCompleter *completer = new QCompleter(*cwo_->getListeProduit(), parent);
            completer->setCaseSensitivity(Qt::CaseInsensitive);
            editor->setCompleter(completer);
            return editor;
        }

        void setEditorData(QWidget *editor, const QModelIndex &index) const
        {
            QString value = index.model()->data(index, Qt::EditRole).toString();

            QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
            lineEdit->setText(value);
        }

        void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
        {
            QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
        //    lineEdit->returnPressed();
            QString value = lineEdit->text();

            model->setData(index, value, Qt::EditRole);
        }

        void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
        {
            editor->setGeometry(option.rect);
        }

    private:
        CentralWidgetOrdonnance *cwo_;
};

#endif // LINEEDITPRODUITDELEGATE_H
