#ifndef MEDICAL_HISTORY_LIST_H
#define MEDICAL_HISTORY_LIST_H

#include <QWidget>
#include <QListWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include "medical_history.h"
#include "container_template.h"
#include "medical_history_panel.h"

class Medical_history_list: public QWidget{
    Q_OBJECT
    private:
        QListWidget* listWidget;
        Container<Medical_history*>& medical_history_list;
        Container<Worker*>& worker_list;
    public:
        Medical_history_list(Container<Medical_history*>& lista_cartelle_mediche, Container<Worker*>& lista_operatori, QWidget* parent);
    signals:
        void refresh_worker_list();
        void save();
    public slots:
        void refresh();
};

#endif
