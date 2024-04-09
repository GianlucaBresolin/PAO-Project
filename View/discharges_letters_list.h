#ifndef DISCHARGES_LETTERS_LIST_H
#define DISCHARGES_LETTERS_LIST_H

#include <QDialog>
#include <QLabel>
#include <QListWidget>
#include <QVBoxLayout>
#include "container_template.h"
#include "discharges_letter_panel.h"


class Discharges_letters_list: public QDialog{
    Q_OBJECT
    private:
        const Container<const std::string>& discharges_letters_list;
        QListWidget* listWidget;
    public:
        Discharges_letters_list(const Container<const std::string>& lista_lettere_dimissioni, QWidget* parent=nullptr);
    public slots:
        void refresh();
};

#endif
