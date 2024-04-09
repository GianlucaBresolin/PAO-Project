#include "creation_operator_window.h"

Creation_operator_window::Creation_operator_window(Container<Worker*>& lista_operatori, Container<Medical_history*>& medical_history_white_list, Container<Medical_history*>& medical_history_green_list, Container<Medical_history*>& medical_history_blue_list, Container<Medical_history*>& medical_history_orange_list, Container<Medical_history*>& medical_history_red_list, QWidget *parent): QDialog(parent), operators_list(lista_operatori), lista_cartelle_mediche_white(medical_history_white_list), lista_cartelle_mediche_green(medical_history_green_list), lista_cartelle_mediche_blue(medical_history_blue_list), lista_cartelle_mediche_orange(medical_history_orange_list), lista_cartelle_mediche_red(medical_history_red_list) {
    nurse_type=true;
    doctor_type=false;
    primary_type=false;

    QGridLayout* layout=new QGridLayout(this);
    layout->setAlignment(Qt::AlignCenter);
    layout->setVerticalSpacing(20);

    QLabel* creazione_paziente=new QLabel();
    creazione_paziente->setText("CREAZIONE OPERATORE");
    creazione_paziente->setAlignment(Qt::AlignCenter);
    layout->addWidget(creazione_paziente,0,0,1,3, Qt::AlignCenter);

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

    allButtons.push_back(nurse_button);
    nurse_button->setChecked(true);
    layout->addWidget(nurse_button,4,0,1,1, Qt::AlignCenter);
    connect(nurse_button, &QPushButton::clicked, this, &Creation_operator_window::setType);
    connect(nurse_button, &QPushButton::clicked, this, &Creation_operator_window::onToggleButtonClicked);

    allButtons.push_back(doctor_button);
    doctor_button->setChecked(false);
    layout->addWidget(doctor_button,4,1,1,1, Qt::AlignCenter);
    connect(doctor_button, &QPushButton::clicked, this, &Creation_operator_window::setType);
    connect(doctor_button, &QPushButton::clicked, this, &Creation_operator_window::onToggleButtonClicked);

    allButtons.push_back(primary_button);
    primary_button->setChecked(false);
    layout->addWidget(primary_button,4,2,1,1, Qt::AlignCenter);
    connect(primary_button, &QPushButton::clicked, this, &Creation_operator_window::setType);
    connect(primary_button, &QPushButton::clicked, this, &Creation_operator_window::onToggleButtonClicked);

    QPushButton* crea=new QPushButton("CREA");
    crea->setFixedWidth(100);
    layout->addWidget(crea,6,0,1,3, Qt::AlignCenter);  
    connect(crea, &QPushButton::clicked, this, &Creation_operator_window::add_operator);

}

void Creation_operator_window::onToggleButtonClicked(){
    QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());

    for (QList<QPushButton*>::iterator it = allButtons.begin(); it != allButtons.end(); ++it){
        if (*it!=clickedButton){
            (*it)->setChecked(false);
        }
    }
    clickedButton->setChecked(true);
}

void Creation_operator_window::setType(){

    QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());

    if(clickedButton==nurse_button){
        nurse_type=true;
        doctor_type=false;
        primary_type=false;
    } else if(clickedButton==doctor_button){
        nurse_type=false;
        doctor_type=true;
        primary_type=false;
    } else{
        nurse_type=false;
        doctor_type=false;
        primary_type=true;
    }
}

void Creation_operator_window::add_operator(){
    std::string nome=(lineEdit_name->text()).toStdString();
    std::string cognome=(lineEdit_surname->text()).toStdString();
    std::string data_nascita=(lineEdit_birth_date->text()).toStdString();

    bool error_flag=false;
    std::string error_message="";
    if(nome==""){
        error_message+="\nDevi inserire un nome valido!\n";
        error_flag=true;
    }
    if(nome[0]=='0'){
        error_message+="\nNon puoi inserire un nome iniziante col carattere '0'\n";
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

    if(error_flag){
        Error_window* error_window=new Error_window(error_message, this);
        error_window->resize(250,150);
        error_window->setWindowTitle("ERROR_OPERATOR_CREATION");
        error_window->show();
    }
    else{
        Worker* p=nullptr;
        if(nurse_type){
            p=new Nurse(nome, cognome, data_nascita);
        } else if(doctor_type){
            p=new Doctor(nome, cognome, data_nascita);
        } else if(primary_type){
            p=new Primary(nome, cognome, data_nascita);
        } else{
            Error_window* error_window=new Error_window("ERROR: NO OPERATOR TYPE SELECTED", this);
            error_window->resize(250,50);
            error_window->setWindowTitle("ERROR_NO_OPERATOR_TYPE_SELECTED");
            error_window->show();
            return;
        }
        if (operators_list.search(p)==nullptr && p!=nullptr){
            Container<Medical_history*>::const_iterator it_w=lista_cartelle_mediche_white.begin();
            while(it_w!=lista_cartelle_mediche_white.end() && (*(*it_w)->Get_worker())!=(*p)){
                it_w++;
            }
            Container<Medical_history*>::const_iterator it_g=lista_cartelle_mediche_green.begin();
            while(it_g!=lista_cartelle_mediche_green.end() && (*(*it_g)->Get_worker())!=(*p)){
                it_g++;
            }
            Container<Medical_history*>::const_iterator it_b=lista_cartelle_mediche_blue.begin();
            while(it_b!=lista_cartelle_mediche_blue.end() && (*(*it_b)->Get_worker())!=(*p)){
                it_b++;
            }
            Container<Medical_history*>::const_iterator it_o=lista_cartelle_mediche_orange.begin();
            while(it_o!=lista_cartelle_mediche_orange.end() && (*(*it_o)->Get_worker())!=(*p)){
                it_o++;
            }
            Container<Medical_history*>::const_iterator it_r=lista_cartelle_mediche_red.begin();
            while(it_r!=lista_cartelle_mediche_red.end() && (*(*it_r)->Get_worker())!=(*p)){
                it_r++;
            }
            if(it_w==lista_cartelle_mediche_white.end() && it_g==lista_cartelle_mediche_green.end() && it_b==lista_cartelle_mediche_blue.end() && it_o==lista_cartelle_mediche_orange.end() && it_r==lista_cartelle_mediche_red.end()){
            operators_list.add(p);
            emit clear_for_add();
            emit close();
            } else {
                delete p;
                Error_window* error_window=new Error_window("ERROR: OPERATOR ALREDY EXISTING", this);
                error_window->resize(250,50);
                error_window->setWindowTitle("ERROR_OPERATOR_ALREADY_EXISTING");
                error_window->show();
            }
        }
        else{
            delete p;
            Error_window* error_window=new Error_window("ERROR: OPERATOR ALREDY EXISTING", this);
            error_window->resize(250,50);
            error_window->setWindowTitle("ERROR_OPERATOR_ALREADY_EXISTING");
            error_window->show();
        }
    }
}

