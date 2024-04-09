#include "creation_medical_history_window.h"

Creation_medical_history_window::Creation_medical_history_window(Container<Medical_history*>& medical_history_unsettled_list, Container<Medical_history*>& medical_history_white_list, Container<Medical_history*>& medical_history_green_list, Container<Medical_history*>& medical_history_blue_list, Container<Medical_history*>& medical_history_orange_list, Container<Medical_history*>& medical_history_red_list, const Patient* patient, QWidget* parent): QDialog(parent), lista_cartelle_mediche_unsettled(medical_history_unsettled_list), lista_cartelle_mediche_white(medical_history_white_list), lista_cartelle_mediche_green(medical_history_green_list), lista_cartelle_mediche_blue(medical_history_blue_list), lista_cartelle_mediche_orange(medical_history_orange_list), lista_cartelle_mediche_red(medical_history_red_list), paziente(patient){
    QGridLayout* layout=new QGridLayout(this);
    layout->setAlignment(Qt::AlignCenter);

    QLabel* question_label=new QLabel(QString::fromStdString("Il Paziente e' stato correttamente trovato.\nVuoi procedere con la creazione\ndi una Nuova Cartella Medica?"));
    question_label->setAlignment(Qt::AlignCenter);
    layout->addWidget(question_label,0,0,1,2);

    QPushButton* yes_button=new QPushButton("SI");
    layout->addWidget(yes_button,1,0,1,1);
    connect(yes_button, &QPushButton::clicked, this, &Creation_medical_history_window::Add_medical_history);
    connect(yes_button, &QPushButton::clicked, this, &Creation_medical_history_window::reject);
    connect(yes_button, &QPushButton::clicked, this, &Creation_medical_history_window::close);

    QPushButton* no_button=new QPushButton("NO");
    layout->addWidget(no_button,1,1,1,1);
    connect(no_button, &QPushButton::clicked, this, &Creation_medical_history_window::reject);
}

void Creation_medical_history_window::Add_medical_history(){
    Container<Medical_history*>::const_iterator it_u=lista_cartelle_mediche_unsettled.begin();
    while(it_u!=lista_cartelle_mediche_unsettled.end() && (*(*it_u)->Get_patient())!=(*paziente)){
        it_u++;
    }
    Container<Medical_history*>::const_iterator it_w=lista_cartelle_mediche_white.begin();
    while(it_w!=lista_cartelle_mediche_white.end() && (*(*it_w)->Get_patient())!=(*paziente)){
        it_w++;
    }
    Container<Medical_history*>::const_iterator it_g=lista_cartelle_mediche_green.begin();
    while(it_g!=lista_cartelle_mediche_green.end() && (*(*it_g)->Get_patient())!=(*paziente)){
        it_g++;
    }
    Container<Medical_history*>::const_iterator it_b=lista_cartelle_mediche_blue.begin();
    while(it_b!=lista_cartelle_mediche_blue.end() && (*(*it_b)->Get_patient())!=(*paziente)){
        it_b++;
    }
    Container<Medical_history*>::const_iterator it_o=lista_cartelle_mediche_orange.begin();
    while(it_o!=lista_cartelle_mediche_orange.end() && (*(*it_o)->Get_patient())!=(*paziente)){
        it_o++;
    }
    Container<Medical_history*>::const_iterator it_r=lista_cartelle_mediche_red.begin();
    while(it_r!=lista_cartelle_mediche_red.end() && (*(*it_r)->Get_patient())!=(*paziente)){
        it_r++;
    }
    if(it_u==lista_cartelle_mediche_unsettled.end() && it_w==lista_cartelle_mediche_white.end() && it_g==lista_cartelle_mediche_green.end() && it_b==lista_cartelle_mediche_blue.end() && it_o==lista_cartelle_mediche_orange.end() && it_r==lista_cartelle_mediche_red.end()){
        lista_cartelle_mediche_unsettled.add(new Medical_history(paziente));
        emit clear_for_add();
    }
    else{
        Error_window* error_window=new Error_window("ERROR: THIS PATIENT IS ALREADY IN A MEDICAL HISTORY!", this);
        error_window->resize(250,50);
        error_window->setWindowTitle("ERROR_PATIENT_ALREADY_IN");
        error_window->show();
        }
}
