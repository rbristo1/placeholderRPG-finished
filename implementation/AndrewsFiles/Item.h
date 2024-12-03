#ifndef ITEM_H
#define ITEM_H

#include <string>


class Item {
    public:
        Item();
        Item(int);
        void reconstruct(int);
        Item(int, std::string, int);
        void print();
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