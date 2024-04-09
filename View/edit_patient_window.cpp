#include "edit_patient_window.h"

Edit_patient_window::Edit_patient_window(Patient& paziente, Container<Patient*>& lista_pazienti, QWidget* parent): QDialog(parent), patient(paziente), patients_list(lista_pazienti){

    QGridLayout* layout=new QGridLayout(this);
    layout->setAlignment(Qt::AlignCenter);
    layout->setVerticalSpacing(20);

    QLabel* modifica_paziente=new QLabel();
    modifica_paziente->setText("MODIFICA PAZIENTE");
    modifica_paziente->setAlignment(Qt::AlignCenter);
    layout->addWidget(modifica_paziente,0,0,1,4, Qt::AlignCenter);

    QLabel* name_label=new QLabel();
    name_label->setText("Nome");
    layout->addWidget(name_label,1,0,1,1, Qt::AlignRight);
    lineEdit_name=new QLineEdit(QString::fromStdString(patient.Get_name()));
    lineEdit_name->setFixedWidth(160);
    layout->addWidget(lineEdit_name,1,1,1,3, Qt::AlignLeft);

    QLabel* surname_label=new QLabel();
    surname_label->setText("Cognome");
    layout->addWidget(surname_label,2,0,1,1, Qt::AlignRight);
    lineEdit_surname=new QLineEdit(QString::fromStdString(patient.Get_surname()));
    lineEdit_surname->setFixedWidth(160);
    layout->addWidget(lineEdit_surname,2,1,1,3, Qt::AlignLeft);

    QLabel* birth_date_label=new QLabel();
    birth_date_label->setText("Data Di Nascita");
    layout->addWidget(birth_date_label,3,0,1,1, Qt::AlignRight);
    lineEdit_birth_date=new QLineEdit(QString::fromStdString(patient.Get_birth_date()));
    lineEdit_birth_date->setFixedWidth(160);
    layout->addWidget(lineEdit_birth_date,3,1,1,3, Qt::AlignLeft);

    QLabel* codice_fiscale_label=new QLabel();
    codice_fiscale_label->setText("Codice Fiscale");
    layout->addWidget(codice_fiscale_label,4,0,1,1, Qt::AlignRight);
    lineEdit_codice_fiscale=new QLineEdit(QString::fromStdString(patient.Get_codice_fiscale()));
    lineEdit_codice_fiscale->setFixedWidth(160);
    layout->addWidget(lineEdit_codice_fiscale,4,1,1,3, Qt::AlignLeft);

    QHBoxLayout* buttonLayout = new QHBoxLayout;

    QPushButton* annulla_modifica=new QPushButton("ANNULLA");
    annulla_modifica->setFixedWidth(80);
    buttonLayout->addWidget(annulla_modifica);
    connect(annulla_modifica, &QPushButton::clicked, this, &Edit_patient_window::reject);

    QPushButton* conferma_modifica=new QPushButton("CONFERMA");
    conferma_modifica->setFixedWidth(80);
    buttonLayout->addWidget(conferma_modifica);
    connect(conferma_modifica, &QPushButton::clicked, this, &Edit_patient_window::edit_patient);

    buttonLayout->setAlignment(Qt::AlignCenter);
    layout->addLayout(buttonLayout,6,0,1,4, Qt::AlignCenter);

}

void Edit_patient_window::edit_patient(){
    std::string nome=(lineEdit_name->text()).toStdString();
    std::string cognome=(lineEdit_surname->text()).toStdString();
    std::string data_nascita=(lineEdit_birth_date->text()).toStdString();
    std::string cod_fiscale=(lineEdit_codice_fiscale->text()).toStdString();

    bool error_flag=false;
    std::string error_message="";
    if(nome==""){
        error_message+="\nDevi inserire un nome valido!\n";
        error_flag=true;
    }
    if(cognome==""){
        error_message+="\nDevi inserire un cognome valido!\n";
        error_flag=true;
    }
    if(data_nascita==""){
        error_message+="\nDevi inserire una data di nascita valida!\n";
        error_flag=true;
    }
    if(cod_fiscale==""){
        error_message+="\nDevi inserire un codice fiscale valido!\n";
        error_flag=true;
    }

    if(error_flag){
        Error_window* error_window=new Error_window(error_message, this);
        error_window->resize(250,150);
        error_window->setWindowTitle("ERROR_PATIENT_MODIFICATION");
        error_window->show();
    }
    else{
        Patient* p=new Patient(nome, cognome, data_nascita, cod_fiscale);
        if (patients_list.search(p)==nullptr){
            patient.Set_name(nome);
            patient.Set_surname(cognome);
            patient.Set_birth_date(data_nascita);
            patient.Set_codice_fiscale(cod_fiscale);
            delete p;
            emit clear_for_edit();
            emit close();
        }
        else{
            if(*p==patient){
                Error_window* error_window=new Error_window("ERROR: PATIENT NOT MODIFIED", this);
                error_window->resize(250,50);
                error_window->setWindowTitle("ERROR_PATIENT_NOT_MODIFIED");
                error_window->show();
            } else {
            Error_window* error_window=new Error_window("ERROR: PATIENT ALREDY EXISTING", this);
            error_window->resize(250,50);
            error_window->setWindowTitle("ERROR_PATIENT_ALREADY_EXISTING");
            error_window->show();
            }
            delete p;
        }
    }
}
