#ifndef BUTTONDELEGATEENVIADAS_H
#define BUTTONDELEGATEENVIADAS_H

#include <QStyledItemDelegate>
#include <QPushButton>
#include <QWidget>

class ButtonDelegateEnviadas : public QStyledItemDelegate {
    Q_OBJECT
public:
    explicit ButtonDelegateEnviadas(QObject *parent = nullptr, const QString &buttonText = "Cancelar");

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

signals:
    void solicitudCancelada(const QModelIndex &index) const;

private:
    QString buttonText;
};

#endif // BUTTONDELEGATEENVIADAS_H
