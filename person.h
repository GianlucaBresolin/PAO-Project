#ifndef PERSONA_H
#define PERSONA_H
#include <string>

class Person{
    
    private:

        std::string name;
        std::string surname;
        std::string birth_date;

    public:

        Person(const std::string& ="...", const std::string& ="...", const std::string& ="../../..");   
        Person(const Person&);

        void Set_name(const std::string&);
        std::string Get_name() const;
        
        void Set_surname(const std::string&);
        std::string Get_surname() const;
        
        void Set_birth_date(const std::string&);
        std::string Get_birth_date() const;

        bool operator==(const Person&) const;
        bool operator!=(const Person&) const;

        virtual ~Person(){};

};

#endif