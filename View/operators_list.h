#ifndef OPERATORS_LIST_H
#define OPERATORS_LIST_H

#include <QWidget>
#include <QLabel>
#include <QListWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "nurse.h"
#include "doctor.h"
#include "primary.h"
#include "container_template.h"
#include "operator_panel.h"

class Operators_list: public QWidget{
    Q_OBJECT
    private:
        QListWidget* listWidget;
        Container<Worker*>& operators_list;
    public:
        Operators_list(Container<Worker*>& lista_operatori, QWidget* parent=nullptr);
    signals:
        void save();
    public slots:
        void refresh();
};

#endif
