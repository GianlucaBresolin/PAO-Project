#include "doctor.h"
#include "medical_history.h"
#include <limits>

Doctor::Doctor(const std::string& n, const std::string& s, const std::string& d): Worker(n,s,d){};

Doctor::Doctor(const Doctor& d): Worker(d){};

void Doctor::set_symptons(const std::string& sintomi){
    symptons="Sintomi: \n"+sintomi;
}

void Doctor::set_diagnosis(const std::string& diagnosi){
    diagnosis="\n\nDiagnosi: \n"+diagnosi+"\n\n";
}

void Doctor::work(Medical_history& m) const{
    const Patient* p=m.Get_patient();
    if(m.Get_state()==Patients_state::Visit)
        m.Change_State();
    
    std::string writing("Il/la paziente "+p->Get_name()+" "+p->Get_surname()+"\ne' stato/a visitato/a dal dott./dott.ssa "+Get_name()+" "+Get_surname()+"\n\n");
    m.Write_documentation(writing);

    m.Write_documentation(symptons);

    m.Write_documentation(diagnosis);
}

void Doctor::accept(WorkerVisitorInterface& visitor) const{
    visitor.visitDoctor();
}

bool Doctor::operator==(const Worker& d) const{
    return ((dynamic_cast<const Worker*>(&d)!=nullptr) && Get_name()==d.Get_name() && Get_surname()==d.Get_surname() && Get_birth_date()==d.Get_birth_date());
}

bool Doctor::operator!=(const Worker& d) const{
    return !(*this==d);
}
