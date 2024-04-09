#include "error_window.h"

Error_window::Error_window(const std::string& error_string, QWidget* parent): QDialog(parent){
    QVBoxLayout* layout=new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter);

    QLabel* error_label=new QLabel(QString::fromStdString(error_string));
    error_label->setAlignment(Qt::AlignCenter);
    layout->addWidget(error_label);
}
