#ifndef PATIENT_PANEL_H
#define PATIENT_PANEL_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "patient.h"
#include "discharges_letters_list.h"
#include "error_window.h"
#include "medical_history.h"
#include "edit_patient_window.h"

class Patient_panel : public QWidget{
    Q_OBJECT
    private:
    const Patient& patient;
    Container<Patient*>& patients_list;
    Container<Medical_history*>& lista_cartelle_mediche_unsettled;
    Container<Medical_history*>& lista_cartelle_mediche_white;
    Container<Medical_history*>& lista_cartelle_mediche_green;
    Container<Medical_history*>& lista_cartelle_mediche_blue;
    Container<Medical_history*>& lista_cartelle_mediche_orange;
    Container<Medical_history*>& lista_cartelle_mediche_red;
    public:
        Patient_panel(const Patient& paziente, Container<Patient*>& lista_pazienti, Container<Medical_history*>& medical_history_unsettled_list, Container<Medical_history*>& medical_history_white_list, Container<Medical_history*>& medical_history_green_list, Container<Medical_history*>& medical_history_blue_list, Container<Medical_history*>& medical_history_orange_list, Container<Medical_history*>& medical_history_red_list, QWidget *parent = nullptr);
    signals:
        void refresh_discharges_letters_list();
        void refresh_patients_list();
    public slots:
        void elenco_lettere_dimissione();
        void elimina_paziente();
        void modifica_paziente();
};

#endif
