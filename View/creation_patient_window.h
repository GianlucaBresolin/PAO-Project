#ifndef CREATION_PATIENT_WINDOW_H
#define CREATION_PATIENT_WINDOW_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QLineEdit>
#include "patient.h"
#include "container_template.h"
#include "error_window.h"

class Creation_patient_window:public QDialog{
    Q_OBJECT
    private:
    Container<Patient*>& patients_list;
    QLineEdit* lineEdit_name;
    QLineEdit* lineEdit_surname;
    QLineEdit* lineEdit_birth_date;
    QLineEdit* lineEdit_codice_fiscale;

    public:
        Creation_patient_window(Container<Patient*>& lista_pazienti, QWidget* parent=nullptr);

    signals:
        void clear_for_add();

    public slots:
        void add_patient();
};

#endif
