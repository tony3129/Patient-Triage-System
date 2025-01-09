#ifndef TESTPATIENT_H
#define TESTPATIENT_H
#include "Patient.h"

namespace triage{
    class TestPatient : public Patient {
        //no member variables
    public:
        TestPatient();
        ~TestPatient();
        virtual char type() const;
        virtual std::ostream& write(std::ostream&)const;
        virtual std::istream& read(std::istream&);
    };

    std::ostream& operator<<(std::ostream& os, const TestPatient& other);
	std::istream& operator>>(std::istream& is, TestPatient& other);
}

#endif