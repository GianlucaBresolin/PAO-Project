#ifndef PATIENTS_LIST_H
#define PATIENTS_LIST_H

#include <QWidget>
#include <QListWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "patient.h"
#include "container_template.h"
#include "patient_panel.h"

class Patients_list: public QWidget{
    Q_OBJECT
    private:
    QListWidget* listWidget;
    Container<Patient*>& patients_list;
    Container<Medical_history*>& lista_cartelle_mediche_unsettled;
    Container<Medical_history*>& lista_cartelle_mediche_white;
    Container<Medical_history*>& lista_cartelle_mediche_green;
    Container<Medical_history*>& lista_cartelle_mediche_blue;
    Container<Medical_history*>& lista_cartelle_mediche_orange;
    Container<Medical_history*>& lista_cartelle_mediche_red;
    public:
        Patients_list(Container<Patient*>& lista_pazienti, Container<Medical_history*>& medical_history_unsettled_list, Container<Medical_history*>& medical_history_white_list, Container<Medical_history*>& medical_history_green_list, Container<Medical_history*>& medical_history_blue_list, Container<Medical_history*>& medical_history_orange_list, Container<Medical_history*>& medical_history_red_list, QWidget* parent);
    signals:
        void save();
    public slots:
        void refresh();
};

#endif
