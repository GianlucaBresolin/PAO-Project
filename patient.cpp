#include "patient.h"

Patient::Patient(const std::string& n, const std::string& s, const std::string& d, const std::string& cf): Person::Person(n,s,d), codice_fiscale(cf){}

Patient::Patient(const Patient& p): Person(p), codice_fiscale(p.codice_fiscale), lista_lettere_dimissioni(p.lista_lettere_dimissioni){}

void Patient::Set_codice_fiscale(const std::string& cf){
    codice_fiscale=cf;
}

std::string Patient::Get_codice_fiscale() const{
    return codice_fiscale;
}

void Patient::Aggiungi_lettera_dimissioni(const std::string& lettera){
    if(!lettera.empty()){
        lista_lettere_dimissioni.add(lettera);
    }
}

bool Patient::Empty_lettere_dimissioni() const{
    return lista_lettere_dimissioni.empty();
}

const Container<const std::string>& Patient::Get_lista_lettere_dimissioni() const{
    return lista_lettere_dimissioni;
};

bool Patient::operator==(const Patient& p) const{
    return (Get_name()==p.Get_name() && Get_surname()==p.Get_surname() && Get_birth_date()==p.Get_birth_date() && codice_fiscale==p.codice_fiscale);
}

bool Patient::operator!=(const Patient& p) const{
    return !(*this==p);
}
