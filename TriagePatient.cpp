#include "TriagePatient.h"

int nextTriageTicket = 1;

namespace seneca {
    TriagePatient::TriagePatient() : Patient(nextTriageTicket) {
        m_symptoms = nullptr;
        nextTriageTicket++;
    }

    TriagePatient::~TriagePatient() {
        delete[] m_symptoms;
        m_symptoms = nullptr;
    }
    char TriagePatient::type() const {
        return 'T';
    }
    std::ostream& TriagePatient::write(std::ostream& ostr)const {
        if (&ostr == &std::cout)
        {
            ostr << "TRIAGE" << std::endl;
            Patient::write(ostr);
            ostr << "Symptoms: " << m_symptoms << std::endl;
        }
        else if (&ostr == &std::clog)
        {
            Patient::write(ostr);
        }
        else {
            Patient::write(ostr);
            ostr << "," << m_symptoms;
        }
        return ostr;
    }
    std::istream& TriagePatient::read(std::istream& istr) {
        char localSymptom[MAX_SYMPTOM + 1];
        delete[] m_symptoms;
        m_symptoms = nullptr;
        Patient::read(istr);

        if (&istr == &std::cin)
        {
            std::cout << "Symptoms: ";
            istr.get(localSymptom, MAX_SYMPTOM, '\n');
            m_symptoms = new char[strlen(localSymptom) + 1];
            strcpy(m_symptoms, localSymptom);
            istr.ignore(2000, '\n');
        }
        else {
            istr.ignore(2000, ',');
            istr.get(localSymptom, MAX_SYMPTOM, '\n');
            m_symptoms = new char[strlen(localSymptom) + 1];
            strcpy(m_symptoms, localSymptom);
            nextTriageTicket = Patient::number() + 1;
        }

        if (istr.fail()) {
            delete[] m_symptoms;
            m_symptoms = nullptr;
            return istr;
        }
        return istr;
    }
    std::ostream& operator<<(std::ostream& os, const TriagePatient& other) {
        other.write(os);
        return os;
    }
    std::istream& operator>>(std::istream& is, TriagePatient& other) {
        other.read(is);
        return is;
    }
}