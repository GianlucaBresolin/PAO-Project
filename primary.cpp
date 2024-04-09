#include "primary.h"
#include "medical_history.h"

Primary::Primary(const std::string& n, const std::string& s, const std::string& d): Doctor(n,s,d) {};

Primary::Primary(const Primary& p): Doctor(p){};

void Primary::work(Medical_history& m) const {
    const Patient* p=m.Get_patient();
    if(m.Get_state()==Patients_state::End_visit)
        m.Change_State();

    std::string writing("Il/la paziente "+p->Get_name()+" "+p->Get_surname()+"\ne' stato/a dimesso/a sotto responsabilita' del/della dott./dott.ssa "+Get_name()+" "+Get_surname()+"\n\n");
    m.Write_documentation(writing);
    
    (const_cast<Patient*>(m.Get_patient()))->Aggiungi_lettera_dimissioni((m.Get_Documentation()));
}

void Primary::accept(WorkerVisitorInterface& visitor) const{
    visitor.visitPrimary();
}

bool Primary::operator==(const Worker& p) const{
    return (dynamic_cast<const Primary*>(&p)!=nullptr && Get_name()==p.Get_name() && Get_surname()==p.Get_surname() && Get_birth_date()==p.Get_birth_date());
}

bool Primary::operator!=(const Worker& p) const{
    return !(*this==p);
}
