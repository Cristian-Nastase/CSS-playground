#ifndef INLINEELEMENT_H
#define INLINEELEMENT_H

#include <iostream>
#include "Element.h"

class InlineElement : public Element {
private:
    bool alreadyRendered;

    static void renderGroup(std::vector<const InlineElement*>& group);
    void printLine(int line) const;
public:
    InlineElement();
    InlineElement(const std::string& innerText, const std::string& className, const std::string& idName, bool isColored);
    InlineElement(const InlineElement& obj);
    InlineElement& operator=(const InlineElement& obj);
    ~InlineElement();

    friend std::istream& operator>>(std::istream& in, InlineElement& obj);
    friend std::ostream& operator<<(std::ostream& out, const InlineElement& obj);

    void setRendered(bool rendered);

    void render() const override;
    Element* clone() const override;

    std::string serialize() const override;
};
#endif
