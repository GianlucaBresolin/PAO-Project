#ifndef CREATION_MEDICAL_HISTORY_WINDOW_H
#define CREATION_MEDICAL_HISTORY_WINDOW_H

#include <QDialog>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include "patient.h"
#include "medical_history.h"
#include "container_template.h"
#include "error_window.h"

class Creation_medical_history_window: public QDialog{
    Q_OBJECT
    private:
        Container<Medical_history*>& lista_cartelle_mediche_unsettled;
        Container<Medical_history*>& lista_cartelle_mediche_white;
        Container<Medical_history*>& lista_cartelle_mediche_green;
        Container<Medical_history*>& lista_cartelle_mediche_blue;
        Container<Medical_history*>& lista_cartelle_mediche_orange;
        Container<Medical_history*>& lista_cartelle_mediche_red;
        const Patient* paziente;
    public:
        Creation_medical_history_window(Container<Medical_history*>& medical_history_unsettled_list, Container<Medical_history*>& medical_history_white_list, Container<Medical_history*>& medical_history_green_list, Container<Medical_history*>& medical_history_blue_list, Container<Medical_history*>& medical_history_orange_list, Container<Medical_history*>& medical_history_red_list, const Patient* patient, QWidget* parent);
    signals:
        void clear_for_add();
        void close();
    public slots:
        void Add_medical_history();
};

#endif
