#include "creation_patient_window.h"

Creation_patient_window::Creation_patient_window(Container<Patient*>& lista_pazienti, QWidget* parent): QDialog(parent), patients_list(lista_pazienti){

    QGridLayout* layout=new QGridLayout(this);
    layout->setAlignment(Qt::AlignCenter);
    layout->setVerticalSpacing(20);

    QLabel* creazione_paziente=new QLabel();
    creazione_paziente->setText("CREAZIONE PAZIENTE");
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

    QPushButton* crea=new QPushButton("CREA");
    crea->setFixedWidth(100);
    layout->addWidget(crea,6,0,1,2, Qt::AlignCenter);
    connect(crea, &QPushButton::clicked, this, &Creation_patient_window::add_patient);

}

void Creation_patient_window::add_patient(){
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
    if(nome.find('(') !=std::string::npos || nome.find(')')!=std::string::npos || nome.find('|')!=std::string::npos){
        error_message+="\nNon puoi inserire un nome contenente i caratteri '(', ')' e/o '|'\n";
        error_flag=true;
    }
    if(cognome==""){
        error_message+="\nDevi inserire un cognome valido!\n";
        error_flag=true;
    }
    if(cognome.find('(') !=std::string::npos || cognome.find(')')!=std::string::npos || cognome.find('|')!=std::string::npos){
        error_message+="\nNon puoi inserire un cognome contenente i caratteri '(', ')' e/o '|'\n";
        error_flag=true;
    }
    if(data_nascita==""){
        error_message+="\nDevi inserire una data di nascita valida!\n";
        error_flag=true;
    }
    if(data_nascita.find('(') !=std::string::npos || data_nascita.find(')')!=std::string::npos || data_nascita.find('|')!=std::string::npos){
        error_message+="\nNon puoi inserire un data di nascita contenente i caratteri '(', ')' e/o '|'\n";
        error_flag=true;
    }
    if(cod_fiscale==""){
        error_message+="\nDevi inserire un codice fiscale valido!\n";
        error_flag=true;
    }
    if(cod_fiscale.find('(') !=std::string::npos || cod_fiscale.find(')')!=std::string::npos || cod_fiscale.find('|')!=std::string::npos){
        error_message+="\nNon puoi inserire un codice fiscale contenente i caratteri '(', ')' e/o '|'\n";
        error_flag=true;
    }

    if(error_flag){
        Error_window* error_window=new Error_window(error_message, this);
        error_window->resize(250,150);
        error_window->setWindowTitle("ERROR_PATIENT_CREATION");
        error_window->show();
    }
    else{
        Patient* p=new Patient(nome, cognome, data_nascita, cod_fiscale);
        if (patients_list.search(p)==nullptr){
            patients_list.add(p);
            emit clear_for_add();
            emit close();
        }
        else{
            delete p;
            Error_window* error_window=new Error_window("ERROR: PATIENT ALREDY EXISTING", this);
            error_window->resize(250,50);
            error_window->setWindowTitle("ERROR_PATIENT_ALREADY_EXISTING");
            error_window->show();
        }
    }
}
