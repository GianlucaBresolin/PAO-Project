#include "edit_operator_window.h"

Edit_operator_window::Edit_operator_window(Worker& operatore, Container<Worker*>& lista_operatori, QWidget* parent): QDialog(parent), worker(operatore), workers_list(lista_operatori){
    QGridLayout* layout=new QGridLayout(this);
    layout->setAlignment(Qt::AlignCenter);
    layout->setVerticalSpacing(20);

    QLabel* modifica_paziente=new QLabel();
    modifica_paziente->setText("MODIFICA OPERATORE");
    modifica_paziente->setAlignment(Qt::AlignCenter);
    layout->addWidget(modifica_paziente,0,0,1,4, Qt::AlignCenter);

    QLabel* name_label=new QLabel();
    name_label->setText("Nome");
    layout->addWidget(name_label,1,0,1,1, Qt::AlignRight);
    lineEdit_name=new QLineEdit(QString::fromStdString(operatore.Get_name()));
    lineEdit_name->setFixedWidth(160);
    layout->addWidget(lineEdit_name,1,1,1,3, Qt::AlignLeft);

    QLabel* surname_label=new QLabel();
    surname_label->setText("Cognome");
    layout->addWidget(surname_label,2,0,1,1, Qt::AlignRight);
    lineEdit_surname=new QLineEdit(QString::fromStdString(operatore.Get_surname()));
    lineEdit_surname->setFixedWidth(160);
    layout->addWidget(lineEdit_surname,2,1,1,3, Qt::AlignLeft);

    QLabel* birth_date_label=new QLabel();
    birth_date_label->setText("Data Di Nascita");
    layout->addWidget(birth_date_label,3,0,1,1, Qt::AlignRight);
    lineEdit_birth_date=new QLineEdit(QString::fromStdString(operatore.Get_birth_date()));
    lineEdit_birth_date->setFixedWidth(160);
    layout->addWidget(lineEdit_birth_date,3,1,1,3, Qt::AlignLeft);

    QHBoxLayout* buttonLayout = new QHBoxLayout;

    QPushButton* annulla_modifica=new QPushButton("ANNULLA");
    annulla_modifica->setFixedWidth(80);
    buttonLayout->addWidget(annulla_modifica);
    connect(annulla_modifica, &QPushButton::clicked, this, &Edit_operator_window::reject);

    QPushButton* conferma_modifica=new QPushButton("CONFERMA");
    conferma_modifica->setFixedWidth(80);
    buttonLayout->addWidget(conferma_modifica);
    connect(conferma_modifica, &QPushButton::clicked, this, &Edit_operator_window::edit_worker);

    buttonLayout->setAlignment(Qt::AlignCenter);
    layout->addLayout(buttonLayout,6,0,1,4, Qt::AlignCenter);
}

void Edit_operator_window::edit_worker(){
    std::string nome=(lineEdit_name->text()).toStdString();
    std::string cognome=(lineEdit_surname->text()).toStdString();
    std::string data_nascita=(lineEdit_birth_date->text()).toStdString();

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

    if(error_flag){
        Error_window* error_window=new Error_window(error_message, this);
        error_window->resize(250,150);
        error_window->setWindowTitle("ERROR_OPERATOR_MODIFICATION");
        error_window->show();
    }
    else{
        Worker* p;
        if(dynamic_cast<Nurse*>(&worker)){
            p=new Nurse(nome, cognome, data_nascita);
        } else if(dynamic_cast<Primary*>(&worker)){
            p=new Primary(nome, cognome, data_nascita);
        } else {
            p=new Doctor(nome, cognome, data_nascita);
        }
        if (workers_list.search(p)==nullptr){
            worker.Set_name(nome);
            worker.Set_surname(cognome);
            worker.Set_birth_date(data_nascita);
            delete p;
            emit clear_for_edit();
            emit close();
        }
        else{
            if(*p==worker){
                Error_window* error_window=new Error_window("ERROR: OPERATOR NOT MODIFIED", this);
                error_window->resize(250,50);
                error_window->setWindowTitle("ERROR_OPERATOR_NOT_MODIFIED");
                error_window->show();
            } else {
            Error_window* error_window=new Error_window("ERROR: OPERATOR ALREDY EXISTING", this);
            error_window->resize(250,50);
            error_window->setWindowTitle("ERROR_OPERATOR_ALREADY_EXISTING");
            error_window->show();
            }
            delete p;
        }
    }
}

