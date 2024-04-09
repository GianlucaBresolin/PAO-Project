#ifndef EDIT_PATIENT_WINDOW_H
#define EDIT_PATIENT_WINDOW_H

#include <QDialog>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QLineEdit>
#include "patient.h"
#include "container_template.h"
#include "error_window.h"

class Edit_patient_window: public QDialog{
    Q_OBJECT
    private:
    Patient& patient;
    Container<Patient*>& patients_list;
    QLineEdit* lineEdit_name;
    QLineEdit* lineEdit_surname;
    QLineEdit* lineEdit_birth_date;
    QLineEdit* lineEdit_codice_fiscale;

    public:
        Edit_patient_window(Patient& paziente, Container<Patient*>& lista_pazienti, QWidget* parent=nullptr);
    signals:
        void clear_for_edit();

    public slots:
        void edit_patient();
};

#endif
