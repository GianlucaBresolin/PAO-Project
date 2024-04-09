QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    acceptance_window.cpp \
    creation_medical_history_window.cpp \
    creation_operator_window.cpp \
    creation_patient_window.cpp \
    discharges_letter_panel.cpp \
    discharges_letter_view.cpp \
    discharges_letters_list.cpp \
    edit_operator_window.cpp \
    edit_patient_window.cpp \
    error_window.cpp \
    file_manager.cpp \
    main.cpp \
    mainwindow.cpp \
    operator_panel.cpp \
    operators_list.cpp \
    operators_list_window.cpp \
    option_list.cpp \
    patient_panel.cpp \
    patients_list.cpp \
    patients_list_window.cpp \
    medical_history.cpp \
    person.cpp \
    patient.cpp \
    search_patient_window.cpp \
    visit_window.cpp \
    worker.cpp \
    nurse.cpp \
    doctor.cpp \
    primary.cpp \
    workerinfovisitor.cpp \
    medical_history_list.cpp \
    medical_history_list_window.cpp \
    medical_history_panel.cpp

HEADERS += \
    acceptance_window.h \
    container_template.h \
    creation_medical_history_window.h \
    creation_operator_window.h \
    creation_patient_window.h \
    discharges_letter_panel.h \
    discharges_letter_view.h \
    discharges_letters_list.h \
    edit_operator_window.h \
    edit_patient_window.h \
    error_window.h \
    file_manager.h \
    mainwindow.h \
    operator_panel.h \
    operators_list.h \
    operators_list_window.h \
    option_list.h \
    patient_panel.h \
    patients_list.h \
    medical_history.h \
    patients_list_window.h \
    person.h \
    patient.h \
    patients_state.h \
    search_patient_window.h \
    visit_window.h \
    worker.h \
    nurse.h \
    doctor.h \
    primary.h \
    medical_code.h \
    workerinfovisitor.h \
    workervisitorinterface.h \
    medical_history_list.h \
    medical_history_list_window.h \
    medical_history_panel.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
