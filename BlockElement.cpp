#include <iostream>

#include "Element.h"
#include "BlockElement.h"
#include <string>

BlockElement::BlockElement() : Element() { }

BlockElement::BlockElement(const std::string& innerText, const std::string& className, const std::string& idName, bool isColored) : Element(innerText, className, idName, isColored) { }

BlockElement::BlockElement(const BlockElement &obj) : Element(obj) { }

BlockElement& BlockElement::operator=(const BlockElement &obj) {
    if (this == &obj) {
        return *this;
    }

    Element::operator=(obj);
    return *this;
}

BlockElement::~BlockElement() { }

std::istream& operator>>(std::istream &in, BlockElement &obj) {
    in>>(Element&)(obj);
    return  in;
}

std::ostream &operator<<(std::ostream &out, const BlockElement &obj) {
    out<<(Element&)(obj);
    return  out;
}

Element *BlockElement::clone() const {
    return new BlockElement(*this);
}

void BlockElement::render() const {
    return;
}