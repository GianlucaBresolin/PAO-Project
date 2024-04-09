#include "medical_history_list_window.h"

Medical_history_list_window::Medical_history_list_window(Container<Medical_history*>& lista_cartelle_mediche_unsettled, Container<Medical_history*>& lista_cartelle_mediche_bianco, Container<Medical_history*>& lista_cartelle_mediche_verde, Container<Medical_history*>& lista_cartelle_mediche_blu, Container<Medical_history*>& lista_cartelle_mediche_arancione, Container<Medical_history*>& lista_cartelle_mediche_rosso, Container<Worker*>& lista_operatori, QWidget* parent): QDialog(parent), medical_history_unsettled_list(lista_cartelle_mediche_unsettled), medical_history_white_list(lista_cartelle_mediche_bianco), medical_history_green_list(lista_cartelle_mediche_verde), medical_history_blue_list(lista_cartelle_mediche_blu), medical_history_orange_list(lista_cartelle_mediche_arancione), medical_history_red_list(lista_cartelle_mediche_rosso), worker_list(lista_operatori){
    QGridLayout* main_layout=new QGridLayout(this);
    main_layout->setContentsMargins(0, 0, 0, 0);
    main_layout->setAlignment(Qt::AlignCenter);
    main_layout->setSpacing(5);

    QVBoxLayout* unsettled_layout=new QVBoxLayout();
    unsettled_layout->setSpacing(0);
    QLabel* unsettled_label=new QLabel("IN ATTESA DI ESSERE ACCOLTI");
    unsettled_label->setAlignment(Qt::AlignCenter);
    unsettled_layout->addWidget(unsettled_label);

    Medical_history_list* medical_history_unsettled_list=new Medical_history_list(lista_cartelle_mediche_unsettled, worker_list, this);
    connect(this, &Medical_history_list_window::clear_unsettled_list, medical_history_unsettled_list, &Medical_history_list::refresh);
    connect(medical_history_unsettled_list, &Medical_history_list::refresh_worker_list, this, &Medical_history_list_window::refresh_worker_list);
    unsettled_layout->addWidget(medical_history_unsettled_list);

    QPushButton* Esegui_accettazione=new QPushButton("Esegui Accettazione");
    connect(Esegui_accettazione, &QPushButton::clicked, this, &Medical_history_list_window::Acceptance_get_nurse);
    Esegui_accettazione->setFixedWidth(150);
    QHBoxLayout* buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(Esegui_accettazione);
    buttonLayout->setAlignment(Qt::AlignCenter);
    unsettled_layout->addLayout(buttonLayout);

    main_layout->addLayout(unsettled_layout,0,0,1,1);

    QVBoxLayout* white_layout=new QVBoxLayout();
    white_layout->setSpacing(0);
    QLabel* white_label=new QLabel("CODICE BIANCO");
    white_label->setAlignment(Qt::AlignCenter);
    white_layout->addWidget(white_label);

    Medical_history_list* medical_history_white_list=new Medical_history_list(lista_cartelle_mediche_bianco, worker_list, this);
    connect(this, &Medical_history_list_window::clear_white_list, medical_history_white_list, &Medical_history_list::refresh);
    connect(medical_history_white_list, &Medical_history_list::refresh_worker_list, this, &Medical_history_list_window::refresh_worker_list);
    connect(medical_history_white_list, &Medical_history_list::save, this, &Medical_history_list_window::save);
    white_layout->addWidget(medical_history_white_list);

    main_layout->addLayout(white_layout,1,0);

    QVBoxLayout* green_layout=new QVBoxLayout();
    green_layout->setSpacing(0);
    QLabel* green_label=new QLabel("CODICE VERDE");
    green_label->setAlignment(Qt::AlignCenter);
    green_layout->addWidget(green_label);

    Medical_history_list* medical_history_green_list=new Medical_history_list(lista_cartelle_mediche_verde, worker_list, this);
    connect(this, &Medical_history_list_window::clear_green_list, medical_history_green_list, &Medical_history_list::refresh);
    connect(medical_history_green_list, &Medical_history_list::refresh_worker_list, this, &Medical_history_list_window::refresh_worker_list);
    connect(medical_history_green_list, &Medical_history_list::save, this, &Medical_history_list_window::save);
    green_layout->addWidget(medical_history_green_list);

    main_layout->addLayout(green_layout,2,0,1,1);

    QVBoxLayout* blue_layout=new QVBoxLayout();
    blue_layout->setSpacing(0);
    QLabel* blue_label=new QLabel("CODICE BLU");
    blue_label->setAlignment(Qt::AlignCenter);
    blue_layout->addWidget(blue_label);

    Medical_history_list* medical_history_blue_list=new Medical_history_list(lista_cartelle_mediche_blu, worker_list, this);
    connect(this, &Medical_history_list_window::clear_blue_list, medical_history_blue_list, &Medical_history_list::refresh);
    connect(medical_history_blue_list, &Medical_history_list::refresh_worker_list, this, &Medical_history_list_window::refresh_worker_list);
    connect(medical_history_blue_list, &Medical_history_list::save, this, &Medical_history_list_window::save);
    blue_layout->addWidget(medical_history_blue_list);

    main_layout->addLayout(blue_layout,0,1);

    QVBoxLayout* orange_layout=new QVBoxLayout();
    orange_layout->setSpacing(0);
    QLabel* orange_label=new QLabel("CODICE ARANCIONE");
    orange_label->setAlignment(Qt::AlignCenter);
    orange_layout->addWidget(orange_label);

    Medical_history_list* medical_history_orange_list=new Medical_history_list(lista_cartelle_mediche_arancione, worker_list, this);
    connect(this, &Medical_history_list_window::clear_orange_list, medical_history_orange_list, &Medical_history_list::refresh);
    connect(medical_history_orange_list, &Medical_history_list::refresh_worker_list, this, &Medical_history_list_window::refresh_worker_list);
    connect(medical_history_orange_list, &Medical_history_list::save, this, &Medical_history_list_window::save);
    orange_layout->addWidget(medical_history_orange_list);

    main_layout->addLayout(orange_layout,1,1,1,1);

    QVBoxLayout* red_layout=new QVBoxLayout();
    red_layout->setSpacing(0);
    QLabel* red_label=new QLabel("CODICE ROSSO");
    red_label->setAlignment(Qt::AlignCenter);
    red_layout->addWidget(red_label);

    Medical_history_list* medical_history_red_list=new Medical_history_list(lista_cartelle_mediche_rosso, worker_list, this);
    connect(this, &Medical_history_list_window::clear_red_list, medical_history_red_list, &Medical_history_list::refresh);
    connect(medical_history_red_list, &Medical_history_list::refresh_worker_list, this, &Medical_history_list_window::refresh_worker_list);
    connect(medical_history_red_list, &Medical_history_list::save, this, &Medical_history_list_window::save);
    red_layout->addWidget(medical_history_red_list);
    main_layout->addLayout(red_layout,2,1,1,1);
}

