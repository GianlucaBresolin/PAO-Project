#include "mainwindow.h"

#include <QApplication>
#include "file_manager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Container<Patient*> lista_pazienti;
    Container<Worker*> lista_operatori;
    Container<Medical_history*> lista_cartelle_mediche_unsettled;
    Container<Medical_history*> lista_cartelle_mediche_white;
    Container<Medical_history*> lista_cartelle_mediche_green;
    Container<Medical_history*> lista_cartelle_mediche_blue;
    Container<Medical_history*> lista_cartelle_mediche_orange;
    Container<Medical_history*> lista_cartelle_mediche_red;
    try {
        File_manager::Load_file("./SaveData.txt", lista_pazienti, lista_operatori, lista_cartelle_mediche_unsettled, lista_cartelle_mediche_white, lista_cartelle_mediche_green, lista_cartelle_mediche_blue, lista_cartelle_mediche_orange, lista_cartelle_mediche_red);
    } catch (std::runtime_error& e) {
        std::cout<<"An error occured during the loading";
    }
    MainWindow w(lista_pazienti, lista_operatori, lista_cartelle_mediche_unsettled, lista_cartelle_mediche_white, lista_cartelle_mediche_green, lista_cartelle_mediche_blue, lista_cartelle_mediche_orange, lista_cartelle_mediche_red);
    QObject::connect(&w, &MainWindow::destroyed, [&]() {
        lista_pazienti.clear_no_garbage();
        lista_operatori.clear_no_garbage();
        lista_cartelle_mediche_unsettled.clear_no_garbage();
        lista_cartelle_mediche_white.clear_no_garbage();
        lista_cartelle_mediche_green.clear_no_garbage();
        lista_cartelle_mediche_blue.clear_no_garbage();
        lista_cartelle_mediche_orange.clear_no_garbage();
        lista_cartelle_mediche_red.clear_no_garbage();
    });
    w.resize(1024,512);
    w.show();
    return a.exec();
}
