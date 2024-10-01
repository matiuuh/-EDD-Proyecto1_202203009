#include "buttondelegateeliminardef.h"
#include <QHBoxLayout>
#include <QPushButton>

ButtonDelegateEliminarDef::ButtonDelegateEliminarDef(QObject *parent, const QString &buttonText)
    : QStyledItemDelegate(parent), buttonText(buttonText) {}

QWidget *ButtonDelegateEliminarDef::createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &index) const {
    QWidget *widget = new QWidget(parent);
    QHBoxLayout *layout = new QHBoxLayout(widget);

    // Crear botón basado en el texto proporcionado
    QPushButton *button = new QPushButton(buttonText, widget);
    layout->addWidget(button);
    layout->setContentsMargins(0, 0, 0, 0);
    widget->setLayout(layout);

    // Conectar el botón según la acción
    if (buttonText == "Eliminar") {
        connect(button, &QPushButton::clicked, [this, index]() {
            emit publicacionEliminada(index); // Emitir señal de eliminación
        });
    } else if (buttonText == "Comentarios") {
        connect(button, &QPushButton::clicked, [this, index]() {
            emit mostrarComentarios(index); // Emitir señal para mostrar comentarios
        });
    }

    return widget;
}

void ButtonDelegateEliminarDef::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &) const {
    editor->setGeometry(option.rect);
}
