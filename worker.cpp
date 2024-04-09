#include "worker.h"

Worker::Worker(const std::string& n, const std::string& s, const std::string& d): Person::Person(n,s,d){};

Worker::Worker(const Worker& w): Person::Person(w){};

bool Worker::operator==(const Worker& d) const{
    return (Get_name()==d.Get_name() && Get_surname()==d.Get_surname() && Get_birth_date()==d.Get_birth_date());
}

bool Worker::operator!=(const Worker& d) const{
    return !(*this==d);
}
