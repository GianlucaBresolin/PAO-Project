#ifndef VISIT_WINDOW_H
#define VISIT_WINDOW_H

#include <QVBoxLayout>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QCloseEvent>
#include "doctor.h"
#include "error_window.h"

class Visit_window: public QDialog{
    Q_OBJECT
    private:
        QLineEdit* lineEdit_sintomi;
        QLineEdit* lineEdit_diagnosi;

        Doctor& doctor;
    protected:
        void closeEvent(QCloseEvent *event) override;
    public:
        Visit_window(Doctor& d, QWidget* parent);
    signals:
        void finish();
    public slots:
        void inserisci_info();
};

#endif
