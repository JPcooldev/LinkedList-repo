//
//  main.cpp
//  Spojovy_seznam-Prokop
//
//  Created by Jakub Prokop on 08.02.2022.
//

#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <iomanip>
#include "Node.h"
#include "List.h"



//kontrola vstupu
template <typename T>
void InputCheck (T& input, std::istream& stream, std::string command)
{
    while(true)     //opakovani dokud vstup nebude odpovidat dane potrebe
    {
        if (stream.fail())      //true kdyz nastave chyba (smichani 2 datovych typu)
        {
            stream.clear();     //vycisteni hlaseni o chybe
            //vycisteni proudu
            stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "ERROR - wrong input. Try again.\n" << command;
            std::cin >> input;
        }
        if (!stream.fail())
        {
            return;
        }
    }
        
}


//kontrola vstupu
template <typename T>
void InputCheckSpecific (T& input, std::istream& stream, std::string command, T a, T b, T c)
{
    while(true)
    {
        if (stream.fail())
        {
            stream.clear();
            stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "ERROR - wrong input. Try again.\n" << command;
            std::cin >> std::setw(1) >> input;
        }
        if (!stream.fail())             //overeni datoveho typu
        {
            if (input == a || input == b || input == c)     //overovani zadani hodnot ze zobrazenych moznosti
            {
                return;
            }
            else                //datovy typ je spravny, ale hodnota neni z nabizenych moznosti
            {
                stream.clear();
                stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "ERROR - wrong input. Try again.\n" << command;
                std::cin >> std::setw(1) >> input;
            }
        }
    }
        
}

//kontrola vstupu (hodonoty z nabizeneho rozmezi)
template <typename T>
void InputCheckSpecificNumbers (T& input, std::istream& stream, std::string command, T a, T b)
{
    while(true)
    {
        if (stream.fail())
        {
            stream.clear();
            stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "ERROR - wrong input. Try again.\n" << command;
            std::cin >> input;
        }
        if (!stream.fail())
        {
            if (a <= input && input <= b) {
                return;
            }
            else
            {
                stream.clear();
                stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "ERROR - wrong input. Try again.\n" << command;
                std::cin >> input;
            }
        }
    }
        
}





int main() {
    
    List Database;
    
    int action;
    std::cout << "1- Display \n2- Edit \n3- Leave \nEnter: ";
    std::cin >> std::setw(1) >> action;
        InputCheckSpecific(action, std::cin, "1- Display \n2- Edit \n3- Leave \nEnter: ", 1, 2, 3);
    while (action == 1 || action == 2)
    {
        
        //Dispay options
        switch (action) {
            
            case 1:
            {
                std::cout << "1- Display \n2- Display in alphabetical order \nEnter: ";
                int action2;
                std::cin >> std::setw(1) >> action2;
                    InputCheckSpecific(action2, std::cin, "1- Display \n2- Display in alphabetical order \nEnter: ", 1, 2, 2);
                
                switch (action2)
                {
                    case 1: {
                        Database.Print();
                        break; }
                        
                    case 2: {
                        Database.SortAZ();
                        Database.Print();
                        break; }
                    
                }
                break;
                
            }   // case 1 action
                
            case 2:
            {
                
                std::cout << "1- Add element \n2- Delete element \n3- Delete entire list \nEnter: ";
                int action3;
                std::cin >> std::setw(1) >> action3;
                    InputCheckSpecific(action3, std::cin, "1- Add element \n2- Delete element \n3- Delete entire list \nEnter: ", 1, 2, 3);
                
                switch (action3)
                {
                    
                    case 1:
                    {
                        std::string firstName, lastName;
                        int age, option;
                        char sex;
                        std::cout << "Enter first name: ";
                        std::cin >> firstName;
                            InputCheck(firstName, std::cin, "Enter first name: ");
                        
                        std::cout << "Enter last name: ";
                        std::cin >> lastName;
                            InputCheck(lastName, std::cin, "Enter last name: ");
                        
                        std::cout << "Enter sex (M-male/F-female): ";
                        std::cin >> sex;
                            InputCheckSpecific(sex, std::cin, "Enter sex (M-male/F-female): ", 'M', 'M', 'F');
                        
                        std::cout << "Enter age: ";
                        std::cin >> age;
                            InputCheckSpecificNumbers(age, std::cin, "Enter age: ", 1, 99);
                    
                        
                        std::cout << "Add to the list as (1)first, (2)last or (3)at specific place \nEnter: ";
                        std::cin >> option;
                           InputCheckSpecific(option, std::cin, "Add to the list as (1)first, (2)last or (3)at specific place \nEnter: ", 1, 2, 3);
                        
                            switch (option)
                            {
                                //Add to the list as first
                                case 1:
                                {
                                    Database.PushFront(firstName, lastName, age, sex);
                                    break;
                                    
                                }
                                
                                //Add to the list as last
                                case 2:
                                {
                                    Database.PushBack(firstName, lastName, age, sex);
                                    break;
                                }
                                    
                                //Add to the list at specific place
                                case 3:
                                {
                                    if (Database.GetTotal() == 0)
                                    {
                                        Database.PushFront(firstName, lastName, age, sex);
                                        std::cout << "List is empty. Element was added as first";
                                        break;
                                    }
                                    
                                    std::cout << "Add after which index? (number of elements = "<< Database.GetTotal() << ") \nEnter: ";
                                    int a;
                                    std::cin >> a;
                                        InputCheckSpecificNumbers(a, std::cin, "Add after which index?", 1, Database.GetTotal());
                                    Database.InsertAfter(firstName, lastName, age, sex, a);
                                    break;
                                }
                                    
                            }
                        std::cout << "Element was added\n";
                        break;
                    }  //case 1 action3
                    
                    case 2:
                    {
                        std::cout << "Delete element with index : ";
                        int action4;
                            InputCheckSpecificNumbers(action4, std::cin, "Delete element with index : ", 1, Database.GetTotal());
                        Database.Delete(action4);
                        std::cout << "Element was deleted\n";
                        break;
                    }
                    
                    case 3:
                    {
                        Database.DeleteALL();
                        std::cout << "List was deleted\n";
                        break;
                    }
                
                }   //switch action3
                
            }  //case 2 action
                        
        }   //switch acton
    
    std::cout << "1- Display \n2- Edit \n3- Leave \nEnter: ";
    std::cin >> std::setw(1) >> action;
        InputCheckSpecific(action, std::cin, "1- Display \n2- Edit \n3- Leave \nEnter: ", 1, 2, 3);
    
    }   //while action
    
    std::cout << "Have a nice day\n";

    return 0;
}
