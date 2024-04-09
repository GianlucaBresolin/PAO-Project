#include "discharges_letter_panel.h"

Discharges_letter_panel::Discharges_letter_panel(const std::string& lettera_dimissioni, int& c, QWidget* parent): QWidget(parent), discharges_letter(lettera_dimissioni){
    QHBoxLayout* layout=new QHBoxLayout(this);

    std::string nome_lettera="Lettera Dimissione #"+ std::to_string(c);
    QLabel* label_nome_lettera=new QLabel(QString::fromStdString(nome_lettera));
    label_nome_lettera->setAlignment(Qt::AlignCenter);
    layout->addWidget(label_nome_lettera, Qt::AlignLeft);

    QPushButton* open=new QPushButton("Apri");
    open->setFixedWidth(50);
    connect(open, &QPushButton::clicked, this, &Discharges_letter_panel::Open_discharges_letter);
    layout->addWidget(open, Qt::AlignCenter);

}

void Discharges_letter_panel::Open_discharges_letter(){
    Discharges_letter_view* view=new Discharges_letter_view(discharges_letter, this);
    view->setWindowTitle("Lettera di Dimissione");
    view->show();
}
