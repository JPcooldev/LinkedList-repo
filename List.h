//
//  List.h
//  Spojovy_seznam-Prokop
//
//  Created by Jakub Prokop on 08.02.2022.
//

#pragma once
#include "List.h"

class List {
public:
    int total;
    Node *head;
    List() { head = NULL; total = 0; }
    void PushFront(std::string, std::string, int, char);
    void InsertAfter(std::string, std::string, int, char, int);
    void PushBack(std::string, std::string, int, char);
    void Delete(int);
    void DeleteALL();
    void Print();
    void SortAZ();
    int GetTotal() { return total;}
    
};

//prirazeni indexu prvku seznamu
int Index(Node *head) {
    
    Node *temp1 = head;
    int a = 1;
    
    while (temp1 != NULL) {
        (temp1->index) = a;
        a++;
        temp1 = temp1->next;
    }
    return a-1;
}

//pridani prvku na prvni misto seznamu
void List::PushFront(std::string fn, std::string ln, int a, char s) {
    
    Node *newNode = new Node(fn, ln, a, s);
    
    if(head == NULL)
    {
        head = newNode;
        total = Index(head);
        return;                    //newNode->next = NULL; netreba, nebot constructor Node() tohle vykona
    }
    
    Node *temp = head;
    head = newNode;
    newNode->next = temp;
    total = Index(head);
}

//pridani prvku na dane misto v seznamu
void List::InsertAfter(std::string fn, std::string ln, int a, char s, int index0) {
    
    //osetreni vstupu index0 > total (index je vetsi, nez kolik je lidi v databazi)
    Node *newNode = new Node(fn, ln, a, s);     //vytvoreniho noveho prvku
    if(head == NULL){
        head = newNode;
        total = Index(head);
        return;
    }
    
    Node *search = head;
    while(search->index != index0){     //nalezeni pointeru na dany prvek
        search = search->next;
    }
    Node *temp = search->next;      //prvek na miste index0 ukazuje na search->next
    search->next = newNode;         //vlozeni prvku
    newNode->next = temp;           //napojeni na zbytek seznamu
    total = Index(head);
}

//pridani prvku na posledni misto seznamu
void List::PushBack(std::string fn, std::string ln, int a, char s) {
    
    Node *newNode = new Node(fn, ln, a, s);
    if(head == NULL){
        head = newNode;
        total = Index(head);
        return;
    }
    
    Node *temp = head;
    while(temp->next != NULL) {
         temp = temp->next;
    }
    temp->next = newNode;       //napojeni prvku na posledni prvke seznamu. Napojeny prvek pak ukazuje na NULL
    total = Index(head);
    
}

//smazani daneho prvku
void List::Delete(int index0) {
    
    Node *search = head;
    if(index0 == 1)     //smazani prvniho prvku
    {
        Node *previous = head;
        head = head->next;
        previous = NULL;
        total = Index(head);
        return;
    }
    while (search->index != index0-1)       //hledani poinetru na prvek s indexem index0
    {
        search = search->next;
    }
    Node *previous = search;            //pointer na prvek s indexem index0
    search =  search->next;
    Node *current = search;             //pointer na prvek, ktery chceme smazat
    previous->next = current->next;     //prvku, ktery ukazuje na prevek, ktery chceme smazat, dame ukazatel na dalsi prvek
    current = NULL; //delete current    //vycisteni pamati
    total = Index(head);
}

//smazani celeho seznamu
void List::DeleteALL(){
    for (int i = total; i > 0; i--) {
        Delete(i);
    }
}

//vypsani seznamu
void List::Print() {
    
    if(head == NULL){
        std::cout<< "List is empty\n";
        return;
    }
    
    Node* temp = head;
    std::cout << "Head\n";
    while (temp != nullptr) {
        std::cout << temp->index << " " << temp->lastName << " " << temp->firstName << "\n"
                  << "  " << temp->sex << " " << temp->age << "\n";
        temp = temp->next;
    }
    std::cout << "Total: " << total << "\n\n";
}


void List::SortAZ() {
    
    if(head == NULL){     //kdyz je list prazdny netreba nic serazovat
        return;
    }
    
    Node *temp = head;
    std::vector<std::string> LastNames;      //vytvoreni dyn. pole, do ktereho se ulozi lastNames
    while (temp->next != NULL ) {
        LastNames.push_back(temp->lastName);
        temp = temp->next;
    }
    LastNames.push_back(temp->lastName);      //while nedosahne na posledni hodnotu
    
    int m = LastNames.size();
    std::string changestr;
    bool change = false;
    do {                               //razeni prvku pole podle abecedy (a<z), nejvetsi prvek se posune na pravou stranu
        change = false;
        m--;                                            //posledni prvek nemusim srovnavat, dostanu tam ten "nejvetsi"
        for (int i = 0; i < m; i++)
            if(LastNames[i] > LastNames[i+1]) {
                changestr = LastNames[i+1];
                LastNames[i+1] = LastNames[i];
                LastNames[i] = changestr;
                change = true;                          //pokud probehne vymena, cyklus probehne jeste jednou
            }
        
    } while (change);
    
    for (int i = 0; i < LastNames.size(); i++) {        //razeni seznamu podle serazenych jmen ve vectoru
        temp = head;
        if(i == 0) {
            if (temp->lastName == LastNames[i]) {       //pripad, kdy je prvni jmena na sve pozici bez upravy
                return;
            }
            while (temp->lastName != LastNames[i]) {    //hledani pointeru na prvni jmeno ve vectoru
                temp = temp->next;
            }
            PushFront(temp->firstName, temp->lastName, temp->age, temp->sex);  //posunuti prvku seznamu na prvni pozici
        }
        if (i != 0) {
            while (temp->lastName != LastNames[i]) {    //hledani pointeru na dane jmeno ve vectoru
                temp = temp->next;
            }
            InsertAfter(temp->firstName, temp->lastName, temp->age, temp->sex, i);   //vlozeni prvku seznamu za predchozi jmeno podle vectoru
        }
    }
    
    //seznam se nam vytvori usporadany a za nim ve stare podobe, ten se smaze
    for (int i = 2*(LastNames.size()); i > LastNames.size(); i--)
    {
        Delete(i);
    }
}
