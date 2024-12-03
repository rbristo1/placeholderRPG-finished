#ifndef ITEM_H
#define ITEM_H

#include <string>


class Item {
    public:
        Item(); // Default constructor used for arrays
        Item(int);
        void reconstruct(int); // calls constructor again, used to avoid dynamic memory allocation
        Item(int, std::string, int); // Custom item
        void print(); // Used for testing only

        // Access and set functions
        int getID();
        std::string getName();
        int getEffect();
        void setID(int);
        void setName(std::string);
        void setEffect(int);

    private:
        int ID;
        std::string name;
        int effect;
};

#endif