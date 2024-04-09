#include "search_patient_window.h"

Search_patient_window::Search_patient_window(Container<Patient*>& lista_pazienti, Container<Medical_history*>& lista_cartelle_mediche_unsettled, Container<Medical_history*>& lista_cartelle_mediche_white, Container<Medical_history*>& lista_cartelle_mediche_green, Container<Medical_history*>& lista_cartelle_mediche_blue, Container<Medical_history*>& lista_cartelle_mediche_orange, Container<Medical_history*>& lista_cartelle_mediche_red, QWidget *parent): QDialog(parent), patients_list(lista_pazienti), medical_history_unsettled_list(lista_cartelle_mediche_unsettled), medical_history_white_list(lista_cartelle_mediche_white), medical_history_green_list(lista_cartelle_mediche_green), medical_history_blue_list(lista_cartelle_mediche_blue), medical_history_orange_list(lista_cartelle_mediche_orange), medical_history_red_list(lista_cartelle_mediche_red){
    QGridLayout* layout=new QGridLayout(this);
    layout->setAlignment(Qt::AlignCenter);
    layout->setVerticalSpacing(20);

    QLabel* creazione_paziente=new QLabel();
    creazione_paziente->setText("RICERCA PAZIENTE");
    creazione_paziente->setAlignment(Qt::AlignCenter);
    layout->addWidget(creazione_paziente,0,0,1,2, Qt::AlignCenter);

    QLabel* name_label=new QLabel();
    name_label->setText("Nome");
    layout->addWidget(name_label,1,0,1,1, Qt::AlignRight);
    lineEdit_name=new QLineEdit();
    lineEdit_name->setFixedWidth(150);
    layout->addWidget(lineEdit_name,1,1,1,1, Qt::AlignLeft);

    QLabel* surname_label=new QLabel();
    surname_label->setText("Cognome");
    layout->addWidget(surname_label,2,0,1,1, Qt::AlignRight);
    lineEdit_surname=new QLineEdit();
    lineEdit_surname->setFixedWidth(150);
    layout->addWidget(lineEdit_surname,2,1,1,1, Qt::AlignLeft);

    QLabel* birth_date_label=new QLabel();
    birth_date_label->setText("Data Di Nascita");
    layout->addWidget(birth_date_label,3,0,1,1, Qt::AlignRight);
    lineEdit_birth_date=new QLineEdit();
    lineEdit_birth_date->setFixedWidth(150);
    layout->addWidget(lineEdit_birth_date,3,1,1,1, Qt::AlignLeft);

    QLabel* codice_fiscale_label=new QLabel();
    codice_fiscale_label->setText("Codice Fiscale");
    layout->addWidget(codice_fiscale_label,4,0,1,1, Qt::AlignRight);
    lineEdit_codice_fiscale=new QLineEdit();
    lineEdit_codice_fiscale->setFixedWidth(150);
    layout->addWidget(lineEdit_codice_fiscale,4,1,1,1, Qt::AlignLeft);

    QPushButton* Cerca_paziente=new QPushButton("Cerca Paziente");
    layout->addWidget(Cerca_paziente,6,0,1,2, Qt::AlignCenter);
    connect(Cerca_paziente, &QPushButton::clicked, this, &Search_patient_window::try_creation_medical_history);

}

void Search_patient_window::try_creation_medical_history(){
    std::string nome=(lineEdit_name->text()).toStdString();
    std::string cognome=(lineEdit_surname->text()).toStdString();
    std::string data_nascita=(lineEdit_birth_date->text()).toStdString();
    std::string cod_fiscale=(lineEdit_codice_fiscale->text()).toStdString();

    Patient* p=new Patient(nome, cognome, data_nascita, cod_fiscale);
    if(patients_list.search(p)==nullptr){
        Error_window* error_window=new Error_window("ERROR: PATIENT NOT FOUND", this);
        error_window->resize(250,50);
        error_window->setWindowTitle("ERROR_PATIENT_NOT_FOUND");
        error_window->show();
    }
    else{
        Creation_medical_history_window* creation_medical_history_window=new Creation_medical_history_window(medical_history_unsettled_list, medical_history_white_list, medical_history_green_list, medical_history_blue_list, medical_history_orange_list, medical_history_red_list, *patients_list.search(p), this);
        connect(creation_medical_history_window, &Creation_medical_history_window::clear_for_add, this, &Search_patient_window::clear_medical_history_list);
        connect(creation_medical_history_window, &Creation_medical_history_window::close, this, &Search_patient_window::reject);
        creation_medical_history_window->resize(300,200);
        creation_medical_history_window->setWindowTitle("Creazione Cartella Medica");
        creation_medical_history_window->show();
    }
    delete p;
}
