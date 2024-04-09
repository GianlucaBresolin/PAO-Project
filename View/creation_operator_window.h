#ifndef CREATION_OPERATOR_WINDOW_H
#define CREATION_OPERATOR_WINDOW_H

#include <QDialog>
#include <QLineEdit>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include "error_window.h"
#include "nurse.h"
#include "doctor.h"
#include "primary.h"
#include "medical_history.h"
#include "container_template.h"

class Creation_operator_window:public QDialog{
    Q_OBJECT
    private:
    Container<Worker*>& operators_list;
    Container<Medical_history*>& lista_cartelle_mediche_white;
    Container<Medical_history*>& lista_cartelle_mediche_green;
    Container<Medical_history*>& lista_cartelle_mediche_blue;
    Container<Medical_history*>& lista_cartelle_mediche_orange;
    Container<Medical_history*>& lista_cartelle_mediche_red;
    QList<QPushButton*> allButtons;
    QPushButton* nurse_button=new QPushButton("Infermiere");
    bool nurse_type;
    QPushButton* doctor_button=new QPushButton("Dottore");
    bool doctor_type;
    QPushButton* primary_button=new QPushButton("Primario");
    bool primary_type;
    QLineEdit* lineEdit_name;
    QLineEdit* lineEdit_surname;
    QLineEdit* lineEdit_birth_date;

    public:
        Creation_operator_window(Container<Worker*>& lista_operatori, Container<Medical_history*>& medical_history_white_list, Container<Medical_history*>& medical_history_green_list, Container<Medical_history*>& medical_history_blue_list, Container<Medical_history*>& medical_history_orange_list, Container<Medical_history*>& medical_history_red_list, QWidget *parent);

    signals:
        void clear_for_add();

    public slots:
        void add_operator();
        void onToggleButtonClicked();
        void setType();
};

#endif
