#include "patient_panel.h"

Patient_panel::Patient_panel(const Patient& paziente, Container<Patient*>& lista_pazienti, Container<Medical_history*>& medical_history_unsettled_list, Container<Medical_history*>& medical_history_white_list, Container<Medical_history*>& medical_history_green_list, Container<Medical_history*>& medical_history_blue_list, Container<Medical_history*>& medical_history_orange_list, Container<Medical_history*>& medical_history_red_list, QWidget *parent): QWidget(parent), patient(paziente), patients_list(lista_pazienti),  lista_cartelle_mediche_unsettled(medical_history_unsettled_list), lista_cartelle_mediche_white(medical_history_white_list), lista_cartelle_mediche_green(medical_history_green_list), lista_cartelle_mediche_blue(medical_history_blue_list), lista_cartelle_mediche_orange(medical_history_orange_list), lista_cartelle_mediche_red(medical_history_red_list){
    QHBoxLayout* layout=new QHBoxLayout(this);

    QLabel* label_nome=new QLabel(QString::fromStdString(patient.Get_name()));
    label_nome->setAlignment(Qt::AlignCenter);
    layout->addWidget(label_nome);

    QLabel* label_cognome=new QLabel(QString::fromStdString(patient.Get_surname()));
    label_cognome->setAlignment(Qt::AlignCenter);
    layout->addWidget(label_cognome);

    QLabel* label_data_di_nascita=new QLabel(QString::fromStdString(patient.Get_birth_date()));
    label_data_di_nascita->setAlignment(Qt::AlignCenter);
    layout->addWidget(label_data_di_nascita);

    QLabel* label_cod_fiscale=new QLabel(QString::fromStdString(patient.Get_codice_fiscale()));
    label_cod_fiscale->setAlignment(Qt::AlignCenter);
    layout->addWidget(label_cod_fiscale);

    QPushButton* open=new QPushButton("Apri");
    open->setFixedWidth(65);
    connect(open, &QPushButton::clicked, this, &Patient_panel::elenco_lettere_dimissione);
    layout->addWidget(open, Qt::AlignCenter);

    QPushButton* modifica=new QPushButton("Modifica");
    modifica->setFixedWidth(65);
    connect(modifica, &QPushButton::clicked, this, &Patient_panel::modifica_paziente);
    layout->addWidget(modifica, Qt::AlignCenter);

    QPushButton* elimina=new QPushButton("Elimina");
    elimina->setFixedWidth(65);
    connect(elimina, &QPushButton::clicked, this, &Patient_panel::elimina_paziente);
    layout->addWidget(elimina, Qt::AlignCenter);

}

void Patient_panel::elenco_lettere_dimissione(){
    if(patient.Empty_lettere_dimissioni()){
        std::string error_messagge="Il paziente "+ patient.Get_codice_fiscale()+"\nnon presenta alcuna lettera di dimissioni";
        Error_window* error_window=new Error_window(error_messagge, this);
        error_window->resize(250,150);
        error_window->setWindowTitle("ERROR_EMPTY_DISCHARGE'S_LETTERS_LIST");
        error_window->show();
    } else{
        Discharges_letters_list* discharges_letters_list=new Discharges_letters_list(patient.Get_lista_lettere_dimissioni(), this);
        connect(this, &Patient_panel::refresh_discharges_letters_list, discharges_letters_list, &Discharges_letters_list::refresh);
        discharges_letters_list->resize(600,400);
        discharges_letters_list->setWindowTitle("Elenco Operatori");
        discharges_letters_list->show();
    }
}

void Patient_panel::elimina_paziente(){

    Container<Medical_history*>::const_iterator it_u=lista_cartelle_mediche_unsettled.begin();
    while(it_u!=lista_cartelle_mediche_unsettled.end() && (*(*it_u)->Get_patient())!=patient){
        it_u++;
    }
    Container<Medical_history*>::const_iterator it_w=lista_cartelle_mediche_white.begin();
    while(it_w!=lista_cartelle_mediche_white.end() && (*(*it_w)->Get_patient())!=patient){
        it_w++;
    }
    Container<Medical_history*>::const_iterator it_g=lista_cartelle_mediche_green.begin();
    while(it_g!=lista_cartelle_mediche_green.end() && (*(*it_g)->Get_patient())!=patient){
        it_g++;
    }
    Container<Medical_history*>::const_iterator it_b=lista_cartelle_mediche_blue.begin();
    while(it_b!=lista_cartelle_mediche_blue.end() && (*(*it_b)->Get_patient())!=patient){
        it_b++;
    }
    Container<Medical_history*>::const_iterator it_o=lista_cartelle_mediche_orange.begin();
    while(it_o!=lista_cartelle_mediche_orange.end() && (*(*it_o)->Get_patient())!=patient){
        it_o++;
    }
    Container<Medical_history*>::const_iterator it_r=lista_cartelle_mediche_red.begin();
    while(it_r!=lista_cartelle_mediche_red.end() && (*(*it_r)->Get_patient())!=patient){
        it_r++;
    }
    if(it_u==lista_cartelle_mediche_unsettled.end() && it_w==lista_cartelle_mediche_white.end() && it_g==lista_cartelle_mediche_green.end() && it_b==lista_cartelle_mediche_blue.end() && it_o==lista_cartelle_mediche_orange.end() && it_r==lista_cartelle_mediche_red.end()){
        patients_list.remove(const_cast<Patient*>(&patient));
        delete const_cast<Patient*>(&patient);

        emit refresh_patients_list();
    } else {
        std::string error_messagge="Il paziente "+ patient.Get_codice_fiscale()+"\nrisulta essere in una cartella\nmedica non ancora terminata!";
        Error_window* error_window=new Error_window(error_messagge, this);
        error_window->resize(250,150);
        error_window->setWindowTitle("ERROR_DELETE_PATIENT");
        error_window->show();
    }
}

void Patient_panel::modifica_paziente(){
    Edit_patient_window* edit_patient_window=new Edit_patient_window(const_cast<Patient&>(patient), patients_list, this);
    std::string window_name="EDIT WINDOW for PATIENT: "+patient.Get_name()+" "+patient.Get_surname();
    edit_patient_window->setWindowTitle(QString::fromStdString(window_name));
    edit_patient_window->resize(600,400);
    edit_patient_window->show();

    connect(edit_patient_window, &Edit_patient_window::clear_for_edit, this, &Patient_panel::refresh_patients_list);
}
