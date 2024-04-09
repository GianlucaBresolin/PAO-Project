#ifndef ERROR_WINDOW_H
#define ERROR_WINDOW_H

#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>

class Error_window: public QDialog{
    Q_OBJECT
    public:
        Error_window(const std::string& error_string, QWidget* parent);
};

#endif
