#include "file_manager.h"
#include "medical_history.h"

void File_manager::Save_to_file(const std::string& nome_file, const Container<Patient*>& lista_pazienti, Container<Worker*>& lista_operatori, Container<Medical_history*>& lista_cartelle_mediche_unsettled, Container<Medical_history*>& lista_cartelle_mediche_white, Container<Medical_history*>& lista_cartelle_mediche_green, Container<Medical_history*>& lista_cartelle_mediche_blue, Container<Medical_history*>& lista_cartelle_mediche_orange, Container<Medical_history*>& lista_cartelle_mediche_red){
    std::ofstream file(nome_file);

    if(file.is_open()){
        file<<"Pazienti:\n";
        Container<Patient*>::const_iterator it_p;
        for(it_p=lista_pazienti.begin(); it_p!=lista_pazienti.end(); it_p++){
            file<<"("<<(*it_p)->Get_name()<<"|"<<(*it_p)->Get_surname()<<"|"<<(*it_p)->Get_birth_date()<<"|"<<(*it_p)->Get_codice_fiscale();
            Container<const std::string>::const_iterator it_l;
            for(it_l=(*it_p)->Get_lista_lettere_dimissioni().begin(); it_l!=(*it_p)->Get_lista_lettere_dimissioni().end(); it_l++){
                file<<"|\n"<<*it_l;
            }
            file<<")\n";
        }
        file<<"END_Pazienti\n";

        file<<"Operatori:\n";
        Container<Worker*>::const_iterator it_o;
        for(it_o=lista_operatori.begin(); it_o!=lista_operatori.end(); it_o++){
            if(dynamic_cast<Nurse*>(*it_o)){
                file<<"(N";
            } else if(dynamic_cast<Primary*>(*it_o)){
                file<<"(P";
            } else{
                file<<"(D";
            }
            file<<"|"<<(*it_o)->Get_name()<<"|"<<(*it_o)->Get_surname()<<"|"<<(*it_o)->Get_birth_date()<<")\n";
        }
        file<<"END_Operatori\n";

        file<<"Cartelle Mediche:\n";
            Save_medical_history_list(lista_cartelle_mediche_unsettled, file);
            Save_medical_history_list(lista_cartelle_mediche_white, file);
            Save_medical_history_list(lista_cartelle_mediche_green, file);
            Save_medical_history_list(lista_cartelle_mediche_blue, file);
            Save_medical_history_list(lista_cartelle_mediche_orange, file);
            Save_medical_history_list(lista_cartelle_mediche_red, file);
        file<<"END_Cartelle_Mediche";

        file.close();
    } else {
        throw std::runtime_error("Error: file not openable");
    }
}

void File_manager::Save_medical_history_list(Container<Medical_history*>& lista_cartelle_mediche, std::ofstream& file){
    Container<Medical_history*>::const_iterator it_c;
    for(it_c=lista_cartelle_mediche.begin(); it_c!=lista_cartelle_mediche.end(); it_c++){
        const Patient* p=(*it_c)->Get_patient();
        file<<"(P("+p->Get_name()<<"|"<<p->Get_surname()<<"|"<<p->Get_birth_date()<<"|"<<p->Get_codice_fiscale()+"),O(";
        if((*it_c)->Get_worker()){
            const Worker* w=(*it_c)->Get_worker();
            if(dynamic_cast<const Nurse*>(w)){
                file<<"N";
            } else if(dynamic_cast<const Primary*>(w)){
                file<<"P";
            } else{
                file<<"D";
            }
            file<<"|"<<w->Get_name()<<"|"<<w->Get_surname()<<"|"<<w->Get_birth_date();
        } else {
            file<<"0";
        }
        file<<"),S("+(*it_c)->Get_string_state()+"),C("+(*it_c)->Get_cod()+"),D("+(*it_c)->Get_Documentation()+"\n))\nFine_Cartella\n";
    }
}

