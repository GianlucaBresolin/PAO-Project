#include "workerinfovisitor.h"

QWidget* WorkerInfoVisitor::getWidget(){
    return widget;
}

void WorkerInfoVisitor::visitNurse(){
    QLabel* label=new QLabel("INFERMIERE/A");
    label->setAlignment(Qt::AlignCenter);
    widget=label;
}

void WorkerInfoVisitor::visitDoctor(){
    QLabel* label=new QLabel("DOTT./DOTT.SSA");
    label->setAlignment(Qt::AlignCenter);
    widget=label;
}

void WorkerInfoVisitor::visitPrimary(){
    QLabel* label=new QLabel("PRIMARIO/A");
    label->setAlignment(Qt::AlignCenter);
    widget=label;
}
