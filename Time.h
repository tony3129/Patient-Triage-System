#ifndef TIME_H
#define TIME_H
#include "Utils.h"

namespace triage {
	class Time {
		int m_minutes;
	public:
		Time& reset();
		Time(unsigned int min = 0u);
		std::ostream& write(std::ostream& ostr = std::cout) const;
		std::istream& read(std::istream& istr = std::cin);
		operator unsigned int()const;
		Time& operator*= (int val);
		Time& operator-= (const Time& D);
		Time operator-(const Time& T)const;
		int getMins(Time&);
	};
	std::ostream& operator<<(std::ostream& os, const Time& other);
	std::istream& operator>>(std::istream& is, Time& other);
}
#endif