#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <string>
#include "Node.h"
#include "Photo.h"
#include "Stack.h"

class LinkedList {
public:
    Node* head;
    Node* tail;
    Stack undoStack;

    LinkedList() {
        head = NULL;
        tail = NULL;
    }

    void addPhoto(string cat, int SN, string name, string location, string type, int size, string CN, string date, string categories[5]) {
        Node* temp = head;
        while (temp != NULL) {
            if (temp -> cat == cat) {
                Node* newNode = new Node;
                newNode -> photo = new Photo;
                newNode -> photo -> SN = SN;
                newNode -> photo -> name = name;
                newNode -> photo -> location = location;
                newNode -> photo -> type = type;
                newNode -> photo -> size = size;
                newNode -> photo -> CN = CN;
                newNode -> photo -> date = date;
                for (int i = 0; i < 5; i++) {
                    newNode -> photo -> categories[i] = categories[i];
                }

                if (temp -> child == NULL) {
                    temp -> child = newNode;
                } else {
                    Node* childTemp = temp -> child;
                    while (childTemp -> next != NULL) {
                        childTemp = childTemp -> next;
                    }
                    childTemp -> next = newNode;
                }
                for (int i = 0; i < 5; i++) {
                    string category = categories[i];
                    bool categoryExists = false;

                    Node* categoryTemp = head;
                    while (categoryTemp != NULL) {
                        if (categoryTemp -> cat == category) {
                            categoryExists = true;
                            break;
                        }
                        categoryTemp = categoryTemp -> next;
                    }
                    if (!categoryExists) {
                        if (category == "-") {
                            return;
                        }
                        addCategory(category);
                    }
                }
                return;
            }
            temp = temp -> next;
        }
        cout << "No category found, photo not added" << endl;
    }

    void deletePhoto(string name) {
        Node* categoryNode = head;

        if (head == NULL) {
            cout << "List is empty\n";
            return;
        }

        while (categoryNode != NULL) {
            Node* prevPhotoNode = NULL;
            Node* currentPhotoNode = categoryNode -> child;

            while (currentPhotoNode != NULL) {
                if (currentPhotoNode -> photo != NULL && currentPhotoNode -> photo -> name == name) {
                    if (prevPhotoNode == NULL) {
                        categoryNode -> child = currentPhotoNode -> next;
                    } else {
                        prevPhotoNode -> next = currentPhotoNode -> next;
                    }
                    undoStack.push(currentPhotoNode);

                    cout << "Photo deleted successfully\n";
                    return;
                }

                prevPhotoNode = currentPhotoNode;
                currentPhotoNode = currentPhotoNode -> next;
            }

            categoryNode = categoryNode -> next;
        }

        cout << "Photo not found\n";
    }

    void addMainCategories() {
        addCategory("Default");
        addCategory("Food");
        addCategory("Family");
        addCategory("Trip");
        addCategory("College");
        addCategory("University");
    }

    void undoOperation(string option) {
        if(option == "Photo") {
            if (undoStack.top != NULL) {
                Node* operationNode = undoStack.pop();
                if (operationNode -> photo != NULL) {
                    addPhoto(operationNode -> cat, operationNode -> photo -> SN, operationNode -> photo -> name,
                             operationNode -> photo -> location, operationNode -> photo -> type,
                             operationNode -> photo -> size, operationNode -> photo -> CN,
                             operationNode -> photo -> date, operationNode -> photo -> categories);
                    cout << "Undo Operation successful\n" ;
                } else {
                    cout << "Invalid operation in undo stack for Photo.\n";
                }
            } else {
                cout << "Nothing to undo for Photo.\n";
            }
        } 
        else if (option == "Category") {
            if (undoStack.top != NULL) {
                Node* operationNode = undoStack.pop();
                if (operationNode -> cat != "") {
                    addCategory(operationNode -> cat);
                    cout << "Undo Operation successful\n" ;
                } else {
                    cout << "Invalid operation in undo stack for Category.\n";
                }
            } else {
                cout << "Nothing to undo for Category.\n";
            }
        } 
        else {
            cout << "Invalid option for undo. Choose 'Photo' or 'Category'.\n";
        }
    }
    
    void changeCategory(string name, string newCat) {
        Node* categoryNode = head;

        while (categoryNode != NULL) {
            Node* prevPhotoNode = NULL;
            Node* currentPhotoNode = categoryNode -> child;

            while (currentPhotoNode != NULL) {
                if (currentPhotoNode -> photo -> name == name) {

                    if (categoryNode -> cat != "Default") {
                        if (prevPhotoNode == NULL) {
                            categoryNode -> child = currentPhotoNode -> next;
                        } else {
                            prevPhotoNode -> next = currentPhotoNode -> next;
                        }

                        addPhoto(newCat, currentPhotoNode -> photo -> SN, currentPhotoNode -> photo -> name,
                                    currentPhotoNode -> photo -> location, currentPhotoNode -> photo -> type,
                                    currentPhotoNode -> photo -> size, currentPhotoNode -> photo -> CN,
                                    currentPhotoNode -> photo -> date, currentPhotoNode -> photo -> categories);

                        for (int i = 0; i < 5; i++) {
                            if (currentPhotoNode -> photo -> categories[i] == "") {
                                currentPhotoNode -> photo -> categories[i] = newCat;
                                break;
                            }
                        }

                        delete currentPhotoNode;
                        cout << "Photo moved from category " << categoryNode -> cat << " to " << newCat << endl;
                        return;
                    } else {
                        cout << "Cannot remove photo from the Default category." << endl;
                        return;
                    }
                }

                prevPhotoNode = currentPhotoNode;
                currentPhotoNode = currentPhotoNode -> next;
            }

            categoryNode = categoryNode -> next;
        }

        cout << "Photo not found." << endl;
    }

    void deleteCategory(string cat) {
        Node* pp;
        Node* cp;

        if (head == NULL) {
            cout << "List is empty\n";
            return;
        }

        cp = head -> next;
        pp = head;

        if (pp -> cat == cat) {
            head = head -> next;
            return;
        } else {
            while (cp != NULL) {
                if (cp -> cat == cat) {
                    pp -> next = cp -> next;
                    if (cp == tail) {
                        tail = pp;
                    }
                    undoStack.push(cp);
                    return;
                }
                cp = cp -> next;
                pp = pp -> next;
            }

            cout << "Data not found\n";
        }
    }

    void addCategory(string cat) {
        Node* newNode = new Node;
        newNode -> cat = cat;
        newNode -> next = NULL;
        newNode -> child = NULL;

        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            tail -> next = newNode;
            tail = newNode;
        }
    }

    void Display() {
        Node* categoryNode = head;
        int categoryIndex = 1;

        while (categoryNode != NULL) {
            Node* photoNode = categoryNode -> child;
            int photoIndex = 1;

            while (photoNode != NULL) {
                cout << "Category: " << categoryNode -> cat << endl;
                cout << "  " << photoIndex << ". " << photoNode -> photo -> name << endl;
                photoNode = photoNode -> next;
                photoIndex++;
            }

            categoryNode = categoryNode -> next;
            categoryIndex++;
        }
    }
};
    
#endif
