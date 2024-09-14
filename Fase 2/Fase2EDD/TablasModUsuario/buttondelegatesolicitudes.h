#ifndef BUTTONDELEGATESOLICITUDES_H
#define BUTTONDELEGATESOLICITUDES_H

#include <QStyledItemDelegate>
#include <QPushButton>
#include <QWidget>

class ButtonDelegateSolicitudes : public QStyledItemDelegate {
    Q_OBJECT
public:
    explicit ButtonDelegateSolicitudes(QObject *parent = nullptr, const QString &buttonText = "Acción");

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

signals:
    void solicitudAceptada(const QModelIndex &index) const;
    void solicitudRechazada(const QModelIndex &index) const;

private:
    QString buttonText; // Nueva variable para almacenar el texto del botón
};

#endif // BUTTONDELEGATESOLICITUDES_H
