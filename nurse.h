#ifndef NURSE_H
#define NURSE_H

#include "worker.h"
#include "medical_code.h"

class Nurse: public Worker{
    private:

    std::string patients_code;

    public:

    Nurse(const std::string& ="...", const std::string& ="...", const std::string& ="../../..");
    Nurse(const Nurse&);

    void set_patients_code(const std::string&);
    const std::string& get_patients_code() const;

    void work(Medical_history&) const override;

    void accept(WorkerVisitorInterface& visitor) const override;

    bool operator==(const Worker&) const;
    bool operator!=(const Worker&) const;

    ~Nurse() override{};
    
};

#endif
