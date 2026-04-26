#include <iostream>
#include <vector>
#include <string>

#include "Selector.h"

#include "BlockElement.h"
#include "InlineElement.h"
#include <fstream>

#include "Exceptii.h"

int Selector::noSelector = 0;

Selector::Selector() : id(noSelector++) {
    selectorString = "N/A";

    type = '*';
    isEmpty = true;
}

Selector::Selector(const std::string& selectorString) : id(noSelector++) {
    this->selectorString = selectorString;

    isEmpty = true;

    verifyType();
}

Selector::Selector(const Selector &obj) : id(noSelector++) {
    this->selectorString = obj.selectorString;

    this->type = obj.type;

    if (obj.isEmpty) {
        this->isEmpty = obj.isEmpty;
        return;
    }

    for (int i = 0; i < obj.elements.size(); i++) {
        Element* ptr = obj.elements[i]->clone();
        this->elements.push_back(ptr);
    }

    this->isEmpty = false;
}

Selector& Selector::operator=(const Selector &obj) {
    if (this == &obj)
        return *this;

    this->selectorString = obj.selectorString;

    while (!elements.empty()) {
        delete elements[elements.size() - 1];
        this->elements.pop_back();
    }

    this->isEmpty = obj.isEmpty;
    for (int i = 0; i < obj.elements.size(); i++) {
        Element* ptr = obj.elements[i]->clone();
        this->elements.push_back(ptr);
    }

    this->type = obj.type;

    return *this;
}

Selector::~Selector() {
    for (int i = 0; i < elements.size(); i++) {
        delete elements[i];
    }
}

int Selector::getVectorSize() const {
    return elements.size();
}

char Selector::getType() const {
    return this->type;
}

std::string Selector::getSelectorString() const {
    return this->selectorString;
}

bool Selector::validSelector(const std::string& string) {
    std::string blockedCharacters = "~!@$%^&*()+=,/';:?><[]{}|`\\ \"";

    for (int i = 0 ; i < string.length(); i++) {
        if (blockedCharacters.find(string[i]) != std::string::npos)
            return false;
    }

    return true;
}

void Selector::verifyType() {
    char lastChr = '-';
    for (int i = 0; i < selectorString.length(); i++) {
        if (selectorString[i] == '.' || selectorString[i] == '#') {
            if (lastChr != '-') {
                std::cout<<"Compound selector, not allowed here, defaults to '*'.\n";
                this->type = '*';
                return;
            }

            lastChr = selectorString[i];
        }
    }

    if (lastChr == '-') {
        std::cout<<"Element selector, not allowed here, defaults to '*'. \n";
        this->type = '*';
        return;
    }

    if (lastChr == '.') {
        this->type = 'C';
    }

    if (lastChr == '#') {
        this->type = 'I';
    }

    this->selectorString = this->selectorString.substr(1);
}

void Selector::setSelectorString(const std::string& string) {
    if (string.empty()) {
        throw TextInvalidException();
    }

    if (!validSelector(string)) {
        std::cout<<"Invalid selector entered, will target all elements as default.";
        this->type = '*';

        this->selectorString = "N/A";

    }

    this->selectorString = string;

    verifyType();
}


std::istream& operator>>(std::istream &in, Selector &obj) {
    std::cout<<"Type what elements you want to select: ";

    char buffer[256];
    in>>buffer;

    obj.setSelectorString(buffer);

    return in;
}

std::ostream& operator<<(std::ostream &out, const Selector &obj) {
    out<<"\nSelector: "<<obj.getSelectorString()<<"\nElements it affects: ";

    for (int i = 0; i < obj.elements.size(); i++) {
        out<<"Element"<<i+1<<": \n"<<*obj.elements[i]<<"\n";
    }

    return out;
}

void Selector::changeSiblings() const {
    if (!elements.empty())
        elements.back()->setNextSibling(nullptr);

    for (int i = 0; i < elements.size() - 1; i++) {
        elements[i]->setNextSibling(elements[i+1]);
    }
}

// 0 - block
// 1 - inline
void Selector::createElement(int elementType) {
    std::cout<<"\n[Element "<<this->elements.size() + 1<<"]: \n\n";

    Element* e;

    if (elementType == 0) {
        e = new BlockElement;
    }
    else {
        e = new InlineElement;
    }

    std::cin>>*e;

    this->elements.push_back(e);
    isEmpty = false;

    changeSiblings();
}

void Selector::listElements() const {
    if (elements.empty()) {
        std::cout<<"\nNo elements created.\n";
        return;
    }

    for (int i = 0; i < elements.size(); i++) {
        std::cout<<"\n- Element "<<i+1<<"\n";
        std::cout<<*elements[i]<<'\n';
    }
}

void Selector::copyElement(int index) {
    Element* element = elements[index];

    Element* copy = element->clone();
    this->elements.push_back(copy);

    changeSiblings();
}

void Selector::removeElement(int index) {
    delete elements[index];

    this->elements.erase(this->elements.begin() + index);

    if (elements.empty()) {
        this->isEmpty = true;
    }

    changeSiblings();
}

bool Selector::checkClassName(const Element* element) const {
    return element->getClassName() == this->selectorString;
}

bool Selector::checkIdName(const Element* element) const {
    return element->getIdName() == this->selectorString;
}

std::vector<Element*> Selector::returnTargetedElements() const{
    std::vector<Element*> targetedElements;

    if (type != '*') {
        for (int i = 0; i < elements.size(); i++) {
            if (type == 'C' && checkClassName(elements[i])) {
                targetedElements.push_back(elements[i]);
            }

            else if (type == 'I' && checkIdName(elements[i])) {
                targetedElements.push_back(elements[i]);
            }
        }

        return targetedElements;
    }

    for (int i = 0; i < elements.size(); i++) {
        targetedElements.push_back(elements[i]);
    }

    return targetedElements;
}

void Selector::printElements() const {
    if (this->elements.empty()) {
        std::cout<<"No elements to print. \n";
        return;
    }
    for (int i = 0; i < elements.size(); i++) {
        elements[i]->render();
    }

    for (int i = 0; i < elements.size(); i++) {
        InlineElement* e = dynamic_cast<InlineElement*>(elements[i]);
        if (e != nullptr) {
            e->setRendered(false);
        }
    }
}

void Selector::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    for (auto* e : elements) {
        file << e->serialize() << "\n";
    }
}

void Selector::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw FisierException("No saved session found: " + filename);
    }

    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        Element* e;
        if (line.find("<div") != std::string::npos)
            e = new BlockElement;
        else
            e = new InlineElement;

        try {
            e->deserialize(line);
            elements.push_back(e);
            isEmpty = false;
        } catch (const std::exception& ex) {
            delete e;
        }
    }
    changeSiblings();
}
