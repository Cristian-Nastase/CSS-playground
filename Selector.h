#ifndef SELECTOR_H
#define SELECTOR_H

#include <iostream>
#include <string>
#include <vector>

#include "Element.h"

class Selector {
private:
    static int noSelector;
    const int id;

    std::string selectorString;
    char type;
    std::vector<Element*> elements;

    bool isEmpty;

    static bool validSelector(const std::string& string);

    bool checkClassName(const Element* element) const;
    bool checkIdName(const Element* element) const;

    void changeSiblings() const;
public:
    Selector();
    Selector(const std::string& selectorString);
    Selector(const Selector &obj);
    Selector& operator=(const Selector &obj);
    ~Selector();

    int getVectorSize() const;
    char getType() const;
    std::string getSelectorString() const;

    void setSelectorString(const std::string& string);

    friend std::istream& operator>>(std::istream& in, Selector& obj);
    friend std::ostream& operator<<(std::ostream& out, const Selector& obj);

    void createElement(int elementType);
    void listElements() const;
    void addElement(Element* element);
    void removeElement(int index);

    void verifyType();

    std::vector<Element*> returnTargetedElements() const;

    void printElements() const;
};

#endif