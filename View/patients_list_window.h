#ifndef PATIENTS_LIST_WINDOW_H
#define PATIENTS_LIST_WINDOW_H

#include <QDialog>
#include <QHBoxLayout>
#include "patient.h"
#include "container_template.h"
#include "medical_history.h"
#include "patients_list.h"

class Patients_list_window: public QDialog{
    Q_OBJECT
    public:
        Patients_list_window(Container<Patient*>& lista_pazienti, Container<Medical_history*>& lista_cartelle_mediche_unsettled, Container<Medical_history*>& lista_cartelle_mediche_white, Container<Medical_history*>& lista_cartelle_mediche_green, Container<Medical_history*>& lista_cartelle_mediche_blue, Container<Medical_history*>& lista_cartelle_mediche_orange, Container<Medical_history*>& lista_cartelle_mediche_red, QWidget* parent=nullptr);
    signals:
        void clear_list();
        void save();
};

#endif
