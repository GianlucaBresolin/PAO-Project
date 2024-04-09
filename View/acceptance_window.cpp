#include "acceptance_window.h"

Acceptance_window::Acceptance_window(Nurse& n, QWidget *parent): QDialog(parent), nurse(n){
    QVBoxLayout* layout=new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter);

    nurse.set_patients_code("White");

    QLabel* creazione_paziente=new QLabel();
    creazione_paziente->setText("SELEZIONA CODICE PAZIENTE");
    creazione_paziente->setAlignment(Qt::AlignCenter);
    layout->addWidget(creazione_paziente, Qt::AlignCenter);

    allButtons.push_back(white_button);
    white_button->setChecked(true);
    layout->addWidget(white_button, Qt::AlignCenter);
    connect(white_button, &QPushButton::clicked, this, &Acceptance_window::setType);
    connect(white_button, &QPushButton::clicked, this, &Acceptance_window::onToggleButtonClicked);

    allButtons.push_back(green_button);
    green_button->setChecked(false);
    layout->addWidget(green_button, Qt::AlignCenter);
    connect(green_button, &QPushButton::clicked, this, &Acceptance_window::setType);
    connect(green_button, &QPushButton::clicked, this, &Acceptance_window::onToggleButtonClicked);

    allButtons.push_back(blue_button);
    blue_button->setChecked(false);
    layout->addWidget(blue_button, Qt::AlignCenter);
    connect(blue_button, &QPushButton::clicked, this, &Acceptance_window::setType);
    connect(blue_button, &QPushButton::clicked, this, &Acceptance_window::onToggleButtonClicked);

    allButtons.push_back(orange_button);
    orange_button->setChecked(false);
    layout->addWidget(orange_button, Qt::AlignCenter);
    connect(orange_button, &QPushButton::clicked, this, &Acceptance_window::setType);
    connect(orange_button, &QPushButton::clicked, this, &Acceptance_window::onToggleButtonClicked);

    allButtons.push_back(red_button);
    red_button->setChecked(false);
    layout->addWidget(red_button, Qt::AlignCenter);
    connect(red_button, &QPushButton::clicked, this, &Acceptance_window::setType);
    connect(red_button, &QPushButton::clicked, this, &Acceptance_window::onToggleButtonClicked);

    QPushButton* conferma=new QPushButton("CONFERMA");
    conferma->setFixedWidth(100);
    connect(conferma, &QPushButton::clicked, this, &Acceptance_window::reject);
    QHBoxLayout* buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(conferma);
    buttonLayout->setAlignment(Qt::AlignCenter);
    layout->addLayout(buttonLayout);

}

void Acceptance_window::onToggleButtonClicked(){

    QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());
    
    for (QList<QPushButton*>::iterator it = allButtons.begin(); it != allButtons.end(); ++it){
        if (*it!=clickedButton){
            (*it)->setChecked(false);
        }
    }
    clickedButton->setChecked(true);
}

void Acceptance_window::setType(){

    QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());

    if(clickedButton==white_button){
        nurse.set_patients_code("White");
    } else if(clickedButton==green_button){
        nurse.set_patients_code("Green");
    } else if(clickedButton==blue_button){
        nurse.set_patients_code("Blue");
    } else if(clickedButton==orange_button){
        nurse.set_patients_code("Orange");
    } else {
        nurse.set_patients_code("Red");
    }
}
