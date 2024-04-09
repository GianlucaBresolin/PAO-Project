#ifndef DOCTOR_H
#define DOCTOR_H

#include "worker.h"

class Doctor: public Worker{
    private:
    std::string symptons;
    std::string diagnosis;

    public:

    Doctor(const std::string& ="...", const std::string& ="...", const std::string& ="../../..");
    Doctor(const Doctor&);

    void set_symptons(const std::string&);
    void set_diagnosis(const std::string&);

    void work(Medical_history&) const override;

    void accept(WorkerVisitorInterface& visitor) const override;

    bool operator==(const Worker&) const;
    bool operator!=(const Worker&) const;

    ~Doctor() override{};

};

#endif
