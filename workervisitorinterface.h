#ifndef WORKERVISITORINTERFACE_H
#define WORKERVISITORINTERFACE_H

class Nurse;
class Doctor;
class Primary;

class WorkerVisitorInterface{
    public:
    virtual ~WorkerVisitorInterface() = default;
    virtual void visitNurse() = 0;
    virtual void visitDoctor() = 0;
    virtual void visitPrimary() = 0;
};

#endif
