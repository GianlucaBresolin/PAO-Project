#include "medical_history.h"

Medical_history::Medical_history(const Patient* p): patient(p), worker(nullptr), state(Patients_state::Pre_acceptance), cod(Medical_code::Unsettled){
    documentation="\nDocumentazione del paziente\n\tNome: " + p->Get_name() + "\n\tCognome: " + p->Get_surname() + "\n\tData di nascita: " + p->Get_birth_date() + "\n\tCodice Fiscale: " + p->Get_codice_fiscale() + "\n\n";
};

Medical_history::Medical_history(const Medical_history& m): patient(m.patient), worker(m.worker), state(m.state), cod(m.cod), documentation(m.documentation){};

Patients_state Medical_history::Get_state() const{
    return state;
}

const std::string Medical_history::Get_string_state() const{
    switch (state){
        case Patients_state::Pre_acceptance:
            return "Pre Acceptance";
        case Patients_state::Acceptance:
            return "Acceptance";
        case Patients_state::Visit:
            return "Visit";
        case Patients_state::End_visit:
            return "End Visit";
        case Patients_state::Discharge:
            return "Discharge";
        case Patients_state::End:
            return "End";
        default:
            return "Error_state";
    }
}

void Medical_history::Change_State(){
    switch (state){
        case Patients_state::Pre_acceptance:
            state=Patients_state::Acceptance;
            break;
        case Patients_state::Acceptance:
            state=Patients_state::Visit;
            break;
        case Patients_state::Visit:
            state=Patients_state::End_visit;
            break;
        case Patients_state::End_visit:
            state=Patients_state::Discharge;
        break;
        case Patients_state::Discharge:
            state=Patients_state::End;
            break;
        case Patients_state::End:
            break;
    }
}

void Medical_history::Set_string_state(const std::string& stato){
    if(stato=="Pre Acceptance")
        state=Patients_state::Pre_acceptance;
    else if(stato=="Acceptance")
        state=Patients_state::Acceptance;
    else if(stato=="Visit")
        state=Patients_state::Visit;
    else if(stato=="End Visit")
        state=Patients_state::End_visit;
    else if(stato=="Discharge")
        state=Patients_state::Discharge;
    else
        state=Patients_state::End;
}

const Patient* Medical_history::Get_patient() const{
    return patient;
}

void Medical_history::Set_worker(const Worker* w){
    worker=w;
}

void Medical_history::Do_work(){
    if(!(worker==nullptr)){
        if(dynamic_cast<const Primary*>(worker) && state==Patients_state::Visit)
            dynamic_cast<const Primary*>(worker)->Doctor::work(*this);
        else
            worker->work(*this);
    }
}

const Worker* Medical_history::Get_worker() const{
    return worker;
}

const Worker* Medical_history::remove_worker(){
    const Worker* tmp=worker;
    worker=nullptr;
    return tmp;
}

void Medical_history::Set_cod(const std::string& c){
    if (c=="White" || c=="white")
            cod=Medical_code::White;
    else if(c=="Green" || c=="green")
            cod=Medical_code::Green;
    else if(c=="Blue" || c=="blue")
            cod=Medical_code::Blue;
    else if(c=="Orange" || c=="orange")
            cod=Medical_code::Orange;
    else if(c=="Red" || c=="red")
            cod=Medical_code::Red;
    else 
            cod=Medical_code::Unsettled;
}

const std::string Medical_history::Get_cod() const{
    switch (cod){
        case Medical_code::White: return "White";
        case Medical_code::Green: return "Green";
        case Medical_code::Blue: return "Blue";
        case Medical_code::Orange: return "Orange";
        case Medical_code::Red: return "Red";
        default: return "Unsettled";
    }
}

Medical_code Medical_history::Get_medical_code() const{
    return cod;
};

void Medical_history::Write_documentation(const std::string& s){
    documentation+=s;
}

void Medical_history::Set_documentation(const std::string& documentazione){
    documentation.clear();
    documentation=documentazione;
}

const std::string& Medical_history::Get_Documentation() const{
    return documentation;
}

void Medical_history::End_medical_history(){
    if(state==Patients_state::Discharge)
        Change_State();
}

void Medical_history::Delete_medical_history(){
    if(state==Patients_state::End)
        this->~Medical_history();
}

bool Medical_history::operator==(const Medical_history& m) const{
    return (*patient==*(m.patient));
}

bool Medical_history::operator!=(const Medical_history& m) const{
    return !(*this==m);
}
