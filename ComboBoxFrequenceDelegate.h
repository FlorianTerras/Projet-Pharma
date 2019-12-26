#ifndef COMBOBOXFREQUENCEDELEGATE_H
#define COMBOBOXFREQUENCEDELEGATE_H

#include "mainwindow.h"
#include "centralwidgetordonnance.h"
#include <QDebug>

class ComboBoxFrequenceDelegate : public QStyledItemDelegate
{
    Q_OBJECT
    Q_DISABLE_COPY(ComboBoxFrequenceDelegate)
    public:
        explicit ComboBoxFrequenceDelegate(CentralWidgetOrdonnance *cwo, QObject* parent = Q_NULLPTR) : QStyledItemDelegate(parent)
        {
            cwo_ = cwo;
        }

        QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &/* option */, const QModelIndex &/* index */) const
        {
            QComboBox *editor = new QComboBox(parent);
            QStringList *sl = new QStringList();
            *sl << "" << "tous" << "1/2" << "1/3" << "2/3" << "1/4" << "1/5" << "1/6"
                << "1/7" << "5/7" << "6/7" << "3 semaines sur 4" << "sur mesure (pas encore implémenté)";
            editor->addItems(*sl);
            return editor;
        }

        void setEditorData(QWidget *editor, const QModelIndex &index) const
        {
            QString value = index.model()->data(index, Qt::EditRole).toString();
            QComboBox *cb = static_cast<QComboBox*>(editor);
            cb->setCurrentText(value);
        }

        void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
        {
            QComboBox *lineEdit = static_cast<QComboBox*>(editor);
            QString value = lineEdit->currentText();
            model->setData(index, value, Qt::EditRole);
        }

        void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
        {
            editor->setGeometry(option.rect);
        }

    private:
        CentralWidgetOrdonnance *cwo_;
};

#endif // COMBOBOXFREQUENCEDELEGATE_H