void File_manager::Load_file(const std::string& nome_file, Container<Patient*>& lista_pazienti, Container<Worker*>& lista_operatori, Container<Medical_history*>& lista_cartelle_mediche_unsettled, Container<Medical_history*>& lista_cartelle_mediche_white, Container<Medical_history*>& lista_cartelle_mediche_green, Container<Medical_history*>& lista_cartelle_mediche_blue, Container<Medical_history*>& lista_cartelle_mediche_orange, Container<Medical_history*>& lista_cartelle_mediche_red) {
    std::ifstream file(nome_file);

    if (file.is_open()) {
        if(file.peek()==EOF)
            return;

        std::string line;
        char c;
        std::getline(file, line);
        if (line=="Pazienti:") {
            bool flag_pazienti=true;
            std::string nome, cognome, data_nascita, cod_fiscale, documentazione;
            while(flag_pazienti){
                if(file.peek()=='E'){
                    std::getline(file, line);
                    if(line=="END_Pazienti")
                        flag_pazienti=false;
                    else
                        throw std::runtime_error("Error: a problem occured during the loading.");
                }else{
                    nome.clear();
                    cognome.clear();
                    data_nascita.clear();
                    cod_fiscale.clear();
                    documentazione.clear();
                    file.get(c);
                    if(c=='('){
                        file.get(c);
                        while(c!='|' && c!=')'){
                            nome+=c;
                            file.get(c);
                        }
                        if(c!='|' && c!=')'){
                            throw std::runtime_error("Error: a problem occured during the loading.");
                        }
                        file.get(c);
                        while(c!='|' && c!=')'){
                            cognome+=c;
                            file.get(c);
                        }
                        if(c!='|' && c!=')'){
                            throw std::runtime_error("Error: a problem occured during the loading.");
                        }
                        file.get(c);
                        while(c!='|' && c!=')'){
                            data_nascita+=c;
                            file.get(c);
                        }
                        if(c!='|' && c!=')'){
                            throw std::runtime_error("Error: a problem occured during the loading.");
                        }
                        file.get(c);
                        while(c!='|' && c!=')'){
                            cod_fiscale+=c;
                            file.get(c);
                        }
                        if(c!='|' && c!=')'){
                            throw std::runtime_error("Error: a problem occured during the loading.");
                        }
                    } else {
                        throw std::runtime_error("Error: a problem occured during the loading.");
                    }
                    Patient* p=new Patient(nome, cognome, data_nascita, cod_fiscale);
                    lista_pazienti.add(p);

                    if(c!=')'){ //ci sono lettere di dimissioni
                        if(c=='|'){
                            std::getline(file, line);
                            while(line!=")"){
                                documentazione.clear();
                                line.clear();
                                while(line!="|" && line!=")"){
                                    std::getline(file, line);
                                    if(line!="|" && line!=")")
                                        documentazione+=line+"\n";
                                }
                                p->Aggiungi_lettera_dimissioni(documentazione);
                            }
                        } else {
                            throw std::runtime_error("Error: a problem occured during the loading.");
                        }
                    } else
                        file.get(c);
                }
            }
        } else {
            throw std::runtime_error("Error: a problem occured during the loading.");
        }

        std::getline(file, line);
        if (line=="Operatori:") {
            bool flag_operatori=true;
            std::string nome, cognome, data_nascita;
            bool n, d, p;
            while(flag_operatori){
                if(file.peek()=='E'){
                    std::getline(file, line);
                    if(line=="END_Operatori")
                        flag_operatori=false;
                    else
                        throw std::runtime_error("Error: a problem occured during the loading.");
                } else {
                    nome.clear();
                    cognome.clear();
                    data_nascita.clear();
                    n=false;
                    d=false;
                    p=false;
                    char c;
                    file.get(c);
                    if(c=='('){
                        file.get(c);
                        if(c=='N')
                            n=true;
                        else if(c=='D')
                            d=true;
                        else if(c=='P')
                            p=true;
                        else
                            throw std::runtime_error("Error: a problem occured during the loading.");
                        file.get(c);
                        if(c=='|'){
                                file.get(c);
                                while(c!='|' && c!=')'){
                                    nome+=c;
                                    file.get(c);
                                }
                                if(c!='|' && c!=')'){
                                    throw std::runtime_error("Error: a problem occured during the loading.");
                                }
                                file.get(c);
                                while(c!='|' && c!=')'){
                                    cognome+=c;
                                    file.get(c);
                                }
                                if(c!='|' && c!=')'){
                                    throw std::runtime_error("Error: a problem occured during the loading.");
                                }
                                file.get(c);
                                while(c!='|' && c!=')'){
                                    data_nascita+=c;
                                    file.get(c);
                                }
                                if(c!='|' && c!=')'){
                                    throw std::runtime_error("Error: a problem occured during the loading.");
                                }
                            } else {
                                throw std::runtime_error("Error: a problem occured during the loading.");
                            }
                        Worker* w;
                        if(n)
                            w=new Nurse(nome, cognome, data_nascita);
                        else if(d)
                            w=new Doctor(nome, cognome, data_nascita);
                        else if(p)
                            w=new Primary(nome, cognome, data_nascita);
                        else
                            throw std::runtime_error("Error: a problem occured during the loading.");
                        lista_operatori.add(w);
                    } else {
                        throw std::runtime_error("Error: a problem occured during the loading.");
                    }
                    file.get(c);
                }
            }
        } else {
            throw std::runtime_error("Error: a problem occured during the loading.");
        }

        std::getline(file, line);
        if (line=="Cartelle Mediche:") {
                bool flag=true;
                while(flag){
                    Patient* paziente;
                    Worker* w;
                    std::string stato, codice, documentazione, line;

                    char c;
                    file.get(c);
                    if(c=='('){
                        file.get(c);
                        if(c=='P'){
                            file.get(c);
                            if(c=='('){
                                std::string nome, cognome, data_nascita, cod_fiscale;
                                file.get(c);
                                while(c!='|' && c!=')'){
                                    nome+=c;
                                    file.get(c);
                                }
                                if(c!='|' && c!=')'){
                                    throw std::runtime_error("Error: a problem occured during the loading.");
                                }
                                file.get(c);
                                while(c!='|' && c!=')'){
                                    cognome+=c;
                                    file.get(c);
                                }
                                if(c!='|' && c!=')'){
                                    throw std::runtime_error("Error: a problem occured during the loading.");
                                }
                                file.get(c);
                                while(c!='|' && c!=')'){
                                    data_nascita+=c;
                                    file.get(c);
                                }
                                if(c!='|' && c!=')'){
                                    throw std::runtime_error("Error: a problem occured during the loading.");
                                }
                                file.get(c);
                                while(c!='|' && c!=')'){
                                    cod_fiscale+=c;
                                    file.get(c);
                                }
                                if(c!='|' && c!=')'){
                                    throw std::runtime_error("Error: a problem occured during the loading.");
                                }
                                Patient* p=new Patient(nome, cognome, data_nascita, cod_fiscale);
                                if(lista_pazienti.search(p))
                                    paziente=*lista_pazienti.search(p);
                                else
                                    throw std::runtime_error("Error: a problem occured during the loading.");
                                file.get(c);
                                if(c==','){
                                    file.get(c);
                                    if(c=='O'){
                                        file.get(c);
                                        if(c=='('){
                                            file.get(c);
                                            if(c=='0'){
                                                w=nullptr;
                                                file.get(c);
                                                if(c!=')')
                                                   throw std::runtime_error("Error: a problem occured during the loading.");
                                            } else {
                                                std::string nome_w, cognome_w, data_nascita_w;
                                                bool n=false, d=false, p=false;
                                                    if(c=='N')
                                                        n=true;
                                                    else if(c=='D')
                                                        d=true;
                                                    else if(c=='P')
                                                        p=true;
                                                    else
                                                        throw std::runtime_error("Error: a problem occured during the loading.");
                                                    file.get(c);
                                                    if(c=='|'){
                                                            file.get(c);
                                                            while(c!='|' && c!=')'){
                                                                nome_w+=c;
                                                                file.get(c);
                                                            }
                                                            if(c!='|' && c!=')'){
                                                                throw std::runtime_error("Error: a problem occured during the loading.");
                                                            }
                                                            file.get(c);
                                                            while(c!='|' && c!=')'){
                                                                cognome_w+=c;
                                                                file.get(c);
                                                            }
                                                            if(c!='|' && c!=')'){
                                                                throw std::runtime_error("Error: a problem occured during the loading.");
                                                            }
                                                            file.get(c);
                                                            while(c!='|' && c!=')'){
                                                                data_nascita_w+=c;
                                                                file.get(c);
                                                            }
                                                            if(c!='|' && c!=')'){
                                                                throw std::runtime_error("Error: a problem occured during the loading.");
                                                            }
                                                        } else {
                                                            throw std::runtime_error("Error: a problem occured during the loading.");
                                                        }
                                                    if(n)
                                                        w=new Nurse(nome_w, cognome_w, data_nascita_w);
                                                    else if(d)
                                                        w=new Doctor(nome_w, cognome_w, data_nascita_w);
                                                    else if(p)
                                                        w=new Primary(nome_w, cognome_w, data_nascita_w);
                                                    else
                                                        throw std::runtime_error("Error: a problem occured during the loading.");
                                                }
                                            }
                                            file.get(c);
                                            if(c==','){
                                                file.get(c);
                                                if(c=='S'){
                                                    file.get(c);
                                                    if(c=='('){
                                                        file.get(c);
                                                        while(c!='|' && c!=')'){
                                                            stato+=c;
                                                            file.get(c);
                                                        }
                                                        if(c!='|' && c!=')'){
                                                            throw std::runtime_error("Error: a problem occured during the loading.");
                                                        }
                                                        file.get(c);
                                                        if(c==','){
                                                            file.get(c);
                                                            if(c=='C'){
                                                                file.get(c);
                                                                if(c=='('){
                                                                    file.get(c);
                                                                    while(c!='|' && c!=')'){
                                                                        codice+=c;
                                                                        file.get(c);
                                                                    }
                                                                    if(c!='|' && c!=')'){
                                                                        throw std::runtime_error("Error: a problem occured during the loading.");
                                                                    }
                                                                    file.get(c);
                                                                    if(c==','){
                                                                        file.get(c);
                                                                        if(c=='D'){
                                                                            file.get(c);
                                                                            if(c=='('){
                                                                                std::getline(file, line);
                                                                                while(line!="))"){
                                                                                    documentazione+=line+"\n";
                                                                                    std::getline(file, line);
                                                                                }
                                                                            } else {
                                                                                throw std::runtime_error("Error: a problem occured during the loading.");
                                                                            }
                                                                        } else {
                                                                            throw std::runtime_error("Error: a problem occured during the loading.");
                                                                        }
                                                                    } else {
                                                                        throw std::runtime_error("Error: a problem occured during the loading.");
                                                                    }
                                                                } else {
                                                                    throw std::runtime_error("Error: a problem occured during the loading.");
                                                                }
                                                            } else {
                                                                throw std::runtime_error("Error: a problem occured during the loading.");
                                                            }
                                                        } else {
                                                            throw std::runtime_error("Error: a problem occured during the loading.");
                                                        }
                                                    } else {
                                                        throw std::runtime_error("Error: a problem occured during the loading.");
                                                    }
                                                } else {
                                                    throw std::runtime_error("Error: a problem occured during the loading.");
                                                }
                                            } else {
                                                throw std::runtime_error("Error: a problem occured during the loading.");
                                            }
                                        } else {
                                            throw std::runtime_error("Error: a problem occured during the loading.");
                                        }
                                    } else {
                                        throw std::runtime_error("Error: a problem occured during the loading.");
                                    }
                                } else {
                                    throw std::runtime_error("Error: a problem occured during the loading.");
                                }
                            } else {
                                throw std::runtime_error("Error: a problem occured during the loading.");
                            }
                        } else {
                            throw std::runtime_error("Error: a problem occured during the loading.");
                        }

                    Medical_history* m=new Medical_history(paziente);
                    m->Set_worker(w);
                    m->Set_string_state(stato);
                    m->Set_cod(codice);
                    m->Set_documentation(documentazione);

                    if(m->Get_cod()=="White"){
                        lista_cartelle_mediche_white.add(m);
                    } else if(m->Get_cod()=="Green"){
                        lista_cartelle_mediche_green.add(m);
                    } else if(m->Get_cod()=="Blue"){
                        lista_cartelle_mediche_blue.add(m);
                    } else if(m->Get_cod()=="Orange"){
                        lista_cartelle_mediche_orange.add(m);
                    } else if(m->Get_cod()=="Red"){
                        lista_cartelle_mediche_red.add(m);
                    } else {
                        lista_cartelle_mediche_unsettled.add(m);
                    }
                    std::getline(file, line);
                    if(file.peek()=='E'){
                        std::getline(file, line);
                        flag=false;
                    }
                }
            } else {
                throw std::runtime_error("Error: a problem occured during the loading.");
            }
            file.close();
    } else {
        throw std::runtime_error("Error: Impossibile aprire il file.");
    }
}
