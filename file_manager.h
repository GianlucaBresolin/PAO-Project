#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <iostream>
#include <fstream>
#include "container_template.h"
#include "patient.h"
#include "primary.h"
#include "nurse.h"

class File_manager{
    public:
        File_manager(){};
        static void Save_to_file(const std::string& nome_file, const Container<Patient*>& lista_pazienti, Container<Worker*>& lista_operatori,  Container<Medical_history*>& lista_cartelle_mediche_unsettled, Container<Medical_history*>& lista_cartelle_mediche_white, Container<Medical_history*>& lista_cartelle_mediche_green, Container<Medical_history*>& lista_cartelle_mediche_blue, Container<Medical_history*>& lista_cartelle_mediche_orange, Container<Medical_history*>& lista_cartelle_mediche_red);
        static void Save_medical_history_list(Container<Medical_history*>& lista_cartelle_mediche, std::ofstream& file);
        static void Load_file(const std::string& nome_file, Container<Patient*>& lista_pazienti, Container<Worker*>& lista_operatori, Container<Medical_history*>& lista_cartelle_mediche_unsettled, Container<Medical_history*>& lista_cartelle_mediche_white, Container<Medical_history*>& lista_cartelle_mediche_green, Container<Medical_history*>& lista_cartelle_mediche_blue, Container<Medical_history*>& lista_cartelle_mediche_orange, Container<Medical_history*>& lista_cartelle_mediche_red);
};

#endif
