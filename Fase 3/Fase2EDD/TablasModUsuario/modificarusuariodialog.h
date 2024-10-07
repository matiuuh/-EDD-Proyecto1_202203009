#ifndef MODIFICARUSUARIODIALOG_H
#define MODIFICARUSUARIODIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>

class ModificarUsuarioDialog : public QDialog {
    Q_OBJECT

public:
    explicit ModificarUsuarioDialog(QWidget *parent = nullptr);

    // Funciones para obtener los valores ingresados
    QString getNombre() const;
    QString getApellido() const;
    QString getCorreo() const;
    QString getContrasenia() const;
    QString getFechaNacimiento() const;

private slots:
    void onAceptar();  // Slot para el botón de Aceptar

private:
    QLineEdit *nombreLineEdit;
    QLineEdit *apellidoLineEdit;
    QLineEdit *correoLineEdit;
    QLineEdit *contraseniaLineEdit;
    QLineEdit *fechaNacimientoLineEdit;
};

#endif // MODIFICARUSUARIODIALOG_H
