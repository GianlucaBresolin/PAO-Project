#include "discharges_letters_list.h"

Discharges_letters_list::Discharges_letters_list(const Container<const std::string>& lista_lettere_dimissioni, QWidget* parent): QDialog(parent), discharges_letters_list(lista_lettere_dimissioni){
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setAlignment(Qt::AlignTop);

    listWidget=new QListWidget(this);
    listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    listWidget->setUniformItemSizes(true);
    listWidget->setStyleSheet("QListWidget { border: 1px solid black; }"
                              "QListWidget::item { border-bottom: 1px solid black; }");

    int c=0;
    Container<const std::string>::const_iterator it;
    for(it=discharges_letters_list.begin(); it!=discharges_letters_list.end(); it++){
        c++;
        Discharges_letter_panel* discharges_letter_widget=new Discharges_letter_panel(*it, c, this);

        QListWidgetItem* item=new QListWidgetItem();
        item->setSizeHint(discharges_letter_widget->sizeHint());
        listWidget->addItem(item);
        listWidget->setItemWidget(item, discharges_letter_widget);
    }

    mainLayout->addWidget(listWidget);
}

void Discharges_letters_list::refresh(){
    listWidget->clear();

    int c=0;
    Container<const std::string>::const_iterator it;
    for(it=discharges_letters_list.begin(); it!=discharges_letters_list.end(); it++){
        c++;
        Discharges_letter_panel* discharges_letter_widget=new Discharges_letter_panel(*it, c, this);

        QListWidgetItem* item=new QListWidgetItem();
        item->setSizeHint(discharges_letter_widget->sizeHint());
        listWidget->addItem(item);
        listWidget->setItemWidget(item, discharges_letter_widget);
    }
}
