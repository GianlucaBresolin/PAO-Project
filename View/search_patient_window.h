#ifndef SEARCH_PATIENT_WINDOW_H
#define SEARCH_PATIENT_WINDOW_H

#include <QDialog>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QGridLayout>
#include "patient.h"
#include "container_template.h"
#include "error_window.h"
#include "creation_medical_history_window.h"

class Search_patient_window: public QDialog{
    Q_OBJECT
    private:
    Container<Patient*>& patients_list;
    Container<Medical_history*>& medical_history_unsettled_list;
    Container<Medical_history*>& medical_history_white_list;
    Container<Medical_history*>& medical_history_green_list;
    Container<Medical_history*>& medical_history_blue_list;
    Container<Medical_history*>& medical_history_orange_list;
    Container<Medical_history*>& medical_history_red_list;
    QLineEdit* lineEdit_name;
    QLineEdit* lineEdit_surname;
    QLineEdit* lineEdit_birth_date;
    QLineEdit* lineEdit_codice_fiscale;
    public:
        Search_patient_window(Container<Patient*>& patients_list, Container<Medical_history*>& lista_cartelle_mediche_unsettled, Container<Medical_history*>& lista_cartelle_mediche_white, Container<Medical_history*>& lista_cartelle_mediche_green, Container<Medical_history*>& lista_cartelle_mediche_blue, Container<Medical_history*>& lista_cartelle_mediche_orange, Container<Medical_history*>& lista_cartelle_mediche_red, QWidget *parent = nullptr);
    signals:
        void clear_medical_history_list();
    public slots:
        void try_creation_medical_history();
};

#endif
