#ifndef INLINEELEMENT
#define INLINEELEMENT

#include <iostream>
#include "Element.h"

class InlineElement : public Element {
public:
    InlineElement();
    InlineElement(const std::string& innerText, const std::string& className, const std::string& idName, bool isColored);
    InlineElement(const InlineElement& obj);
    InlineElement& operator=(const InlineElement& obj);
    ~InlineElement();

    friend std::istream& operator>>(std::istream& in, InlineElement& obj);
    friend std::ostream& operator<<(std::ostream& out, const InlineElement& obj);

    void render() const override;
    Element* clone() const override;
};
#endif
