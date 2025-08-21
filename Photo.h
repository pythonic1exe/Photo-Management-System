#ifndef PHOTO_H
#define PHOTO_H

#include <string>
using namespace std;

class Photo {
public:
    int SN;
    string name;
    string location;
    string type;
    int size;
    string CN;
    string date;
    string categories[5];

    void setSN(int sn) {
        SN = sn;
    }

    int getSN() const {
        return SN;
    }

    void setName(const string& name) {
        this->name = name;
    }

    string getName() const {
        return name;
    }

    void setLocation(const string& location) {
        this->location = location;
    }

    string getLocation() const {
        return location;
    }

    void setType(const string& type) {
        this->type = type;
    }

    string getType() const {
        return type;
    }

    void setSize(int size) {
        this->size = size;
    }

    int getSize() const {
        return size;
    }

    void setCN(const string& cn) {
        CN = cn;
    }

    string getCN() const {
        return CN;
    }

    void setDate(const string& date) {
        this->date = date;
    }

    string getDate() const {
        return date;
    }

    void setCategory(int index, const string& category) {
        if (index >= 0 && index < 5) {
            categories[index] = category;
        }
    }

    string getCategory(int index) const {
        if (index >= 0 && index < 5) {
            return categories[index];
        }
        return "";
    }
};

#endif