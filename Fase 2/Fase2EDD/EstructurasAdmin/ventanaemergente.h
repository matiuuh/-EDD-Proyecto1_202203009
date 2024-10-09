// VentanaEmergente.h
#ifndef VENTANAEMERGENTE_H
#define VENTANAEMERGENTE_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>

class VentanaEmergente : public QDialog {
    Q_OBJECT

public:
    explicit VentanaEmergente(QWidget *parent = nullptr);
    QString getEmail() const;

private:
    QLineEdit *lineEditEmail;
    QPushButton *btnAceptar;
    QPushButton *btnCancelar;
};

#endif // VENTANAEMERGENTE_H
