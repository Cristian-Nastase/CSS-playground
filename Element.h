#ifndef ELEMENT_H
#define ELEMENT_H

#include <iostream>
#include <string>
#include "Box.h"
#include "Color.h"

class Element {
private:
    static int noElements;

    static std::string readString(std::istream& in, std::string textToPrint);
    static std::string checkString(std::string& text);
protected:
    std::string innerText;
    std::string className;
    std::string idName;

    bool isColored;

    Box* boxModel;
    Color* color;

    const int id;
public:
    Element();
    Element(std::string& innerText, std::string& className, std::string& idName, bool isColored);
    Element(const Element& obj);
    Element& operator=(const Element& obj);
    virtual ~Element();


    std::string getClassName() const;
    std::string getIdName() const;
    int getId() const;

    void setClassName(std::string& string);
    void setIdName(std::string& string);
    void setColor(Color* color);
    void setBox(Box* box);

    friend std::istream& operator>>(std::istream& in, Element& obj);
    friend std::ostream& operator<<(std::ostream& out, const Element& obj);

    virtual void render() const;
};

#endif