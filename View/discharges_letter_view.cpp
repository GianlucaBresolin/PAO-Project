#include "discharges_letter_view.h"

Discharges_letter_view::Discharges_letter_view(const std::string& lettera_dimissione, QWidget* parent): QDialog(parent){
    QVBoxLayout* layout=new QVBoxLayout(this);

    QLabel* label_nome_lettera=new QLabel(QString::fromStdString(lettera_dimissione));
    label_nome_lettera->setAlignment(Qt::AlignLeft);
    layout->addWidget(label_nome_lettera, Qt::AlignLeft | Qt::AlignTop);
}
