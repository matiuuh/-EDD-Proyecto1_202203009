#ifndef BUTTONDELEGATETABLAADMIN_H
#define BUTTONDELEGATETABLAADMIN_H

#include <QStyledItemDelegate>
#include <QPushButton>
#include <QWidget>

class ButtonDelegateTablaAdmin : public QStyledItemDelegate {
    Q_OBJECT
public:
    explicit ButtonDelegateTablaAdmin(QObject *parent = nullptr);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

signals:
    void modificarUsuario(const QModelIndex &index) const;
    void eliminarUsuario(const QModelIndex &index) const;

private:
    QString buttonText; // Nueva variable para almacenar el texto del botón
};

#endif // BUTTONDELEGATETABLAADMIN_H
