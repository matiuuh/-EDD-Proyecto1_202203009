#include "buttondelegateenviadas.h"
#include <QHBoxLayout>
#include <QPushButton>

ButtonDelegateEnviadas::ButtonDelegateEnviadas(QObject *parent, const QString &buttonText)
    : QStyledItemDelegate(parent), buttonText(buttonText) {}

QWidget *ButtonDelegateEnviadas::createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &index) const {
    QWidget *widget = new QWidget(parent);
    QHBoxLayout *layout = new QHBoxLayout(widget);

    // Crear el botón para cancelar la solicitud
    QPushButton *button = new QPushButton(buttonText, widget);

    layout->addWidget(button);
    layout->setContentsMargins(0, 0, 0, 0);

    widget->setLayout(layout);

    // Conectar el botón a la acción de cancelar solicitud
    connect(button, &QPushButton::clicked, [this, index]() {
        emit solicitudCancelada(index); // Emitir la señal cuando se hace clic en Cancelar
    });

    return widget;
}

void ButtonDelegateEnviadas::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &) const {
    editor->setGeometry(option.rect);
}
