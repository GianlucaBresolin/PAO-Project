#ifndef DISCHARGES_LETTER_VIEW_H
#define DISCHARGES_LETTER_VIEW_H

#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>

class Discharges_letter_view: public QDialog{
public:
    Discharges_letter_view(const std::string& lettera_dimissione, QWidget* parent);
};

#endif
