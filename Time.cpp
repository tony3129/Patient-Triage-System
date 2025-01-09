#include "Time.h"
#include "Utils.h"

namespace seneca {
	Time& Time::reset() {
		m_minutes = U.getTime();
		return *this;
	}

	Time::Time(unsigned int min) {
		m_minutes = min;
	}

	//format output
	std::ostream& Time::write(std::ostream& ostr) const {
		ostr.fill('0');
		ostr.width(2);
		ostr << U.convertHrs(m_minutes) << ":";
		ostr.width(2);
		ostr << U.convertMins(m_minutes);
		return ostr;
	}

	std::istream& Time::read(std::istream& istr) {
		int hrs, mins;
		//store first int into hrs
		istr >> hrs;
		//check if the next variable in the istream is a ':'
		if (istr.peek() == ':')
		{
			//if colon ignore and input next variable into mins
			istr.ignore();
			istr >> mins;
			if (hrs >= 0 && mins >= 0)
			{
				m_minutes = hrs * 60 + mins;
			}
		}
		else
		{
			istr.setstate(std::ios::failbit);
		}
		return istr;
	}

	Time::operator unsigned int()const {
		return m_minutes;
	}

	Time& Time::operator*= (int val) {
		m_minutes *= val;
		return *this;
	}

	Time& Time::operator-=(const Time& D) {
		this->m_minutes -= D.m_minutes;
		//if D.m_minutes is larger, this->m_minutues will be negative, so add 1440mins(24hrs) to prevent that
		if (this->m_minutes < 0)
		{
			this->m_minutes += 1440;
		}
		return *this;
	}
	Time Time::operator-(const Time& T)const {
		Time temp;
		temp.m_minutes = this->m_minutes;
		temp -= T;
		return temp;
	}

	std::ostream& operator<<(std::ostream& os, const Time& other) {
		other.write(os);
		return os;
	}
	std::istream& operator>>(std::istream& is, Time& other) {
		other.read(is);
		return is;
	}
}