#include "person.h"

Person::Person(const std::string& n, const std::string& s, const std::string& b): name(n), surname(s), birth_date(b){}

Person::Person(const Person& p): name(p.name), surname(p.surname), birth_date(p.birth_date){}

void Person::Set_name(const std::string& n){
    name=n;
}

std::string Person::Get_name() const{
    return name;
}
        
void Person::Set_surname(const std::string& s){
    surname=s;
}

std::string Person::Get_surname() const{
    return surname;
}

void Person::Set_birth_date(const std::string& b){
    birth_date=b;
}
        
std::string Person::Get_birth_date() const{
    return birth_date;
}

bool Person::operator==(const Person& p) const{
    return (name==p.name && surname==p.surname && birth_date==p.birth_date);
}

bool Person::operator!=(const Person& p) const{
    return !(*this==p);
}