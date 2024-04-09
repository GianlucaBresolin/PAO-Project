#include "patients_list_window.h"

Patients_list_window::Patients_list_window(Container<Patient*>& lista_pazienti, Container<Medical_history*>& lista_cartelle_mediche_unsettled, Container<Medical_history*>& lista_cartelle_mediche_white, Container<Medical_history*>& lista_cartelle_mediche_green, Container<Medical_history*>& lista_cartelle_mediche_blue, Container<Medical_history*>& lista_cartelle_mediche_orange, Container<Medical_history*>& lista_cartelle_mediche_red, QWidget* parent): QDialog(parent){
    QHBoxLayout* layout=new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    Patients_list* patients_list=new Patients_list(lista_pazienti, lista_cartelle_mediche_unsettled, lista_cartelle_mediche_white, lista_cartelle_mediche_green, lista_cartelle_mediche_blue, lista_cartelle_mediche_orange, lista_cartelle_mediche_red, this);
    connect(this, &Patients_list_window::clear_list, patients_list, &Patients_list::refresh);
    connect(patients_list, &Patients_list::save, this, &Patients_list_window::save);
    layout->addWidget(patients_list);
}
