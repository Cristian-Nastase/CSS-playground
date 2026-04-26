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
    in>>static_cast<Element&>(obj);
    return  in;
}

std::ostream &operator<<(std::ostream &out, const BlockElement &obj) {
    out<<static_cast<const Element&>(obj);
    out<<"Display: block\n";
    return  out;
}

Element *BlockElement::clone() const {
    return new BlockElement(*this);
}

void BlockElement::render() const {
    int j;

    auto margin = boxModel->getMargin();
    auto padding = boxModel->getPadding();

    int m_top = margin[0];
    int m_bottom = margin[2];

    int p_top = padding[0];
    int p_bottom = padding[2];

    int border = boxModel->getBorder();

    std::cout<<"\n";

    // on top of content
    for (j = 0; j < m_top; j++) {
        printMarginLine();
        std::cout<<"\n";
    }

    for (j = 0; j < border; j++) {
        printBorderLine();
        std::cout<<"\n";
    }

    for (j = 0; j < p_top; j++) {
        printPaddingLine();
        std::cout<<"\n";
    }

    printContent();
    std::cout<<"\n";

    // bottom of content
    for (j = 0; j < p_bottom; j++) {
        printPaddingLine();
        std::cout<<"\n";
    }

    for (j = 0; j < border; j++) {
        printBorderLine();
        std::cout<<"\n";
    }

    for (j = 0; j < m_bottom; j++) {
        printMarginLine();
        std::cout<<"\n";
    }

    std::cout<<"\n";
}

std::string BlockElement::serialize() const {
    auto p = boxModel->getPadding();
    auto m = boxModel->getMargin();
    int b = boxModel->getBorder();

    return "<div class=\"" + className + "\" id=\"" + idName + "\" "
           "style=\"padding:" + std::to_string(p[0]) + " " + std::to_string(p[1]) + " " + std::to_string(p[2]) + " " + std::to_string(p[3]) + "; "
           "margin:" + std::to_string(m[0]) + " " + std::to_string(m[1]) + " " + std::to_string(m[2]) + " " + std::to_string(m[3]) + "; "
           "border:" + std::to_string(b) + "px solid; " + "color:" + std::string(1, color->getCurrentColor()) + "; " + " \">"
           + innerText + "</div>";
}