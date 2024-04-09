#ifndef OPTION_LIST_H
#define OPTION_LIST_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QFont>
#include "search_patient_window.h"
#include "creation_patient_window.h"
#include "creation_operator_window.h"
#include "patients_list_window.h"
#include "operators_list_window.h"
#include "medical_history_list_window.h"
#include "error_window.h"
#include "patient.h"
#include "nurse.h"
#include "doctor.h"
#include "primary.h"
#include "container_template.h"
#include "file_manager.h"

class Option_list : public QWidget{
    Q_OBJECT
    private:
    Container<Patient*>& patients_list;
    Container<Worker*>& operators_list;
    Container<Medical_history*>& medical_history_unsettled_list;
    Container<Medical_history*>& medical_history_white_list;
    Container<Medical_history*>& medical_history_green_list;
    Container<Medical_history*>& medical_history_blue_list;
    Container<Medical_history*>& medical_history_orange_list;
    Container<Medical_history*>& medical_history_red_list;

    public:
        Option_list(Container<Patient*>& lista_pazienti, Container<Worker*>& lista_operatori, Container<Medical_history*>& lista_cartelle_mediche_unsettled, Container<Medical_history*>& lista_cartelle_mediche_bianco, Container<Medical_history*>& lista_cartelle_mediche_verde, Container<Medical_history*>& lista_cartelle_mediche_blu, Container<Medical_history*>& lista_cartelle_mediche_arancione, Container<Medical_history*>& lista_cartelle_mediche_rosso, QWidget *parent = nullptr);

    signals:
        void clear_patients_list();
        void clear_operators_list();
        void clear_medical_history_list();

    public slots:
        void open_search_patient_window();
        void open_creation_patient_window();
        void open_patients_list_window();
        void open_creation_operator_window();
        void open_operators_list_window();
        void open_medical_history_list_window();
        void save();
};

#endif
