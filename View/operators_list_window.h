#ifndef OPERATORS_LIST_WINDOW_H
#define OPERATORS_LIST_WINDOW_H

#include <QDialog>
#include <QHBoxLayout>
#include "doctor.h"
#include "nurse.h"
#include "primary.h"
#include "container_template.h"
#include "operators_list.h"

class Operators_list_window: public QDialog{
    Q_OBJECT
    public:
        Operators_list_window(Container<Worker*>& lista_operatori, QWidget* parent=nullptr);

    signals:
        void clear_list();
        void save();
};

#endif
