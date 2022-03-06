//
//  Node.h
//  Spojovy_seznam-Prokop
//
//  Created by Jakub Prokop on 08.02.2022.
//

#pragma once

class Node {
public:
    int index;
    std::string firstName, lastName;
    int age;
    char sex;
    Node *next;
    Node() { next = NULL; index = 0; }
    Node(std::string, std::string, int, char);
};

Node::Node(std::string fn, std::string ln, int a, char s):
    firstName(fn), lastName(ln), age(a), sex(s)
{
        next = NULL;
        index = 0;
}
