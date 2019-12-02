#ifndef SPINBOXDELEGATE_H
#define SPINBOXDELEGATE_H

#endif // SPINBOXDELEGATE_H

#include "mainwindow.h"

class SpinBoxDelegate : public QStyledItemDelegate{
    Q_OBJECT
    Q_DISABLE_COPY(SpinBoxDelegate)
public:
    explicit SpinBoxDelegate(QObject* parent = Q_NULLPTR) : QStyledItemDelegate(parent)
    {
    }

    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE
    {
        Q_UNUSED(option)
        Q_UNUSED(index)
        return new QSpinBox(parent);
    }

    void  setEditorData(QWidget *editor, const QModelIndex &index) const Q_DECL_OVERRIDE
    {
       static_cast<QSpinBox>(editor).setValue(index.data().toInt());
    }

    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const Q_DECL_OVERRIDE
    {
        model->setData(index, static_cast<QSpinBox>(editor).value());
    }

    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE
    {
        Q_UNUSED(index)
        editor->setGeometry(option.rect);
    }

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE
    {
        qApp->style()->sizeFromContents(
                QStyle::CT_SpinBox,
                &option,
                QSize(option.fontMetrics.horizontalAdvance(displayText(index.data(),option.locale)), option.fontMetrics.height())
        );
        return (QSize());
    }
};
