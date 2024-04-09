#include "operators_list_window.h"

Operators_list_window::Operators_list_window(Container<Worker*>& lista_operatori, QWidget* parent): QDialog(parent){
    QHBoxLayout* layout=new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    Operators_list* operators_list=new Operators_list(lista_operatori, this);
    connect(this, &Operators_list_window::clear_list, operators_list, &Operators_list::refresh);
    connect(operators_list, &Operators_list::save, this, &Operators_list_window::save);
    layout->addWidget(operators_list);
}
