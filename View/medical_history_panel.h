#ifndef MEDICAL_HISTORY_PANEL_H
#define MEDICAL_HISTORY_PANEL_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QSpacerItem>
#include <QPushButton>
#include "medical_history.h"
#include "workerinfovisitor.h"
#include "container_template.h"
#include "doctor.h"
#include "error_window.h"
#include "visit_window.h"

class Medical_history_panel: public QWidget{
    Q_OBJECT
    private:
        Medical_history& medical_history;
        Container<Worker*>& worker_list;
        Container<Medical_history*>& medical_history_list;
        Doctor* doctor;
    public:
        Medical_history_panel(Medical_history& cartella_medica, Container<Worker*>& lista_operatori, Container<Medical_history*>& lista_cartelle_mediche, QWidget* parent=nullptr);
    signals:
        void refresh_worker_list();
        void refresh_medical_history_list();
        void ready();
        void delete_medical_history();
    public slots:
        void prepare_visit();
        void visit();
        void finish_visit();
        void discharge();
        void remove_medical_history();
};

#endif
