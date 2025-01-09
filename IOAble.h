//class to handle input/output
#ifndef IOABLE_H
#define IOABLE_H
#include <iostream>

namespace seneca {
	class IOAble {
	public:
		virtual std::ostream& write(std::ostream&) const = 0;
		virtual std::istream& read(std::istream&) = 0;
		virtual ~IOAble();
	};

	std::ostream& operator <<(std::ostream&, IOAble&);
	std::istream& operator >>(std::istream&, IOAble&);
}
#endif