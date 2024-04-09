#ifndef WORKER_H
#define WORKER_H

#include "person.h"
#include "workervisitorinterface.h"
#include <iostream>

class Medical_history;

class Worker: public Person{
    public:

    Worker(const std::string& ="...", const std::string& ="...", const std::string& ="../../..");
    Worker(const Worker&);

    virtual void work(Medical_history& m) const=0;

    bool operator==(const Worker&) const;
    bool operator!=(const Worker&) const;

    virtual void accept(WorkerVisitorInterface& visitor) const = 0;

    ~Worker() override{};

};

#endif
