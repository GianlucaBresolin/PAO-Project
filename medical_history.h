#ifndef MEDICAL_HISTORY_H
#define MEDICAL_HISTORY_H

#include "patient.h"
#include "patients_state.h"
#include "medical_code.h"
#include "nurse.h"
#include "worker.h"
#include "primary.h"

class Medical_history{
    
    private:

    const Patient* patient;
    const Worker* worker;
    Patients_state state;
    Medical_code cod;
    std::string documentation;

    public:

    Medical_history(const Patient*);
    Medical_history(const Medical_history&);

    Patients_state Get_state() const;
    const std::string Get_string_state() const;
    void Change_State();
    void Set_string_state(const std::string&);

    const Patient* Get_patient() const;

    void Set_worker(const Worker*);
    void Do_work();
    const Worker* Get_worker() const;
    const Worker* remove_worker();

    void Set_cod(const std::string&);
    const std::string Get_cod() const;
    Medical_code Get_medical_code() const;

    void Write_documentation(const std::string&);
    void Set_documentation(const std::string&);
    const std::string& Get_Documentation() const;

    void End_medical_history();
    void Delete_medical_history();

    bool operator==(const Medical_history&) const;
    bool operator!=(const Medical_history&) const;

    ~Medical_history(){};

};

#endif
