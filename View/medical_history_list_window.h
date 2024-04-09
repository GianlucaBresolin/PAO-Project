#ifndef MEDICAL_HISTORY_LIST_WINDOW_H
#define MEDICAL_HISTORY_LIST_WINDOW_H

#include <QDialog>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include "medical_history.h"
#include "container_template.h"
#include "medical_history_list.h"
#include "error_window.h"
#include "acceptance_window.h"

class Medical_history_list_window: public QDialog{
    Q_OBJECT
    private:
        Container<Medical_history*>& medical_history_unsettled_list;
        Container<Medical_history*>& medical_history_white_list;
        Container<Medical_history*>& medical_history_green_list;
        Container<Medical_history*>& medical_history_blue_list;
        Container<Medical_history*>& medical_history_orange_list;
        Container<Medical_history*>& medical_history_red_list;
        Container<Worker*>& worker_list;

        Nurse* nurse;
        Medical_history* cartella;
    public:
        Medical_history_list_window(Container<Medical_history*>& lista_cartelle_mediche_unsettled, Container<Medical_history*>& lista_cartelle_mediche_bianco, Container<Medical_history*>& lista_cartelle_mediche_verde, Container<Medical_history*>& lista_cartelle_mediche_blu, Container<Medical_history*>& lista_cartelle_mediche_arancione, Container<Medical_history*>& lista_cartelle_mediche_rosso, Container<Worker*>& lista_operatori, QWidget* parent=nullptr);
    signals:
        void clear_unsettled_list();
        void clear_white_list();
        void clear_green_list();
        void clear_blue_list();
        void clear_orange_list();
        void clear_red_list();
        void refresh_worker_list();
        void save();
    public slots:
        void Acceptance_get_nurse();
        void Acceptance_insert_medical_history();

};

#endif
