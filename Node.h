#ifndef NODE_H
#define NODE_H

#include "Photo.h"

class Node {
public:
    string cat;
    Photo* photo;
    Node* next;
    Node* child;

    Node() {
        photo = new Photo();
        next = NULL;
        cat = "";
        child = NULL;
    }
};

#endif