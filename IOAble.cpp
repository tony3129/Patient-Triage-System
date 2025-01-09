//Input output management
#include "IOAble.h"

namespace seneca {

	IOAble::~IOAble() {
		//do nothing
	};

	std::ostream& operator <<(std::ostream& os, IOAble& other) {
		other.write(os);
		return os;
	};
	std::istream& operator >>(std::istream& is, IOAble& other) {
		other.read(is);
		return is;
	};
}