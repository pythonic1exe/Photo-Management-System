#ifndef STACK_H
#define STACK_H

#include "Node.h"
#include <iostream>
using namespace std;

class Stack{
public:
    Node* top ;

    Stack(){
        top = NULL ;
    }

    void push(Node* n){
        Node* newNode = n ;
        newNode->next = NULL;
        if(top == NULL){
            top = newNode ;
        } else {
            newNode->next = top ;
            top = newNode ;
        }
    }

    Node* pop(){
        if(top == NULL){
            cout << "Stack Underflow\n" ;
            return NULL ;
        } else {
            Node* nodeToPop = top ;
            top = top->next ;
            nodeToPop->next = NULL;  
            return nodeToPop ;
        }
    }
};

#endif