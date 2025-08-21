/*
NAME: USMAN SHAKEEL
SAP ID: 70149476
CLASS: BSCS 4H
DSA ASSIGNMENT#2
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include "LinkedList.h"
using namespace std;

int main() {
    ifstream file("picture_data.csv");
    LinkedList l1;
    l1.addMainCategories();

    if (!file) {
        std::cerr << "Error opening file!\n";
        return 1;
    }

    string line;
    string name, location, type, CN, date,cat;
    int SN, size;
    string categories[5];
    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);
        string token;

        getline(ss, token, ',');
        SN = stoi(token);

        getline(ss, name, ',');
        getline(ss, location, ',');
        getline(ss, type, ',');

        getline(ss, token, ',');
        size = stoi(token);

        getline(ss, CN, ',');
        getline(ss, date, ',');

        for (int i = 0; i < 5; i++) {
            getline(ss, categories[i], ',');
        }

        l1.addPhoto("Default", SN, name, location, type, size, CN, date, categories);

    }

    int choice;
    
    do {
        cout << "\n===== Photo Management System =====" << endl;
        cout << "1. Add Photo" << endl;
        cout << "2. Delete Photo" << endl;
        cout << "3. Add Category" << endl;
        cout << "4. Delete Category" << endl;
        cout << "5. Change Category" << endl;
        cout << "6. Undo Last Action" << endl;
        cout << "7. Display Photos" << endl;
        cout << "8. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        string newCategory;
        string option;
        
        switch (choice) {
            case 1: {
                cout << "Enter category: ";
                cin >> cat;
                cout << "Enter serial number: ";
                cin >> SN;
                cout << "Enter photo name: ";
                cin >> name;
                cout << "Enter location: ";
                cin >> location;
                cout << "Enter type: ";
                cin >> type;
                cout << "Enter size: ";
                cin >> size;
                cout << "Enter camera name: ";
                cin >> CN;
                cout << "Enter date: ";
                cin >> date;
                
                cout << "Enter up to 5 categories (type 'end' to stop): ";
                for (int i = 0; i < 5; i++) {
                    cin >> categories[i];
                }    
                l1.addPhoto(cat, SN, name, location, type, size, CN, date, categories);
                break;
            }
            case 2: {
                cout << "Enter photo name to delete: ";
                cin >> name;
                l1.deletePhoto(name);
                break;
            }
            case 3: {
                cout << "Enter new category name: ";
                cin >> cat;
                l1.addCategory(cat);
                break;
            }
            case 4: {
                cout << "Enter category name to delete: ";
                cin >> cat;
                l1.deleteCategory(cat);
                break;
            }
            case 5: {
                string newCategory;
                cout << "Enter photo name: ";
                cin >> name;
                cout << "Enter new category: ";
                cin >> newCategory;
                l1.changeCategory(name,newCategory);
                break;
            }
            case 6:
                cout << "Enter option(Photo or Category): " ;
                cin >> option;
                l1.undoOperation(option);
                break;
            case 7:
                l1.Display();
                break;
            case 8:
                return 0 ;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 8);
    
    return 0;
   
}
