#include "operator_panel.h"

Operator_panel::Operator_panel(const Worker& operatore, Container<Worker*>& lista_operatori, QWidget *parent): QWidget(parent), worker(operatore), workers_list(lista_operatori){
    QHBoxLayout* layout=new QHBoxLayout(this);

    WorkerInfoVisitor visitor;
    operatore.accept(visitor);
    layout->addWidget(visitor.getWidget());

    QLabel* label_nome=new QLabel(QString::fromStdString(worker.Get_name()));
    label_nome->setAlignment(Qt::AlignCenter);
    layout->addWidget(label_nome);

    QLabel* label_cognome=new QLabel(QString::fromStdString(worker.Get_surname()));
    label_cognome->setAlignment(Qt::AlignCenter);
    layout->addWidget(label_cognome);

    QLabel* label_data_di_nascita=new QLabel(QString::fromStdString(worker.Get_birth_date()));
    label_data_di_nascita->setAlignment(Qt::AlignCenter);
    layout->addWidget(label_data_di_nascita);

    QPushButton* modifica=new QPushButton("Modifica");
    modifica->setFixedWidth(65);
    connect(modifica, &QPushButton::clicked, this, &Operator_panel::modifica_operatore);
    layout->addWidget(modifica, Qt::AlignCenter);

    QPushButton* elimina=new QPushButton("Elimina");
    elimina->setFixedWidth(65);
    connect(elimina, &QPushButton::clicked, this, &Operator_panel::elimina_operatore);
    layout->addWidget(elimina, Qt::AlignCenter);
}

void Operator_panel::modifica_operatore(){
    Edit_operator_window* edit_operator_window=new Edit_operator_window(const_cast<Worker&>(worker), workers_list, this);
    std::string window_name="EDIT WINDOW for OPERATOR: "+worker.Get_name()+" "+worker.Get_surname();
    edit_operator_window->setWindowTitle(QString::fromStdString(window_name));
    edit_operator_window->resize(600,400);
    edit_operator_window->show();

    connect(edit_operator_window, &Edit_operator_window::clear_for_edit, this, &Operator_panel::refresh_workers_list);
}

void Operator_panel::elimina_operatore(){
    workers_list.remove(const_cast<Worker*>(&worker));
    delete const_cast<Worker*>(&worker);

    emit refresh_workers_list();
}
