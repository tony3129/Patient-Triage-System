#include "Menu.h"
#include "Time.h"
#include "Utils.h"

namespace triage {
	Menu::Menu(const char* menuContent, int numberOfTabs) {
		//check if menuContent is valid, if it is copy it, if not set member variables to safe state
		if (menuContent != nullptr)
		{
			m_text = new char[strlen(menuContent) + 1];
			strcpy(m_text, menuContent);
			m_numTabs = numberOfTabs;
			m_menuOptions = 0;
			for (int i = 0; m_text[i] != '\0'; i++)
			{
				if (m_text[i] == '\n' || m_text[i + 1] == '\0')
				{
					m_menuOptions++;
				}
			}
		}
		else
		{
			m_menuOptions = 0;
			m_text = nullptr;
			m_numTabs = 0;
		}
	}

	Menu::~Menu() {
		delete[] m_text;
		m_text = nullptr;
	}

	std::ostream& Menu::display(std::ostream& ostr) const {
		//nextOption keeps track of string indexes delimited by \n
		int nextOption = 0;
		//new variable to hold number of needed spaces
		char* spaces;
		spaces = new char[m_numTabs * 3 + 1];
		//set spaces to a empty string
		strcpy(spaces, "");
		for (int i = 0; i < m_numTabs; i++)
		{
			//add 3 spaces per tab to spaces string
			strcat(spaces, "   ");
		}
		//Format options correctly
		for (int i = 0; i < m_menuOptions; i++)
		{
			ostr << spaces;
			//prints string until \n, then from that point +1 it'll print the next string, etc.
			while (m_text[nextOption] != '\n' && m_text[nextOption] != '\0') {
				ostr << m_text[nextOption];
				nextOption++;
			}
			nextOption++;
			ostr << std::endl;
		}
		ostr << spaces << 0 << "- Exit" << std::endl;
		ostr << spaces << "> ";
		//deallocate spaces 
		delete[] spaces;
		spaces = nullptr;

		return ostr;
	}
	int& Menu::operator>>(int& Selection) {
		display(std::cout);
		bool validInput = false;
		char spaceCheck;
		do
		{
			std::cin >> Selection;
			std::cin.get(spaceCheck);
			//check if variable input to Selection is of proper type, in proper format, and within range
			//if improper data type is input to Selection, clear state, and clear buffer
			if (std::cin.fail())
			{
				std::cout << "Bad integer value, try again: ";
				std::cin.clear();
				std::cin.ignore(2000, '\n');
			}
			else if (spaceCheck == ' ')
			{
				std::cout << "Only enter an integer, try again: ";
			}
			else if (Selection < 0 || Selection >= m_menuOptions)
			{
				std::cout << "Invalid value enterd, retry[0 <= value <= " << m_menuOptions - 1 << "]: ";
			}
			else
			{
				validInput = true;
			}
		} while (validInput == false);
		return Selection;
	}

}
