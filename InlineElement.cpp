#include <iostream>

#include "Element.h"
#include "InlineElement.h"
#include <string>

InlineElement::InlineElement() : Element(), alreadyRendered(false) { }

InlineElement::InlineElement(const std::string& innerText, const std::string& className, const std::string& idName, bool isColored) : Element(innerText, className, idName, isColored), alreadyRendered(false) { }

InlineElement::InlineElement(const InlineElement &obj) : Element(obj), alreadyRendered(false) { }

InlineElement& InlineElement::operator=(const InlineElement &obj) {
    if (this == &obj) {
        return *this;
    }

    Element::operator=(obj);

    this->alreadyRendered = false;

    return *this;
}

InlineElement::~InlineElement() { }

std::istream& operator>>(std::istream &in, InlineElement &obj) {
    in>>(Element&)(obj);
    std::cout<<"dwadawd";
    return  in;
}

std::ostream &operator<<(std::ostream &out, const InlineElement &obj) {
    out<<(Element&)(obj);
    out<<"Display: inline";
    return out;
}

Element *InlineElement::clone() const {
    return new InlineElement(*this);
}

void InlineElement::render() const {
    if (alreadyRendered) {
        return;
    }

    std::vector<const InlineElement*> group;
    group.push_back(this);

    Element* current = nextSibling;
    while (current != nullptr) {
        InlineElement* checkInline = dynamic_cast<InlineElement*>(current);

        if (checkInline == nullptr) {
            break;
        }

        checkInline->setRendered(true);
        group.push_back(checkInline);
        current = checkInline->getNextSibling();
    }

    renderGroup(group);
}

void InlineElement::renderGroup(std::vector<const InlineElement*>& group) {
    int maxHeight = 0;

    for (int i = 0; i < group.size(); i++) {
        int currentHeight = group[i]->boxModel->getHeight();
        if (currentHeight > maxHeight) {
            maxHeight = currentHeight;
        }
    }

    for (int line = 0; line < maxHeight; line++) {
        for (int j = 0; j < group.size(); j++) {
            group[j]->printLine(line);
        }
        std::cout<<"\n";
    }
}

void InlineElement::printLine(int line) const {
    if (line > boxModel->getHeight()) {
        return;
    }

    auto margin = boxModel->getMargin();
    auto padding = boxModel->getPadding();
    int border = boxModel->getBorder();

    int m_top = margin[0];

    int p_top = padding[0];
    int p_bottom = padding[2];

    if (line <= m_top) {
        this->printMarginLine();
        return;
    }

    if (line <= m_top + border) {
        this->printBorderLine();
        return;
    }

    if (line <= m_top + border + p_top) {
        this->printPaddingLine();
        return;
    }

    if (line <= m_top + border + p_top + 1) {
        this->printContent();
        return;
    }

    if (line <= m_top + border + p_top + 1 + p_bottom) {
        this->printPaddingLine();
        return;
    }

    if (line <= m_top + 2 * border + p_top + 1 + p_bottom) {
        this->printBorderLine();
        return;
    }

    this->printMarginLine();
}

void InlineElement::setRendered(bool rendered) {
    this->alreadyRendered = rendered;
}
