#ifndef EDIT_OPERATOR_WINDOW_H
#define EDIT_OPERATOR_WINDOW_H

#include <QDialog>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QLineEdit>
#include "worker.h"
#include "nurse.h"
#include "primary.h"
#include "container_template.h"
#include "error_window.h"

class Edit_operator_window: public QDialog{
    Q_OBJECT
    private:
        Worker& worker;
        Container<Worker*>& workers_list;
        QLineEdit* lineEdit_name;
        QLineEdit* lineEdit_surname;
        QLineEdit* lineEdit_birth_date;
    public:
        Edit_operator_window(Worker& operatore, Container<Worker*>& lista_operatori, QWidget* parent=nullptr);
    signals:
        void clear_for_edit();

    public slots:
        void edit_worker();
};

#endif
