#include <iostream>
#include <string>

#include "Element.h"
#include "Box.h"
#include "Color.h"

int Element::noElements = 0;

Element::Element() : boxModel(new Box), color(new Color), id(noElements++) {
    innerText = "N/A";
    className = "N/A";
    idName = "N/A";

    isColored = true;
}

std::string Element::checkString(const std::string& text) {
    if (text.empty()) {
        return "N/A";
    }

    std::string blockedCharacters = "~!@$%^&*()+=,./';:?><[]{}|`#\\ \"";

    for (int i = 0; i < blockedCharacters.length(); i++) {
        if (text.find(blockedCharacters[i]) != std::string::npos)
            return "N/A";
    }

    return text;
}

Element::Element(const std::string& innerText, const std::string& className, const std::string& idName, bool isColored) : boxModel(new Box), color(new Color), id(noElements++) {
    this->innerText = checkString(innerText);
    this->className = checkString(className);
    this->idName = checkString(idName);

    this->isColored = isColored;
}

Element::Element(const Element& obj) : boxModel(new Box(*obj.boxModel)), color(new Color(*obj.color)), id(noElements++) {
    this->innerText = obj.innerText;
    this->className = obj.className;
    this->idName = obj.idName;

    this->isColored = obj.isColored;

    for (int i = 0; i < obj.children.size(); i++) {
        this->children.push_back(obj.children[i]->clone());
    }
}

Element& Element::operator=(const Element& obj) {
    if (this == &obj) {
        return *this;
    }

    this->innerText = obj.innerText;
    this->className = obj.className;
    this->idName = obj.idName;

    this->isColored = obj.isColored;

    delete this->boxModel;
    this->boxModel = new Box(*obj.boxModel);

    delete this->color;
    this->color = new Color(*obj.color);

    for (int i = 0; i < children.size(); i++)
        delete children[i];

    this->children.clear();

    for (int i = 0; i < obj.children.size(); i++) {
        this->children.push_back(obj.children[i]->clone());
    }

    return *this;
}

Element::~Element() {
    for (int i = 0; i < children.size(); i++)
        delete children[i];

    delete boxModel;
    delete color;
}

std::string Element::getClassName() const {
    return this->className;
}

std::string Element::getIdName() const {
    return this->idName;
}

int Element::getId() const {
    return this->id;
}

void Element::setClassName(const std::string& string) {
    this->className = checkString(string);
}

void Element::setIdName(const std::string& string) {
    this->idName = checkString(string);
}

void Element::setBox(const Box* box) {
    if (box == nullptr) {
        return;
    }

    delete this->boxModel;
    this->boxModel = new Box(*box);
}

void Element::setColor(const Color* color) {
    if (color == nullptr) {
        return;
    }

    delete this->color;
    this->color = new Color(*color);
}

std::string Element::readString(std::istream &in, const std::string& textToPrint) {
    std::string temp;
    std::cout<<textToPrint;
    in>>temp;

    return checkString(temp);
}

std::istream& operator>>(std::istream& in, Element& obj) {
    in.ignore(1000, '\n');

    obj.innerText = Element::readString(in,"Enter a text: ");
    obj.className = Element::readString(in, "Enter a class name: ");
    obj.idName = Element::readString(in, "Enter an id: ");

    std::cout<<"\n(Box model): \n";
    in>>*obj.boxModel;
    obj.boxModel->setTextLength(obj.innerText.length());

    std::cout<<"\n(Color): \n";
    in>>*obj.color;

    return in;
}

std::ostream& operator<<(std::ostream &out, const Element &obj) {
    out<<"Text: "<<obj.innerText<<"\n";
    out<<"Class Name: "<<obj.className<<"\n";
    out<<"Id:"<<obj.idName<<"\n";

    out<<"Box model: "<<*obj.boxModel<<"\n";
    out<<"Color: "<<*obj.color;

    return out;
}

void Element::addChild(const Element& obj) {
    children.push_back(obj.clone());
}

void Element::removeChild(int index) {
    delete children[index];
    children.erase(children.begin() + index);
}