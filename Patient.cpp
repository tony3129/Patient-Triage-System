#include "Patient.h"

namespace triage {
	//construct m_ticket and set member variables to safe state
	Patient::Patient(int number) : m_ticket(number) {
		m_name = nullptr;
		m_OHIP = -1;
	};

	//Wanted to use operator= to save on code, but the delete[] seemed to be crashing my program
	//operator= needs to have delete[], so decided to implement copy constructor
	Patient::Patient(const Patient& other) : m_ticket(other.m_ticket.number()) {
		int length = 0;
		//check if other is in valid state
		if (other.m_name != nullptr && other.m_OHIP != -1) {
			//if m_name is over 50 chars, only copy the first 50 chars
			length = strlen(other.m_name);
			if (length > 50) {
				length = 50;
			}
			m_name = new char[length + 1];
			strcpy(m_name, other.m_name);
			m_OHIP = other.m_OHIP;
			m_ticket = other.m_ticket;
		}
		else {
			m_name = nullptr;
			m_OHIP = -1;
		}
	}

	Patient& Patient::operator=(const Patient& other) {
		int length = 0;
		//check for self assignment
		if (this != &other)
		{
			//check if other is in valid state
			if (other.m_name != nullptr && other.m_OHIP != -1) {
				//if m_name is over 50 chars, only copy the first 50 chars
				length = strlen(other.m_name);
				if (length > 50)
				{
					length = 50;
				}
				delete[] m_name;
				m_name = nullptr;
				m_name = new char[length + 1];
				strcpy(m_name, other.m_name);
				m_OHIP = other.m_OHIP;
				m_ticket = other.m_ticket;
			}
		}
		return *this;
	}

	Patient::~Patient() {
		delete[] m_name;
		m_name = nullptr;
	}

	bool Patient::operator==(char compChar) const {
		return type() == compChar;
	};

	bool Patient::operator==(const Patient& other) const {
		return (this->type() == other.type());
	};

	void Patient::setArrivalTime() {
		m_ticket.resetTime();
	};

	Time Patient::time() const {
		return m_ticket.time();
	};

	int Patient::number() const {
		return m_ticket.number();
	};

	Patient::operator bool() const {
		return (m_name != nullptr || m_OHIP != -1);
	};

	Patient::operator char* () const {
		return m_name;
	};

	std::ostream& Patient::write(std::ostream& os) const {
		//check if m_name or m_OHIP are in invalid states
		if (m_name == nullptr || m_OHIP == -1) {
			os << "Invalid Patient Record" << std::endl;
		}
		else {
			//if std::cout, output this format
			if (&os == &std::cout) {
				m_ticket.write(os);
				os << std::endl;
				os << m_name << ", OHIP: " << m_OHIP << std::endl;
			}
			//if std::clog, output this format
			else if (&os == &std::clog) {
				os.setf(std::ios::left);
				os.width(53);
				os.fill('.');
				os << m_name << m_OHIP;
				os.unsetf(std::ios::left);
				os.width(5);
				os.fill(' ');
				os << m_ticket.number();
				os << " " << m_ticket.time();
			}
			//if neither std::clog or std::cout assume output to file appropriate format
			else {
				os << type() << "," << m_name << "," << m_OHIP << ",";
				m_ticket.write(os);
			}
		}
		return os;
	};

	std::istream& Patient::read(std::istream& is) {
		char tempName[50 + 1];
		bool validInput = false;
		//if std::cin allow input proper format
		if (&is == &std::cin)
		{
			std::cout << "Name: ";
			is.get(tempName, 51, '\n');
			delete[] m_name;
			m_name = nullptr;
			m_name = new char[strlen(tempName) + 1];
			strcpy(m_name, tempName);
			std::cout << "OHIP: ";
			//ensure input is correct format (taken from Menu.cpp)
			do
			{
				is >> m_OHIP;
				//check if variable input to m_OHIP is of proper type, in proper format, and within range
				//if improper data type is input to m_OHIP, clear state, and clear buffer
				if (is.fail())
				{
					std::cout << "Bad integer value, try again: ";
					is.clear();
				}
				else if (m_OHIP <= 100000000 || m_OHIP >= 999999999)
				{
					std::cout << "Invalid value enterd, retry[100000000 <= value <= 999999999]: ";
				}
				else
				{
					validInput = true;
				}
			} while (validInput == false);
			is.ignore(2000, '\n');
		}
		//if not std::cin accept input in format appropriate for file
		else
		{
			is.get(tempName, 51, ',');
			delete[] m_name;
			m_name = nullptr;
			m_name = new char[strlen(tempName) + 1];
			strcpy(m_name, tempName);
			is.ignore(2000, ',');
			is >> m_OHIP;
			is.ignore(2000, ',');
			m_ticket.read(is);
		}
		return is;
	};
	//required to call write function otherwise output is in 1 and 0
	std::ostream& operator<<(std::ostream& os, const Patient& other) {
		other.write(os);
		return os;
	}
	//required to call read function otherwise output is in 1 and 0
	std::istream& operator>>(std::istream& is, Patient& other) {
		other.read(is);
		return is;
	}
}