#ifndef PRETRIAGE_H
#define PRETRIAGE_H
#define MAX_PATIENTS 100
#define _CRT_SECURE_NO_WARNINGS
#include "Time.h"
#include "TestPatient.h"
#include "TriagePatient.h"
#include "Menu.h"
#include <fstream>

namespace seneca{
    class PreTriage{
        Time m_contaigenAvgTime;
        Time m_triageAvgTime;
        Patient* m_patientLineup[MAX_PATIENTS];
        char* m_fileName;
        int m_numPatients;

    public:
        PreTriage(const char*);
        ~PreTriage();
        void getWaitTime(const Patient&);
        void setAverageWaitTime(const Patient&);
        int indexOfFirstInLine(char) const;
        void load();
        void save();
        void registerPatient();
        void admit();
        void lineup();
        void run();
    };
}
#endif