void Medical_history_list_window::Acceptance_get_nurse(){
    if(medical_history_unsettled_list.empty()){
        Error_window* error_window=new Error_window("Devi ancora creare una Cartella\nMedica!", this);
        error_window->resize(250,150);
        error_window->setWindowTitle("ERROR_VOID_MEDICAL_HISTORY_LIST");
        error_window->show();
    }
    else{
        Container<Worker*>::const_iterator it=worker_list.begin();
        while(it!=worker_list.end() && !(dynamic_cast<Nurse*>(*it))){
            it++;
        }
        if(it==worker_list.end()){
            Error_window* error_window=new Error_window("Devi ancora inserire un infermiere/a\n/\nNon ci sono infermieri liberi!", this);
            error_window->resize(250,150);
            error_window->setWindowTitle("ERROR_NO_NURSE_FOUND");
            error_window->show();
        }
        else{
            try{
                nurse=dynamic_cast<Nurse*>(worker_list.remove(*it));
            } catch(const std::runtime_error& e){
                Error_window* error_window=new Error_window("RUNTIME ERROR", this);
                error_window->resize(250,150);
                error_window->setWindowTitle("RUNTIME ERROR");
                error_window->show();
            }
            emit refresh_worker_list();

            cartella=medical_history_unsettled_list.pop();
            emit clear_unsettled_list();

            cartella->Set_worker(nurse);

            Acceptance_window* acceptance_window=new Acceptance_window(*nurse, this);
            acceptance_window->resize(600,200);
            std::string window_name="ACCEPTANCE WINDOW of "+ nurse->Get_name() +" "+ nurse->Get_surname()+ "for patient: "+ (cartella->Get_patient())->Get_codice_fiscale();
            acceptance_window->setWindowTitle(QString::fromStdString(window_name));
            acceptance_window->show();
            connect(acceptance_window, &QDialog::finished, this, &Medical_history_list_window::Acceptance_insert_medical_history);
        }
    }
}

void Medical_history_list_window::Acceptance_insert_medical_history(){
    cartella->Do_work();
    switch (cartella->Get_medical_code()){
        case Medical_code::White:
            medical_history_white_list.add(cartella);
            emit clear_white_list();
            break;
        case Medical_code::Green:
            medical_history_green_list.add(cartella);
            emit clear_green_list();
            break;
        case Medical_code::Blue:
            medical_history_blue_list.add(cartella);
            emit clear_blue_list();
            break;
        case Medical_code::Orange:
            medical_history_orange_list.add(cartella);
            emit clear_orange_list();
            break;
        case Medical_code::Red:
            medical_history_red_list.add(cartella);
            emit clear_red_list();
            break;
        default:
            medical_history_white_list.add(cartella);
            emit clear_white_list();
            break;
        }
    emit save();
}
