#ifndef BUTTONDELEGATETABLAADMIN_H
#define BUTTONDELEGATETABLAADMIN_H

#include <QStyledItemDelegate>
#include <QPushButton>
#include <QObject>

class ButtonDelegateTablaAdmin : public QStyledItemDelegate {
    Q_OBJECT
public:
    explicit ButtonDelegateTablaAdmin(QObject *parent = nullptr);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // BUTTONDELEGATETABLAADMIN_H
