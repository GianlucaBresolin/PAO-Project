#ifndef PATIENT_H
#define PATIENT_H

#include "person.h"
#include "container_template.h"

class Patient:public Person{
    
    private:

    std::string codice_fiscale;
    Container<const std::string> lista_lettere_dimissioni;

    public:

    Patient(const std::string& ="...", const std::string& ="...", const std::string& ="../../..", const std::string& ="...");
    Patient(const Patient&);

    void Set_codice_fiscale(const std::string&);
    std::string Get_codice_fiscale() const;

    void Aggiungi_lettera_dimissioni(const std::string&);
    bool Empty_lettere_dimissioni() const;
    const Container<const std::string>& Get_lista_lettere_dimissioni() const;

    bool operator==(const Patient&) const;
    bool operator!=(const Patient&) const;

    ~Patient() override{};
};

#endif
