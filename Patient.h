#ifndef PATIENT_H
#define PATIENT_H
#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include "IOAble.h"
#include "Ticket.h"

namespace triage {
	class Patient : public IOAble {
		char* m_name;
		int m_OHIP;
		Ticket m_ticket;
	public:
		Patient(int);
		Patient(const Patient&);
		Patient& operator=(const Patient&);
		~Patient();
		virtual char type() const = 0;
		bool operator==(char) const;
		bool operator==(const Patient&) const;
		void setArrivalTime();
		Time time()const;
		int number()const;
		operator bool() const;
		operator char* () const;
		std::ostream& write(std::ostream&)const;
		std::istream& read(std::istream&);
	};
	std::ostream& operator<<(std::ostream& os, const Patient& other);
	std::istream& operator>>(std::istream& is, Patient& other);
}
#endif // !PATIENT_H
