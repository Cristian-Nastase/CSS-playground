#include <iostream>

#include "Element.h"
#include "InlineElement.h"
#include <string>

InlineElement::InlineElement() : Element() { }

InlineElement::InlineElement(const std::string& innerText, const std::string& className, const std::string& idName, bool isColored) : Element(innerText, className, idName, isColored) { }

InlineElement::InlineElement(const InlineElement &obj) : Element(obj) { }

InlineElement& InlineElement::operator=(const InlineElement &obj) {
    if (this == &obj) {
        return *this;
    }

    Element::operator=(obj);
    return *this;
}

InlineElement::~InlineElement() { }

std::istream& operator>>(std::istream &in, InlineElement &obj) {
    in>>static_cast<Element&>(obj);
    return  in;
}

std::ostream &operator<<(std::ostream &out, const InlineElement &obj) {
    out<<static_cast<const Element&>(obj);
    return  out;
}

Element *InlineElement::clone() const {
    return new InlineElement(*this);
}

void InlineElement::render() const {
    return;
}
