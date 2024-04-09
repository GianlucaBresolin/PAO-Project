#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "option_list.h"
#include "patient.h"
#include "nurse.h"
#include "doctor.h"
#include "primary.h"
#include "container_template.h"

class MainWindow : public QMainWindow{
    Q_OBJECT
    public:
    MainWindow(Container<Patient*>& lista_pazienti, Container<Worker*>& lista_operatori, Container<Medical_history*>& lista_cartelle_mediche_unsettled, Container<Medical_history*>& lista_cartelle_mediche_bianco, Container<Medical_history*>& lista_cartelle_mediche_verde, Container<Medical_history*>& lista_cartelle_mediche_blu, Container<Medical_history*>& lista_cartelle_mediche_arancione, Container<Medical_history*>& lista_cartelle_mediche_rosso, QWidget *parent = nullptr);

};

#endif
