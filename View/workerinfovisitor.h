#ifndef WORKERINFOVISITOR_H
#define WORKERINFOVISITOR_H

#include "workervisitorinterface.h"
#include <QWidget>
#include <QLabel>

class WorkerInfoVisitor: public WorkerVisitorInterface{
    private:
    QWidget* widget;
    public:
    QWidget* getWidget();
    void visitNurse() override;
    void visitDoctor() override;
    void visitPrimary() override;
};

#endif
