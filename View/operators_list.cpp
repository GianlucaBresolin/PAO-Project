#include "operators_list.h"

Operators_list::Operators_list(Container<Worker*>& lista_operatori, QWidget* parent): QWidget(parent), operators_list(lista_operatori){
  QVBoxLayout* mainLayout = new QVBoxLayout(this);
  mainLayout->setAlignment(Qt::AlignTop);

  QWidget* headerWidget = new QWidget();
  QHBoxLayout* intestazione=new QHBoxLayout(headerWidget);

  QLabel* int_tipo=new QLabel("OPERATORE");
  int_tipo->setAlignment(Qt::AlignCenter);
  intestazione->addWidget(int_tipo);

  QLabel* int_nome=new QLabel("NOME");
  int_nome->setAlignment(Qt::AlignCenter);
  intestazione->addWidget(int_nome);

  QLabel* int_cognome=new QLabel("COGNOME");
  int_cognome->setAlignment(Qt::AlignCenter);
  intestazione->addWidget(int_cognome);

  QLabel* int_data_nascita=new QLabel("DATA DI NASCITA");
  int_data_nascita->setAlignment(Qt::AlignCenter);
  intestazione->addWidget(int_data_nascita);

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

  Container<Worker*>::const_iterator it;
  for(it=operators_list.begin(); it!=operators_list.end(); it++){
      Operator_panel* operator_widget=new Operator_panel(*(*it), operators_list, this);
      connect(operator_widget, &Operator_panel::refresh_workers_list, this, &Operators_list::refresh);
      connect(operator_widget, &Operator_panel::refresh_workers_list, this, &Operators_list::save);

      QListWidgetItem* item=new QListWidgetItem();
      item->setSizeHint(operator_widget->sizeHint());
      listWidget->addItem(item);
      listWidget->setItemWidget(item, operator_widget);
  }

  mainLayout->addWidget(listWidget);
}

void Operators_list::refresh(){
    listWidget->clear();

    Container<Worker*>::const_iterator it;
    for(it=operators_list.begin(); it!=operators_list.end(); it++){
        Operator_panel* operator_widget=new Operator_panel(*(*it), operators_list, this);
        connect(operator_widget, &Operator_panel::refresh_workers_list, this, &Operators_list::refresh);
        connect(operator_widget, &Operator_panel::refresh_workers_list, this, &Operators_list::save);

        QListWidgetItem* item=new QListWidgetItem();
        item->setSizeHint(operator_widget->sizeHint());
        listWidget->addItem(item);
        listWidget->setItemWidget(item, operator_widget);
    }
}
