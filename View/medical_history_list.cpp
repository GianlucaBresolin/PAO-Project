#include "medical_history_list.h"

Medical_history_list::Medical_history_list(Container<Medical_history*>& lista_cartelle_mediche, Container<Worker*>& lista_operatori, QWidget* parent): QWidget(parent), medical_history_list(lista_cartelle_mediche), worker_list(lista_operatori){
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setAlignment(Qt::AlignTop);

    QWidget* headerWidget = new QWidget();
    QHBoxLayout* intestazione=new QHBoxLayout(headerWidget);
    intestazione->setSpacing(30);
    QLabel* int_cod_fiscale=new QLabel("CODICE FISCALE");
    int_cod_fiscale->setAlignment(Qt::AlignCenter);
    intestazione->addWidget(int_cod_fiscale);

    QLabel* int_state=new QLabel("STATO");
    int_state->setAlignment(Qt::AlignCenter);
    intestazione->addWidget(int_state);

    QLabel* int_codice=new QLabel("CODICE");
    int_codice->setAlignment(Qt::AlignCenter);
    intestazione->addWidget(int_codice);

    QLabel* int_tipo_operatore=new QLabel("TIPO OPERATORE");
    int_tipo_operatore->setAlignment(Qt::AlignCenter);
    intestazione->addWidget(int_tipo_operatore);

    QLabel* int_operatore=new QLabel("OPERATORE");
    int_operatore->setAlignment(Qt::AlignCenter);
    intestazione->addWidget(int_operatore);

    QLabel* int_azione=new QLabel("AZIONE");
    int_azione->setAlignment(Qt::AlignCenter);
    intestazione->addWidget(int_azione);

    mainLayout->addWidget(headerWidget);

    listWidget=new QListWidget(this);
    listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    listWidget->setUniformItemSizes(true);
    listWidget->setStyleSheet("QListWidget { border: 1px solid black; }"
                              "QListWidget::item { border-bottom: 1px solid black; }");

    Container<Medical_history*>::const_iterator it;
    for(it=medical_history_list.begin(); it!=medical_history_list.end(); it++){
        Medical_history_panel* medical_history_widget=new Medical_history_panel(*(const_cast<Medical_history*>(*it)), worker_list, medical_history_list, this);
        connect(medical_history_widget, &Medical_history_panel::refresh_worker_list, this, &Medical_history_list::refresh_worker_list);
        connect(medical_history_widget, &Medical_history_panel::refresh_medical_history_list, this, &Medical_history_list::refresh);
        connect(medical_history_widget, &Medical_history_panel::refresh_medical_history_list, this, &Medical_history_list::save);

        QListWidgetItem* item=new QListWidgetItem();
        item->setSizeHint(medical_history_widget->sizeHint());
        listWidget->addItem(item);
        listWidget->setItemWidget(item, medical_history_widget);
    }

    mainLayout->addWidget(listWidget);

}

void Medical_history_list::refresh(){
    listWidget->clear();

    Container<Medical_history*>::const_iterator it;
    for(it=medical_history_list.begin(); it!=medical_history_list.end(); it++){
        Medical_history_panel* medical_history_widget=new Medical_history_panel(*(const_cast<Medical_history*>(*it)), worker_list, medical_history_list, this);
        connect(medical_history_widget, &Medical_history_panel::refresh_worker_list, this, &Medical_history_list::refresh_worker_list);
        connect(medical_history_widget, &Medical_history_panel::refresh_medical_history_list, this, &Medical_history_list::refresh);
        connect(medical_history_widget, &Medical_history_panel::refresh_medical_history_list, this, &Medical_history_list::save);


        QListWidgetItem* item=new QListWidgetItem();
        item->setSizeHint(medical_history_widget->sizeHint());
        listWidget->addItem(item);
        listWidget->setItemWidget(item, medical_history_widget);
    }
}
