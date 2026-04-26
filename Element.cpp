#include <iostream>
#include <string>

#include "Element.h"
#include "Box.h"
#include "Color.h"
#include <sstream>
int Element::noElements = 0;

Element::Element() : boxModel(new Box), color(new Color), id(noElements++) {
    innerText = "N/A";
    className = "N/A";
    idName = "N/A";

    isColored = true;
    boxModel->setTextLength(innerText.length());

    nextSibling = nullptr;
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
    this->innerText = innerText;
    this->className = checkString(className);
    this->idName = checkString(idName);

    this->isColored = isColored;

    boxModel->setTextLength(this->innerText.length());
    nextSibling = nullptr;
}

Element::Element(const Element& obj) : boxModel(new Box(*obj.boxModel)), color(new Color(*obj.color)), id(noElements++) {
    this->innerText = obj.innerText;
    this->className = obj.className;
    this->idName = obj.idName;

    this->isColored = obj.isColored;

    boxModel->setTextLength(innerText.length());
    nextSibling = nullptr;
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
    this->boxModel->setTextLength(innerText.length());

    delete this->color;
    this->color = new Color(*obj.color);

    return *this;
}

Element::~Element() {
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

Element* Element::getNextSibling() const {
    return this->nextSibling;
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

void Element::setNextSibling(Element *element) {
    if (element == nullptr) {
        return;
    }

    this->nextSibling = element;
}

std::string Element::readString(std::istream &in, const std::string& textToPrint) {
    std::string temp;
    std::cout<<textToPrint;
    in>>temp;

    return checkString(temp);
}

std::istream& operator>>(std::istream& in, Element& obj) {
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

void Element::printMarginLine() const {
    for (int j = 0; j < boxModel->getWidth(); j++) std::cout<<" ";
}

void Element::printBorderLine() const {
    int i, j;

    int width = boxModel->getWidth();

    auto margin = boxModel->getMargin();
    int m_left = margin[3];
    int m_right = margin[1];

    for (j = m_left; j != 0; j--) std::cout<<" ";

    for (j = width - m_left - m_right; j != 0; j--) std::cout << "|";

    for (j = m_right; j != 0; j--) std::cout<<" ";
}

void Element::printPaddingLine() const {
    int i, j;

    auto margin = boxModel->getMargin();
    int m_left = margin[3];
    int m_right = margin[1];

    int width = boxModel->getWidth();

    int contentWidth = width - m_left - m_right - 2 * boxModel->getBorder();

    for (j = m_left; j != 0; j--) std::cout << " ";

    for (j = boxModel->getBorder(); j != 0; j--) std::cout << "|";

    for (j = contentWidth; j != 0; j--) std::cout << " ";

    for (j = boxModel->getBorder(); j != 0; j--) std::cout << "|";

    for (j = m_right; j != 0; j--) std::cout << " ";
}

void Element::printContent() const {
    int j;

    auto margin = boxModel->getMargin();
    int m_left = margin[3];
    int m_right = margin[1];

    auto padding = boxModel->getPadding();
    int p_left = padding[3];
    int p_right = padding[1];

    for (j = m_left; j != 0; j--) std::cout << " ";
    for (j = boxModel->getBorder(); j != 0; j--) std::cout << "|";
    for (j = p_left; j != 0; j--) std::cout << " ";

    color->printColored(innerText);

    for (j = p_right; j != 0; j--) std::cout << " ";
    for (j = boxModel->getBorder(); j != 0; j--) std::cout << "|";
    for (j = m_right; j != 0; j--) std::cout << " ";
}

void Element::deserialize(const std::string& data) {
    size_t pos;

    pos = data.find('>');
    if (pos == std::string::npos) return;
    size_t start = pos + 1;
    size_t end = data.find('<', start);
    if (end == std::string::npos) return;
    innerText = data.substr(start, end - start);

    pos = data.find("class=\"");
    if (pos == std::string::npos) return;
    start = pos + 7;
    end = data.find('"', start);
    if (end == std::string::npos) return;
    className = data.substr(start, end - start);

    pos = data.find("id=\"");
    if (pos == std::string::npos) return;
    start = pos + 4;
    end = data.find('"', start);
    if (end == std::string::npos) return;
    idName = data.substr(start, end - start);

    pos = data.find("padding:");
    if (pos == std::string::npos) return;
    start = pos + 8;
    end = data.find(';', start);
    if (end == std::string::npos) return;
    std::istringstream paddingStream(data.substr(start, end - start));
    std::vector<int> p(4);
    for (int i = 0; i < 4; i++) paddingStream >> p[i];
    boxModel->setPadding(p);

    pos = data.find("margin:");
    if (pos == std::string::npos) return;
    start = pos + 7;
    end = data.find(';', start);
    if (end == std::string::npos) return;
    std::istringstream marginStream(data.substr(start, end - start));
    std::vector<int> m(4);
    for (int i = 0; i < 4; i++) marginStream >> m[i];
    boxModel->setMargin(m);

    pos = data.find("border:");
    if (pos == std::string::npos) return;
    start = pos + 7;
    end = data.find("px", start);
    if (end == std::string::npos) return;
    boxModel->setBorder(std::stoi(data.substr(start, end - start)));

    pos = data.find("color:");
    if (pos == std::string::npos) return;
    start = pos + 6;
    color->setCurrentColor(data[start]);

    boxModel->setTextLength(innerText.length());
}
