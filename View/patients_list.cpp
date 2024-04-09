#include "patients_list.h"

Patients_list::Patients_list(Container<Patient*>& lista_pazienti, Container<Medical_history*>& medical_history_unsettled_list, Container<Medical_history*>& medical_history_white_list, Container<Medical_history*>& medical_history_green_list, Container<Medical_history*>& medical_history_blue_list, Container<Medical_history*>& medical_history_orange_list, Container<Medical_history*>& medical_history_red_list, QWidget* parent): QWidget(parent), patients_list(lista_pazienti), lista_cartelle_mediche_unsettled(medical_history_unsettled_list), lista_cartelle_mediche_white(medical_history_white_list), lista_cartelle_mediche_green(medical_history_green_list), lista_cartelle_mediche_blue(medical_history_blue_list), lista_cartelle_mediche_orange(medical_history_orange_list), lista_cartelle_mediche_red(medical_history_red_list){
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setAlignment(Qt::AlignTop);

    QWidget* headerWidget = new QWidget();
    QHBoxLayout* intestazione=new QHBoxLayout(headerWidget);
    QLabel* int_nome=new QLabel("NOME");
    int_nome->setAlignment(Qt::AlignCenter);
    intestazione->addWidget(int_nome);

    QLabel* int_cognome=new QLabel("COGNOME");
    int_cognome->setAlignment(Qt::AlignCenter);
    intestazione->addWidget(int_cognome);

    QLabel* int_data_nascita=new QLabel("DATA DI NASCITA");
    int_data_nascita->setAlignment(Qt::AlignCenter);
    intestazione->addWidget(int_data_nascita);

    QLabel* int_cod_fiscale=new QLabel("CODICE FISCALE");
    int_cod_fiscale->setAlignment(Qt::AlignCenter);
    intestazione->addWidget(int_cod_fiscale);

    QLabel* int_storico=new QLabel("STORICO");
    int_storico->setAlignment(Qt::AlignRight);
    intestazione->addWidget(int_storico);

    QLabel* int_modifica=new QLabel("MODIFICA");
    int_modifica->setAlignment(Qt::AlignRight);
    intestazione->addWidget(int_modifica);

    QLabel* int_elimina=new QLabel("ELIMINA");
    int_elimina->setAlignment(Qt::AlignRight);
    intestazione->addWidget(int_elimina);

    mainLayout->addWidget(headerWidget);

    listWidget=new QListWidget(this);
    listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    listWidget->setUniformItemSizes(true);
    listWidget->setStyleSheet("QListWidget { border: 1px solid black; }"
                              "QListWidget::item { border-bottom: 1px solid black; }");

    Container<Patient*>::const_iterator it;
    for(it=patients_list.begin(); it!=patients_list.end(); it++){
        Patient_panel* patient_widget=new Patient_panel(*(*it), patients_list, lista_cartelle_mediche_unsettled, lista_cartelle_mediche_white, lista_cartelle_mediche_green, lista_cartelle_mediche_blue, lista_cartelle_mediche_orange, lista_cartelle_mediche_red, this);
        connect(patient_widget, &Patient_panel::refresh_patients_list, this, &Patients_list::refresh);
        connect(patient_widget, &Patient_panel::refresh_patients_list, this, &Patients_list::save);

        QListWidgetItem* item=new QListWidgetItem();
        item->setSizeHint(patient_widget->sizeHint());
        listWidget->addItem(item);
        listWidget->setItemWidget(item, patient_widget);
    }

    mainLayout->addWidget(listWidget);
}

void Patients_list::refresh(){
    listWidget->clear();

    Container<Patient*>::const_iterator it;
    for(it=patients_list.begin(); it!=patients_list.end(); it++){
        Patient_panel* patient_widget=new Patient_panel(*(*it), patients_list, lista_cartelle_mediche_unsettled, lista_cartelle_mediche_white, lista_cartelle_mediche_green, lista_cartelle_mediche_blue, lista_cartelle_mediche_orange, lista_cartelle_mediche_red, this);
        connect(patient_widget, &Patient_panel::refresh_patients_list, this, &Patients_list::refresh);
        connect(patient_widget, &Patient_panel::refresh_patients_list, this, &Patients_list::save);

        QListWidgetItem* item=new QListWidgetItem();
        item->setSizeHint(patient_widget->sizeHint());
        listWidget->addItem(item);
        listWidget->setItemWidget(item, patient_widget);
    }
}
