#include "ButtonDelegateTablaAdmin.h"
#include <QPushButton>
#include <QHBoxLayout>

ButtonDelegateTablaAdmin::ButtonDelegateTablaAdmin(QObject *parent)
    : QStyledItemDelegate(parent) {}

QWidget* ButtonDelegateTablaAdmin::createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &index) const {
    QWidget *widget = new QWidget(parent);
    QHBoxLayout *layout = new QHBoxLayout(widget);

    QPushButton *button = new QPushButton(widget);

    // Asignar el texto adecuado según la columna
    if (index.column() == 4) {
        button->setText("Modificar");
        connect(button, &QPushButton::clicked, [this, index]() {
            emit modificarUsuario(index);
        });
    } else if (index.column() == 5) {
        button->setText("Eliminar");
        connect(button, &QPushButton::clicked, [this, index]() {
            emit eliminarUsuario(index);
        });
    }

    layout->addWidget(button);
    layout->setContentsMargins(0, 0, 0, 0);
    widget->setLayout(layout);

    return widget;
}

void ButtonDelegateTablaAdmin::setEditorData(QWidget *, const QModelIndex &) const {}

void ButtonDelegateTablaAdmin::setModelData(QWidget *, QAbstractItemModel *, const QModelIndex &) const {}

void ButtonDelegateTablaAdmin::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &) const {
    editor->setGeometry(option.rect);
}
