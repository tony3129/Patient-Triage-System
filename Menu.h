#ifndef MENU_H
#define MENU_H
#include "Utils.h"

namespace seneca {
	class Menu {
		char* m_text;
		int m_menuOptions;
		int m_numTabs;
		Menu& operator=(const Menu&);
	public:
		Menu(const char* menuContent, int numberOfTabs = 0);
		~Menu();
		std::ostream& display(std::ostream& ostr = std::cout) const;
		int& operator>>(int& Selection);
	};
}

#endif // !MENU_H
