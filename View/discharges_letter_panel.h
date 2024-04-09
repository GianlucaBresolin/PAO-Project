#ifndef DISCHARGES_LETTER_PANEL_H
#define DISCHARGES_LETTER_PANEL_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "discharges_letter_view.h"

class Discharges_letter_panel: public QWidget{
    Q_OBJECT
    const std::string& discharges_letter;
    public:
        Discharges_letter_panel(const std::string& lettera_dimissioni, int& c, QWidget* parent=nullptr);
    public slots:
        void Open_discharges_letter();
};

#endif
