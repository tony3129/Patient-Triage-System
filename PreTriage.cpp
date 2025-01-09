#include "PreTriage.h"

namespace triage{
    PreTriage::PreTriage(const char* fileName) : m_contaigenAvgTime(15), m_triageAvgTime(5){
        if(fileName!=nullptr){
            //initialize all member variables
            m_fileName = new char[strlen(fileName) +1];
            strcpy(m_fileName, fileName);
            m_numPatients =0;
            for (int i = 0; i < MAX_PATIENTS; i++)
            {
                m_patientLineup[i] = nullptr;
            }
            //load file
            load();
        }
        //initialize all member variables
        else
        {
            m_fileName = nullptr;
            m_numPatients = 0;
            for (int i = 0; i < MAX_PATIENTS; i++)
            {
                m_patientLineup[i] = nullptr;
            }
        }
    }
    PreTriage::~PreTriage(){
        //save to file
        save();
        //delete each patientLineup
        //contains address dynamically allocated to localPatient in load()
        for (int i = 0; i < m_numPatients; i++)
        {
            delete m_patientLineup[i];
            m_patientLineup[i] = nullptr;
        }
        delete[] m_fileName;
        m_fileName = nullptr;
    }
    void PreTriage::getWaitTime(const Patient& patients){
        int cNumPatients =0;
        int tNumPatients =0;
        int waitTime =0;
        for (int i = 0; i < m_numPatients; i++)
        {
            if (*m_patientLineup[i] == patients)
            {
                if (patients.type() == 'C')
                {
                    cNumPatients++;
                }
                else{
                    tNumPatients++;
                }
            }
        }
        //only one type of patient is incremented, so either tNumPatients or cNumPatients = 0
        //so result will always be correct for either Triage or Contagion
        waitTime = cNumPatients * m_contaigenAvgTime + tNumPatients * m_triageAvgTime;
        std::cout.fill('0');
        std::cout.width(2);
        std::cout << U.convertHrs(waitTime) << ":";
        std::cout.width(2);
        std::cout << U.convertMins(waitTime);
    }
    void PreTriage::setAverageWaitTime(const Patient& patients){
        //store times in local variables, giving me incorrect results calling functions in formula
        //incorrect results likely due to patients.time() being in HH:MM format
        //Time has unsigned int operator overloaded
        unsigned int currentTime = U.getTime();
        unsigned int patientTicketTime = patients.time();

        if (patients.type() == 'C')
        {
            //given formula to calculate average time for patients
            m_contaigenAvgTime = ((currentTime - patientTicketTime) + (m_contaigenAvgTime * (patients.number() - 1))) / patients.number();
        }
        else if (patients.type() == 'T'){
            //given formula to calculate average time for patients
            m_triageAvgTime = ((currentTime - patientTicketTime) + (m_triageAvgTime * (patients.number() - 1)))/patients.number();
        }
    }
    int PreTriage::indexOfFirstInLine(char patientType) const{
        int match =-1;

        for (int i = 0; i < m_numPatients; i++)
        {
            if (*m_patientLineup[i] == patientType)
            {
                match =i;
                //end function when match is found
                return match;
            }
        }
        return match;
    }

    void PreTriage::load(){
        int numLines =0;
        char patientType;
        Patient* localPatient = nullptr;

        std::cout << "Loading data..." << std::endl;
        //ifstream object to open file name string stored in m_fileName
        std::ifstream dataFile(m_fileName);
        if (dataFile.is_open())
        {
            dataFile >> m_contaigenAvgTime;
            dataFile.ignore(2000,',');
            dataFile >> m_triageAvgTime;
            dataFile.ignore(2000, '\n');
            for (int i = 0; i < MAX_PATIENTS; i++)
            {
                //only get patient information if line in dataFile is not empty
                if (dataFile >> patientType)
                {
                    dataFile.ignore(2000, ',');
                    if (patientType == 'C')
                    {
                        //no delete, handled by deconstructor
                        localPatient = new TestPatient;
                    }
                    else if (patientType == 'T') {
                        //no delete, handled by deconstructor
                        localPatient = new TriagePatient;
                    }
                    if (localPatient != nullptr)
                    {
                        dataFile >> *localPatient;
                        //m_patientLineup[i] takes address of localPatient, effectively dynamically allocating memory to m_patientLineup[i]
                        //m_patientLineup[i] then gets deallocated instead of localPatient in deconstructor
                        m_patientLineup[i] = localPatient;
                        m_numPatients++;
                        numLines++;
                    }
                }
            }
            //eof goes 1 line past last line with data
            if (!dataFile.eof())
            {
                std::cout << "Warning: number of records exceeded " << MAX_PATIENTS << std::endl;
                std::cout << numLines << " Records imported..." <<std::endl << std::endl;
            }
            else if(numLines == 0){
                std::cout << "No data or bad data file!" << std::endl << std::endl;
            }
            else{
                std::cout << numLines << " Records imported..." <<std::endl << std::endl;
            }
        }
        //if file doesn't exist
        else
        {
            std::cout << "No data or bad data file!" << std::endl <<std::endl;
        }
    }

    void PreTriage::save(){
        int cPatient =0;
        int tPatient =0;
        //ofstream object to open file name stored in m_filename
        std::ofstream dataFile(m_fileName);
        if (dataFile.is_open())
        {
            std::cout << "Saving lineup..." << std::endl;
            //write average wait times to file
            dataFile << m_contaigenAvgTime << ',' << m_triageAvgTime << std::endl;
            for (int i = 0; i < m_numPatients; i++)
            {
                if (m_patientLineup[i] != nullptr) {
                    //write patient information to dataFile. << is overloaded for patient type
                    dataFile << *m_patientLineup[i] << std::endl;
                    // Count the patients based on type
                    if (m_patientLineup[i]->type() == 'C') {
                        cPatient++;
                    }
                    else if (m_patientLineup[i]->type() == 'T') {
                        tPatient++;
                    }
                }
            }
            dataFile.close();
        }
        std::cout << cPatient << " Contagion Tests and " << tPatient << " Triage records were saved!" << std::endl;
    }


