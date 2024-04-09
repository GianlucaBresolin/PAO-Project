#include "medical_history_panel.h"

Medical_history_panel::Medical_history_panel(Medical_history& cartella_medica, Container<Worker*>& lista_operatori, Container<Medical_history*>& lista_cartelle_mediche, QWidget* parent): QWidget(parent), medical_history(cartella_medica), worker_list(lista_operatori), medical_history_list(lista_cartelle_mediche){
    QHBoxLayout* layout=new QHBoxLayout(this);

    QLabel* label_codice_fiscale=new QLabel(QString::fromStdString((medical_history.Get_patient())->Get_codice_fiscale()));
    label_codice_fiscale->setAlignment(Qt::AlignCenter);
    layout->addWidget(label_codice_fiscale);

    QLabel* label_state=new QLabel(QString::fromStdString(medical_history.Get_string_state()));
    label_state->setAlignment(Qt::AlignCenter);
    layout->addWidget(label_state);

    QLabel* label_codice=new QLabel(QString::fromStdString(medical_history.Get_cod()));
    label_codice->setAlignment(Qt::AlignCenter);
    layout->addWidget(label_codice);

    if (medical_history.Get_worker()!=nullptr){
        WorkerInfoVisitor visitor;
        (medical_history.Get_worker())->accept(visitor);
        layout->addWidget(visitor.getWidget());

        QLabel* label_operatore=new QLabel(QString::fromStdString((medical_history.Get_worker())->Get_surname()));
        label_operatore->setAlignment(Qt::AlignCenter);
        layout->addWidget(label_operatore);

        if(medical_history.Get_state()==Patients_state::Acceptance){
            QPushButton* visita=new QPushButton("Esegui Visita");
            connect(visita, &QPushButton::clicked, this, &Medical_history_panel::prepare_visit);
            layout->addWidget(visita);
        }

        if(medical_history.Get_state()==Patients_state::Visit){
            connect(this, &Medical_history_panel::ready, this, &Medical_history_panel::visit);
            emit ready();
            QLabel *spacer1 = new QLabel("-");
            spacer1->setAlignment(Qt::AlignCenter);
            layout->addWidget(spacer1);
        }

        if(medical_history.Get_state()==Patients_state::End_visit){
            QPushButton* dimissioni=new QPushButton("Dimetti");
            connect(dimissioni, &QPushButton::clicked, this, &Medical_history_panel::discharge);
            layout->addWidget(dimissioni);
        }

        if(medical_history.Get_state()==Patients_state::Discharge){
            QPushButton* termina=new QPushButton("Termina");
            connect(termina, &QPushButton::clicked, this, &Medical_history_panel::remove_medical_history);
            layout->addWidget(termina);
        }
    }
    else{
        QLabel *spacer1 = new QLabel("-");
        spacer1->setAlignment(Qt::AlignCenter);
        layout->addWidget(spacer1);
        QLabel *spacer2 = new QLabel("-");
        spacer2->setAlignment(Qt::AlignCenter);
        layout->addWidget(spacer2);
        QLabel *spacer3 = new QLabel("-");
        spacer3->setAlignment(Qt::AlignCenter);
        layout->addWidget(spacer3);
    }
}

void Medical_history_panel::prepare_visit(){
    Container<Worker*>::const_iterator it=worker_list.begin();
    while(it!=worker_list.end() && !(dynamic_cast<Doctor*>(*it))){
        it++;
    }
    if(it==worker_list.end()){
        Error_window* error_window=new Error_window("Devi ancora inserire un/a dott.re/ssa\n/\nNon ci sono dottori liberi!", this);
        error_window->resize(250,150);
        error_window->setWindowTitle("ERROR_NO_DOCTOR_FOUND");
        error_window->show();
    }
    else{
        try{
            doctor=dynamic_cast<Doctor*>(worker_list.remove(*it));
        } catch(const std::runtime_error& e){
            Error_window* error_window=new Error_window("RUNTIME ERROR", this);
            error_window->resize(250,150);
            error_window->setWindowTitle("RUNTIME ERROR");
            error_window->show();
        }

        worker_list.add(const_cast<Worker*>(medical_history.remove_worker()));
        emit refresh_worker_list();

        medical_history.Set_worker(doctor);
        medical_history.Change_State();
        emit refresh_medical_history_list();

    }
}

void Medical_history_panel::visit(){
    doctor=dynamic_cast<Doctor*>(const_cast<Worker*>(medical_history.Get_worker()));
    Visit_window* visit_window=new Visit_window(*doctor, this);
    std::string window_name="VISIT WINDOW of "+ doctor->Get_name() +" "+ doctor->Get_surname()+ " for patient: "+ (medical_history.Get_patient())->Get_codice_fiscale();
    visit_window->setWindowTitle(QString::fromStdString(window_name));
    visit_window->resize(600,200);
    visit_window->show();

    connect(visit_window, &Visit_window::finish, this, &Medical_history_panel::finish_visit);
}

void Medical_history_panel::finish_visit(){
    medical_history.Do_work();
    emit refresh_medical_history_list();
}

void Medical_history_panel::discharge(){
    if(dynamic_cast<Primary*>(const_cast<Worker*>(medical_history.Get_worker()))){
       medical_history.Do_work();
       emit refresh_medical_history_list();
    } else {
        Container<Worker*>::const_iterator it=worker_list.begin();
        while(it!=worker_list.end() && !(dynamic_cast<Primary*>(*it))){
            it++;
        }
        if(it==worker_list.end()){
            Error_window* error_window=new Error_window("Devi ancora inserire un/a primario/a\n/\nNon ci sono primari liberi!", this);
            error_window->resize(250,150);
            error_window->setWindowTitle("ERROR_NO_PRIMARY_FOUND");
            error_window->show();
        }
        else{
            try{
                doctor=dynamic_cast<Doctor*>(worker_list.remove(*it));
            } catch(const std::runtime_error& e){
                Error_window* error_window=new Error_window("RUNTIME ERROR", this);
                error_window->resize(250,150);
                error_window->setWindowTitle("RUNTIME ERROR");
                error_window->show();
            }

            worker_list.add(const_cast<Worker*>(medical_history.remove_worker()));
            emit refresh_worker_list();

            medical_history.Set_worker(doctor);
            medical_history.Do_work();
            emit refresh_medical_history_list();
        }
    }
}

void Medical_history_panel::remove_medical_history(){
    worker_list.add(const_cast<Worker*>(medical_history.remove_worker()));
    emit refresh_worker_list();

    medical_history_list.remove(&medical_history);
    emit refresh_medical_history_list();
};
