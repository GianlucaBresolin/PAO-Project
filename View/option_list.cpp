#include "option_list.h"

Option_list::Option_list(Container<Patient*>& lista_pazienti, Container<Worker*>& lista_operatori, Container<Medical_history*>& lista_cartelle_mediche_unsettled, Container<Medical_history*>& lista_cartelle_mediche_bianco, Container<Medical_history*>& lista_cartelle_mediche_verde, Container<Medical_history*>& lista_cartelle_mediche_blu, Container<Medical_history*>& lista_cartelle_mediche_arancione, Container<Medical_history*>& lista_cartelle_mediche_rosso, QWidget *parent): QWidget(parent), patients_list(lista_pazienti), operators_list(lista_operatori), medical_history_unsettled_list(lista_cartelle_mediche_unsettled), medical_history_white_list(lista_cartelle_mediche_bianco), medical_history_green_list(lista_cartelle_mediche_verde), medical_history_blue_list(lista_cartelle_mediche_blu), medical_history_orange_list(lista_cartelle_mediche_arancione), medical_history_red_list(lista_cartelle_mediche_rosso){
    QGridLayout* layout=new QGridLayout(this);
    layout->setAlignment(Qt::AlignCenter);
    layout->setVerticalSpacing(10);
    layout->setHorizontalSpacing(20);

    QLabel* header=new QLabel(QString::fromStdString("Portale Clinica Medica"));
    QFont font;
    font.setBold(true);
    font.setPointSize(16);
    header->setFont(font);
    header->setAlignment(Qt::AlignCenter);
    layout->addWidget(header,0,0,1,3, Qt::AlignCenter);

    QPushButton* Creazione_cartella_medica=new QPushButton("Creazione Cartella Medica");
    layout->addWidget(Creazione_cartella_medica,1,0,1,1);
    connect(Creazione_cartella_medica, &QPushButton::clicked, this, &Option_list::open_search_patient_window);

    QPushButton* Elenco_cartelle_mediche=new QPushButton("Elenco Cartelle Mediche");
    layout->addWidget(Elenco_cartelle_mediche,2,0,1,1);
    connect(Elenco_cartelle_mediche, &QPushButton::clicked, this, &Option_list::open_medical_history_list_window);

    QPushButton* Inserisci_paziente=new QPushButton("Inserisci Paziente");
    layout->addWidget(Inserisci_paziente,1,1,1,1);
    connect(Inserisci_paziente, &QPushButton::clicked, this, &Option_list::open_creation_patient_window);

    QPushButton* Elenco_pazienti=new QPushButton("Elenco Pazienti");
    layout->addWidget(Elenco_pazienti,2,1,1,1);
    connect(Elenco_pazienti, &QPushButton::clicked, this, &Option_list::open_patients_list_window);

    QPushButton* Inserisci_operatore=new QPushButton("Inserisci Operatore");
    layout->addWidget(Inserisci_operatore,1,2,1,1);
    connect(Inserisci_operatore, &QPushButton::clicked, this, &Option_list::open_creation_operator_window);

    QPushButton* Elenco_operatori=new QPushButton("Elenco Operatori Disponibili");
    layout->addWidget(Elenco_operatori,2,2,1,1);
    connect(Elenco_operatori, &QPushButton::clicked, this, &Option_list::open_operators_list_window);

}

void Option_list::open_search_patient_window(){
    if(patients_list.empty()){
        open_creation_patient_window();
        Error_window* error_window=new Error_window("DEVI ANCORA INSERIRE UN PAZIENTE!", this);
        error_window->resize(150,50);
        error_window->setWindowTitle("ERROR: PATIENT'S LIST EMPTY");
        error_window->show();
        return;
    }
    else{
    Search_patient_window* search_patient_window=new Search_patient_window(patients_list, medical_history_unsettled_list, medical_history_white_list, medical_history_green_list, medical_history_blue_list, medical_history_orange_list, medical_history_red_list, this);
    connect(search_patient_window, &Search_patient_window::clear_medical_history_list, this, &Option_list::clear_medical_history_list);
    connect(search_patient_window, &Search_patient_window::clear_medical_history_list, this, &Option_list::save);
    search_patient_window->resize(600,400);
    search_patient_window->setWindowTitle("Ricerca Paziente per Creazione Cartella Medica");
    search_patient_window->show();
    }
}

void Option_list::open_creation_patient_window(){
    Creation_patient_window* creation_patient_window=new Creation_patient_window(patients_list, this);
    connect(creation_patient_window, &Creation_patient_window::clear_for_add, this, &Option_list::clear_patients_list);
    connect(creation_patient_window, &Creation_patient_window::clear_for_add, this, &Option_list::save);
    creation_patient_window->resize(600,400);
    creation_patient_window->setWindowTitle("Creazione Paziente");
    creation_patient_window->show();
}

void Option_list::open_patients_list_window(){
    Patients_list_window* patients_list_window=new Patients_list_window(patients_list, medical_history_unsettled_list, medical_history_white_list, medical_history_green_list, medical_history_blue_list, medical_history_orange_list, medical_history_red_list, this);
    connect(this, &Option_list::clear_patients_list, patients_list_window, &Patients_list_window::clear_list);
    connect(patients_list_window, &Patients_list_window::save, this, &Option_list::save);
    patients_list_window->resize(600,400);
    patients_list_window->setWindowTitle("Elenco Pazienti");
    patients_list_window->show();
}

void Option_list::open_creation_operator_window(){
    Creation_operator_window* creation_operator_window=new Creation_operator_window(operators_list, medical_history_white_list, medical_history_green_list, medical_history_blue_list, medical_history_orange_list, medical_history_red_list, this);
    connect(creation_operator_window, &Creation_operator_window::clear_for_add, this, &Option_list::clear_operators_list);
    connect(creation_operator_window, &Creation_operator_window::clear_for_add, this, &Option_list::save);
    creation_operator_window->resize(600,400);
    creation_operator_window->setWindowTitle("Creazione Operatore");
    creation_operator_window->show();
}

void Option_list::open_operators_list_window(){
    Operators_list_window* operators_list_window=new Operators_list_window(operators_list, this);
    connect(this, &Option_list::clear_operators_list, operators_list_window, &Operators_list_window::clear_list);
    connect(operators_list_window, &Operators_list_window::save, this, &Option_list::save);
    operators_list_window->resize(600,400);
    operators_list_window->setWindowTitle("Elenco Operatori");
    operators_list_window->show();
}

void Option_list::open_medical_history_list_window(){
    Medical_history_list_window* medical_history_list_window=new Medical_history_list_window(medical_history_unsettled_list, medical_history_white_list, medical_history_green_list, medical_history_blue_list, medical_history_orange_list, medical_history_red_list, operators_list, this);
    connect(this, &Option_list::clear_medical_history_list, medical_history_list_window, &Medical_history_list_window::clear_unsettled_list);
    connect(medical_history_list_window, &Medical_history_list_window::refresh_worker_list, this, &Option_list::clear_operators_list);
    connect(medical_history_list_window, &Medical_history_list_window::save, this, &Option_list::save);
    medical_history_list_window->resize(800,500);
    medical_history_list_window->setWindowTitle("Elenco Pazienti");
    medical_history_list_window->show();
}

void Option_list::save(){
    File_manager::Save_to_file("./SaveData.txt", patients_list, operators_list, medical_history_unsettled_list, medical_history_white_list, medical_history_green_list, medical_history_blue_list, medical_history_orange_list, medical_history_red_list);
}