    void PreTriage::registerPatient(){
        int selection;
        Menu subMenu("Select Type of Registration:\n1- Contagion Test\n2- Triage", 1);

        if (m_numPatients >= MAX_PATIENTS)
        {
            //won't go to else statement and will end
            std::cout <<"Line up full!"<<std::endl;
        }
        else{
            subMenu.display();
            std::cin >> selection;
            if (selection == 1 || selection == 2)
            {
                //enter information for Cotagion patient
                delete m_patientLineup[m_numPatients];
                if (selection ==1)
                {
                    m_patientLineup[m_numPatients] = new TestPatient;
                }
                else if (selection ==2)
                {
                    m_patientLineup[m_numPatients] = new TriagePatient;
                }
                m_patientLineup[m_numPatients]->setArrivalTime();
                std::cout << "Please enter patient information: " << std::endl;
                //clear buffer
                std::cin.ignore(2000, '\n');
                std::cin >> *m_patientLineup[m_numPatients];
                std::cout << std::endl;
                std::cout << "******************************************" <<std::endl;
                std::cout << *m_patientLineup[m_numPatients];
                std::cout << "Estimated Wait Time: ";
                //getWaitTime has std::cout to display time
                getWaitTime(*m_patientLineup[m_numPatients]);
                std::cout << std::endl << "******************************************" <<std::endl <<std::endl;
                m_numPatients++;
            }
            else{
                if (selection != 0) {
                    std::cout << "Invalid selection, exiting menu" << std::endl;
                }
            }
        }
    }
    void PreTriage::admit(){
        int selection;
        int index = -1;
        Patient* localPatient = nullptr;
        Menu subMenu("Select Type of Admittance:\n1- Contagion Test\n2- Triage",1);
        subMenu.display();
        std::cin >> selection;
        std::cout << std::endl;
        if (selection == 1 || selection == 2)
        {
            if (selection == 1)
            {
                index = indexOfFirstInLine('C');
                //localPatient, so call time and ticket issued are different times
                localPatient = new TestPatient;
            }
            else if (selection == 2)
            {
                index = indexOfFirstInLine('T');
                //localPatient, so call time and ticket issued are different times
                localPatient = new TriagePatient;
            }
            localPatient->setArrivalTime();
            //no matching patient type
            if (index == -1)
            {
                std::cout << "Lineup is empty!" << std::endl;
            }
            else{
                std::cout << "******************************************" <<std::endl;
                std::cout << "Call time: [" << localPatient->time() << "]" << std::endl;
                std::cout << "Calling at for " << *m_patientLineup[index];
                std::cout << "******************************************" <<std::endl <<std::endl;
                //if i include setAverageWaitTime it gives me incorrect output?
                setAverageWaitTime(*m_patientLineup[index]);
                //remove patient from array
                removeDynamicElement(m_patientLineup,index,m_numPatients);
            }
        }
        else{
            if (selection != 0) {
                std::cout << "Invalid selection, exiting menu" << std::endl;
            }
        }
        //deallocate localPatient
        delete localPatient;
        localPatient = nullptr;
    }
    void PreTriage::lineup(){
        int selection;
        int patientTypeNum = 0;
        Menu subMenu("Select The Lineup:\n1- Contagion Test\n2- Triage", 1);
        subMenu.display();
        std::cin >> selection;
        std::cout << "Row - Patient name                                          OHIP     Tk #  Time" << std::endl;
        std::cout << "-------------------------------------------------------------------------------" << std::endl;
        if (selection == 1 || selection ==2)
        {
            //display all patients if available
            for (int i = 0; i < m_numPatients; i++)
            {

                if (m_patientLineup[i]->type() == 'C' && selection == 1)
                {
                    //format to match given header above
                    patientTypeNum++;
                    std::cout.setf(std::ios::left);
                    std::cout.width(4);
                    std::cout << patientTypeNum << "- ";
                    std::cout.unsetf(std::ios::left);
                    std::clog << *m_patientLineup[i] << std::endl;
                }
                else if (m_patientLineup[i]->type() == 'T' && selection ==2)
                {
                    //format to match given header above
                    patientTypeNum++;
                    std::cout.setf(std::ios::left);
                    std::cout.width(4);
                    std::cout << patientTypeNum << "- ";
                    std::cout.unsetf(std::ios::left);
                    std::clog << *m_patientLineup[i] << std::endl;
                }
            }
            if (patientTypeNum == 0)
            {
                std::cout << "Line up is empty!" << std::endl;
            }
            std::cout << "-------------------------------------------------------------------------------" << std::endl;
        }
        else{
            if (selection != 0) {
                std::cout << "Invalid selection, exiting menu" << std::endl;
            }
        }
    }
    void PreTriage::run(){
        int selection;
        Menu subMenu("General Healthcare Facility Pre-Triage Application\n1- Register\n2- Admit\n3- View Lineup");
        do
        {
            subMenu.display();
            std::cin >> selection;
            if (selection == 0)
            {
                //do nothing, end function
            }
            else if (selection == 1)
            {
                registerPatient();
            }
            else if (selection == 2)
            {
                admit();
            }
            else if (selection == 3)
            {
                lineup();
            }
            else
            {
                std::cout << "Invalid selection, please choose 1, 2, 3, or 0" << std::endl;
            }
        } while (selection !=0);
    }
}