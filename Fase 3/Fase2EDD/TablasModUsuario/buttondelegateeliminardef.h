#ifndef BUTTONDELEGATEELIMINARDEF_H
#define BUTTONDELEGATEELIMINARDEF_H

#include <QStyledItemDelegate>
#include <QObject>

class ButtonDelegateEliminarDef : public QStyledItemDelegate {
    Q_OBJECT
public:
    explicit ButtonDelegateEliminarDef(QObject *parent = nullptr, const QString &buttonText = QString());

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

signals:
    void publicacionEliminada(const QModelIndex &index) const;
    void mostrarComentarios(const QModelIndex &index) const;

private:
    QString buttonText;
};

#endif // BUTTONDELEGATEELIMINARDEF_H
