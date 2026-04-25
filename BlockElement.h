#ifndef BLOCKELEMENT_H
#define BLOCKELEMENT_H

#include <iostream>
#include <string>

#include "Element.h"

class BlockElement : public Element {
public:
    BlockElement();
    BlockElement(const std::string& innerText, const std::string& className, const std::string& idName, bool isColored);
    BlockElement(const BlockElement& obj);
    BlockElement& operator=(const BlockElement& obj);
    ~BlockElement();

    friend std::istream& operator>>(std::istream& in, BlockElement& obj);
    friend std::ostream& operator<<(std::ostream& out, const BlockElement& obj);

    void render() const override;
    Element* clone() const override;
};

#endif