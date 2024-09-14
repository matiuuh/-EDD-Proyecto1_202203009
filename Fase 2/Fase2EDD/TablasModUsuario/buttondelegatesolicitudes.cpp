#include "buttondelegatesolicitudes.h"
#include <QHBoxLayout>
#include <QPushButton>

ButtonDelegateSolicitudes::ButtonDelegateSolicitudes(QObject *parent, const QString &buttonText)
    : QStyledItemDelegate(parent), buttonText(buttonText) {}

QWidget *ButtonDelegateSolicitudes::createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &index) const {
    QWidget *widget = new QWidget(parent);
    QHBoxLayout *layout = new QHBoxLayout(widget);

    // Usar el texto del botón proporcionado al crear el delegado
    QPushButton *button = new QPushButton(buttonText, widget);

    layout->addWidget(button);
    layout->setContentsMargins(0, 0, 0, 0);

    widget->setLayout(layout);

    // Conectar la señal del botón a las acciones de aceptar o rechazar
    if (buttonText == "Aceptar") {
        connect(button, &QPushButton::clicked, [this, index]() {
            emit solicitudAceptada(index);
        });
    } else if (buttonText == "Rechazar") {
        connect(button, &QPushButton::clicked, [this, index]() {
            emit solicitudRechazada(index);
        });
    }

    return widget;
}

void ButtonDelegateSolicitudes::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &) const {
    editor->setGeometry(option.rect);
}
