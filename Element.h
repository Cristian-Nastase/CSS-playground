#ifndef ELEMENT_H
#define ELEMENT_H

#include <iostream>
#include <string>
#include "Box.h"
#include "Color.h"

class Element {
private:
    static int noElements;

    static std::string readString(std::istream& in, const std::string& textToPrint);
    static std::string checkString(const std::string& text);
protected:
    std::vector<Element*> children;

    std::string innerText;
    std::string className;
    std::string idName;

    bool isColored;

    Box* boxModel;
    Color* color;

    const int id;

    void printMarginLine() const;
    void printBorderLine() const;
    void printPaddingLine() const;
    void printContent() const;
public:
    Element();
    Element(const std::string& innerText,const std::string& className,const std::string& idName, bool isColored);
    Element(const Element& obj);
    Element& operator=(const Element& obj);
    virtual ~Element();


    std::string getClassName() const;
    std::string getIdName() const;
    int getId() const;

    void setClassName(const std::string& string);
    void setIdName(const std::string& string);
    void setColor(const Color* color);
    void setBox(const Box* box);

    friend std::istream& operator>>(std::istream& in, Element& obj);
    friend std::ostream& operator<<(std::ostream& out, const Element& obj);

    void addChild(const Element& obj);
    void removeChild(int index);

    virtual void render() const = 0;
    virtual Element* clone() const = 0;
};

#endif