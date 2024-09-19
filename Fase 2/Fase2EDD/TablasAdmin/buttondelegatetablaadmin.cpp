#include "ButtonDelegateTablaAdmin.h"
#include <QPushButton>
#include <QStyleOptionViewItem>
#include <QAbstractItemModel>
#include <QWidget>

ButtonDelegateTablaAdmin::ButtonDelegateTablaAdmin(QObject *parent)
    : QStyledItemDelegate(parent) {}

// Crear el editor, que en este caso son los botones de Modificar y Eliminar
QWidget* ButtonDelegateTablaAdmin::createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &index) const {
    QPushButton *button = new QPushButton(parent);

    // Asignar el texto adecuado según la columna
    if (index.column() == 1) {
        button->setText("Modificar");
    } else if (index.column() == 2) {
        button->setText("Eliminar");
    }

    return button;
}

// No es necesario cargar datos en los botones, esta función se deja vacía
void ButtonDelegateTablaAdmin::setEditorData(QWidget *, const QModelIndex &) const {
    // No se necesita implementación
}

// No es necesario manipular el modelo de datos con los botones, esta función se deja vacía
void ButtonDelegateTablaAdmin::setModelData(QWidget *, QAbstractItemModel *, const QModelIndex &) const {
    // No se necesita implementación
}

// Ajustar la geometría del botón según el espacio de la celda
void ButtonDelegateTablaAdmin::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &) const {
    editor->setGeometry(option.rect);
}
