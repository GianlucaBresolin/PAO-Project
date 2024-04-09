#ifndef ACCEPTANCE_WINDOW_H
#define ACCEPTANCE_WINDOW_H

#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include "nurse.h"

class Acceptance_window:public QDialog{
    Q_OBJECT
    private:
        QList<QPushButton*> allButtons;
        QPushButton* white_button=new QPushButton("BIANCO");
        QPushButton* green_button=new QPushButton("VERDE");
        QPushButton* blue_button=new QPushButton("BLU");
        QPushButton* orange_button=new QPushButton("ARANCIONE");
        QPushButton* red_button=new QPushButton("ROSSO");

        Nurse& nurse;

    public:
        Acceptance_window(Nurse& n, QWidget *parent);

    public slots:
        void onToggleButtonClicked();
        void setType();
};

#endif
