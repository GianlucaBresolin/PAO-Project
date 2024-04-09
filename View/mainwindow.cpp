#include "mainwindow.h"

MainWindow::MainWindow(Container<Patient*>& lista_pazienti, Container<Worker*>& lista_operatori, Container<Medical_history*>& lista_cartelle_mediche_unsettled, Container<Medical_history*>& lista_cartelle_mediche_bianco, Container<Medical_history*>& lista_cartelle_mediche_verde, Container<Medical_history*>& lista_cartelle_mediche_blu, Container<Medical_history*>& lista_cartelle_mediche_arancione, Container<Medical_history*>& lista_cartelle_mediche_rosso, QWidget *parent): QMainWindow(parent){

    Option_list* options=new Option_list(lista_pazienti, lista_operatori, lista_cartelle_mediche_unsettled, lista_cartelle_mediche_bianco, lista_cartelle_mediche_verde, lista_cartelle_mediche_blu, lista_cartelle_mediche_arancione, lista_cartelle_mediche_rosso);
    setCentralWidget(options);
}
