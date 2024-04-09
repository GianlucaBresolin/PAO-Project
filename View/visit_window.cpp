#include "visit_window.h"

Visit_window::Visit_window(Doctor& d, QWidget* parent): QDialog(parent), doctor(d){
    QVBoxLayout* layout=new QVBoxLayout(this);

    QLabel* sintomi_header=new QLabel("Sintomi:");
    layout->addWidget(sintomi_header);

    lineEdit_sintomi=new QLineEdit();
    lineEdit_sintomi->setFixedHeight(lineEdit_sintomi->fontMetrics().lineSpacing()*10);
    lineEdit_sintomi->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    lineEdit_sintomi->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    layout->addWidget(lineEdit_sintomi);

    QLabel* diagnosi_header=new QLabel("Diagnosi:");
    layout->addWidget(diagnosi_header);

    lineEdit_diagnosi=new QLineEdit();
    lineEdit_diagnosi->setFixedHeight(lineEdit_diagnosi->fontMetrics().lineSpacing()*10);
    lineEdit_diagnosi->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    lineEdit_diagnosi->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    layout->addWidget(lineEdit_diagnosi);

    QPushButton* conferma=new QPushButton("CONFERMA");
    conferma->setFixedWidth(100);
    connect(conferma, &QPushButton::clicked, this, &Visit_window::inserisci_info);
    QHBoxLayout* buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(conferma);
    buttonLayout->setAlignment(Qt::AlignCenter);
    layout->addLayout(buttonLayout);

}

void Visit_window::inserisci_info(){
    std::string sintomi_input=(lineEdit_sintomi->text()).toStdString();
    std::string diagnosi_input=(lineEdit_sintomi->text()).toStdString();
    if(sintomi_input.empty() || diagnosi_input.empty()){
        Error_window* error_window=new Error_window("Non hai inserito i sintomi e/o la diagnosi!", this);
        error_window->resize(250,150);
        error_window->setWindowTitle("VISIT_ERROR");
        error_window->show();
    } else{
        doctor.set_symptons(sintomi_input);
        doctor.set_diagnosis(diagnosi_input);
        emit finish();
        close();
    }
}

void Visit_window::closeEvent(QCloseEvent* event){
        if (lineEdit_sintomi->text().isEmpty() || lineEdit_diagnosi->text().isEmpty()) {
            event->ignore();
            Error_window* error_window=new Error_window("Non hai inserito i sintomi e/o la diagnosi!\nDevi prima inserire una sintomi e delle diagnosi valide prima\ndi poter chiudere la finestra.", this);
            error_window->resize(250,150);
            error_window->setWindowTitle("VISIT_ERROR");
            error_window->show();
        } else {
            event->accept();
        }
    }
