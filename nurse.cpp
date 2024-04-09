#include "nurse.h"
#include "medical_history.h"

Nurse::Nurse(const std::string& n, const std::string& s, const std::string& d): Worker(n,s,d), patients_code("Unsettled"){};

Nurse::Nurse(const Nurse& n): Worker(n){};

void Nurse::set_patients_code(const std::string& cod){
    patients_code=cod;
}

const std::string& Nurse::get_patients_code() const{
    return patients_code;
}

void Nurse::work(Medical_history& m) const{
    const Patient* p=m.Get_patient();
    if(m.Get_state()==Patients_state::Pre_acceptance)
        m.Change_State();
    
    m.Set_cod(patients_code);

    std::string writing("Il/la paziente "+p->Get_name()+" "+p->Get_surname()+"\ne' stato/a accolto/a in accettazione dall'operatore "+Get_name()+" "+Get_surname()+"\ncon il seguente codice: "+m.Get_cod()+"\n\n");
    m.Write_documentation(writing);
}

void Nurse::accept(WorkerVisitorInterface& visitor) const{
    visitor.visitNurse();
}

bool Nurse::operator==(const Worker& n) const{
    return (dynamic_cast<const Nurse*>(&n)!=nullptr && Get_name()==n.Get_name() && Get_surname()==n.Get_surname() && Get_birth_date()==n.Get_birth_date());
}

bool Nurse::operator!=(const Worker& n) const{
    return !(*this==n);
}
