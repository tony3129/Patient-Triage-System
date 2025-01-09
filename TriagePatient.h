#ifndef TRIAGEPATIENT_H
#define TRIAGEPATIENT_H
#include "Patient.h"

#define MAX_SYMPTOM 511


namespace seneca {
    class TriagePatient : public Patient {
        char* m_symptoms;
    public:
        TriagePatient();
        ~TriagePatient();
        virtual char type() const;
        virtual std::ostream& write(std::ostream&)const;
        virtual std::istream& read(std::istream&);
    };
    std::ostream& operator<<(std::ostream& os, const TriagePatient& other);
    std::istream& operator>>(std::istream& is, TriagePatient& other);
}

#endif