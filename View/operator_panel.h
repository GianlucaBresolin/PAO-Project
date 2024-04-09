#ifndef OPERATOR_PANEL_H
#define OPERATOR_PANEL_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "nurse.h"
#include "doctor.h"
#include "primary.h"
#include "workerinfovisitor.h"
#include "container_template.h"
#include "edit_operator_window.h"

class Operator_panel: public QWidget{
    Q_OBJECT
    private:
        const Worker& worker;
        Container<Worker*>& workers_list;
    public:
        Operator_panel(const Worker& operatore, Container<Worker*>& lista_operatori, QWidget *parent = nullptr);
    signals:
        void refresh_workers_list();
    public slots:
        void modifica_operatore();
        void elimina_operatore();
};

#endif
