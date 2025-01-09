#include "TestPatient.h"

int nextTestTicket =1;

namespace seneca{
    //call Patient constructor and increment nextTestTicket global variable
    TestPatient::TestPatient() : Patient(nextTestTicket){
        nextTestTicket++;
    }

    TestPatient::~TestPatient(){
        //no custom implementation
    }

    char TestPatient::type() const{
        return 'C';
    }

    std::ostream& TestPatient::write(std::ostream& ostr)const{
        if (&ostr == &std::cout)
        {
            ostr << "Contagion TEST" << std::endl;
        }
        Patient::write(ostr);
        return ostr;
    };
    //if istr is not std::cin, set global variable nextTestTicket to current object ticket number +1
    std::istream& TestPatient::read(std::istream& istr){
        Patient::read(istr);
        if (&istr != &std::cin)
        {
            nextTestTicket = this->number() + 1;
        }
        return istr;
    };

    std::ostream& operator<<(std::ostream& os, const TestPatient& other){
        other.write(os);
        return os;
    }

	std::istream& operator>>(std::istream& is, TestPatient& other){
        other.read(is);
        return is;
    }
}