#ifndef PRIMARY_H
#define PRIMARY_H

#include "doctor.h"

class Primary: public Doctor{

    public:

    Primary(const std::string& ="...", const std::string& ="...", const std::string& ="../../..");
    Primary(const Primary&);

    void work(Medical_history&) const override;

    void accept(WorkerVisitorInterface& visitor) const override;

    bool operator==(const Worker&) const;
    bool operator!=(const Worker&) const;

    ~Primary() override{};

};

#endif
