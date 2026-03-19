#include <iostream>
#include <map>
#include <vector>
#include <cstring>

// box class

class Box {
private:
    float* padding;
    float* margin;
    float border;

    float* returnVector(float value);
public:
    Box();
    Box(float* padding, float* margin, float border);
    Box(const Box &obj);
    Box& operator=(const Box &obj);
    ~Box();

    friend std::istream& operator>>(std::istream& in, Box& obj);
    friend std::ostream& operator<<(std::ostream& out, const Box& obj);
};

float* Box::returnVector(float value) {
    float* vector = new float[4];

    for (int i = 0; i < 4; i++) {
        vector[i] = value;
    }

    return vector;
}

Box::Box() {
    padding = returnVector(1.0);
    margin = returnVector(1.0);
    border = 1.0;
}

Box::Box(float* padding, float* margin, float border) {
    this->padding = returnVector(1.0);
    for (int i = 0; i < 4; i++) {
        this->padding[i] = padding[i];
    }

    this->margin = returnVector(1.0);
    for (int i = 0; i < 4; i++) {
        this->margin[i] = margin[i];
    }

    this->border = border;
}

Box::Box(const Box &obj) {
    this->padding = returnVector(1.0);
    for (int i = 0; i < 4; i++) {
        this->padding[i] = obj.padding[i];
    }

    this->margin = returnVector(1.0);
    for (int i = 0; i < 4; i++) {
        this->margin[i] = obj.margin[i];
    }

    this->border = obj.border;
}

Box& Box::operator=(const Box &obj) {
    if (this == &obj) {
        return *this;
    }

    for (int i = 0; i < 4; i++) {
        this->padding[i] = obj.padding[i];
    }

    for (int i = 0; i < 4; i++) {
        this->margin[i] = obj.margin[i];
    }

    this->border = obj.border;

    return *this;
}

Box::~Box() {
    if (padding != nullptr) {
        delete[] padding;
        padding = nullptr;
    }

    if (margin != nullptr) {
        delete[] margin;
        margin = nullptr;
    }
}

std::istream& operator>>(std::istream& in, Box& obj) {
    std::cout<<"Padding (4 values): ";
    for (int i = 0; i < 4; i++) {
        in>>obj.padding[i];
    }

    std::cout<<"Margin (4 values): ";
    for (int i = 0; i < 4; i++) {
        in>>obj.margin[i];
    }

    std::cout<<"Border (1 value): ";
    in>>obj.border;

    return in;
}

std::ostream& operator<<(std::ostream& out, const Box& obj) {
    out<<"Padding: ";
    for (int i = 0; i < 4; i++) {
        out<<obj.padding[i]<<" ";
    }

    out<<"\n";

    out<<"Margin: ";
    for (int i = 0; i < 4; i++) {
        out<<obj.margin[i]<<" ";
    }

    out<<"\n";
    out<<"Border: "<<obj.border;

    return out;
}


// color class


class Color {
private:
    // static const std::map<char, char*> colorMap;
    char currentColor;
    bool active;
public:
    Color();
    Color(char currentColor, bool active);
    Color(const Color& obj);
    Color& operator=(const Color& obj);
    ~Color();

    friend std::istream& operator>>(std::istream& in, Color& obj);
    friend std::ostream& operator<<(std::ostream& out, const Color& obj);

    char getCurrentColor() const;
    void setCurrentColor(char color);
    void resetColor();

    void printColored(const char* text);

};

void Color::resetColor() {
    std::cout<<"\033[0m";
}

void Color::printColored(const char* text) {
    if (!this->active)
        return;

    char key = this->getCurrentColor();
    // const char* color = colorMap.at(key);

    // std::cout<<color<<text;
    this->resetColor();
}

char Color::getCurrentColor() const {
    return this->currentColor;
}

void Color::setCurrentColor(char color) {
    this->currentColor = color;
}

Color::Color() {;
    currentColor = 'W';
    active = true;
}

Color::Color(char currentColor, bool active) {
    this->currentColor = currentColor;
    this->active = active;
}

Color::Color(const Color& obj) {
    this->currentColor = obj.currentColor;
    this->active = obj.active;
}

Color& Color::operator=(const Color& obj) {
    if (this == &obj) {
        return *this;
    }

    this->currentColor = obj.currentColor;
    this->active = obj.active;

    return *this;
}

Color::~Color() {
    return;
}

std::istream& operator>>(std::istream& in, Color& obj) {
    std::cout<<"Select a color: ";

    int option;

    in>>option;

    if (option == 1) {
        obj.setCurrentColor('R');
    }

    return in;
}


std::ostream& operator<<(std::ostream& out, const Color& obj) {
    out<<obj.getCurrentColor();
    return out;
}

// element class


class Element {
private:
    static int noElements;
    char* text;
    char* className;
    char* id;
    bool isColored;
    Box* boxModel;
    Color* color;

    char* returnEmptyString();
    char* testEmptyString(char* text);
    void readString(std::istream& in, std::string text, char*& member);
public:
    Element();
    Element(char* text, char* className, char* id, bool isColored);
    Element(const Element& obj);
    Element& operator=(const Element& obj);
    ~Element();

    friend std::istream& operator>>(std::istream& in, Element& obj);
    friend std::ostream& operator<<(std::ostream& out, const Element& obj);
};

int Element::noElements = 0;

char* Element::returnEmptyString() {
    char* p = new char[4];
    strcpy(p,"N/A");

    return p;
}

char* Element::testEmptyString(char* text) {
    if (text == nullptr) {
        return returnEmptyString();
    }

    char* copy = new char[strlen(text) + 1];
    strcpy(copy, text);
    return copy;
}

Element::Element() : boxModel(new Box), color(new Color) {
    noElements++;

    text = returnEmptyString();
    className = returnEmptyString();
    id = returnEmptyString();

    isColored = true;
}

Element::Element(char* text, char* className, char* id, bool isColored) : boxModel(new Box), color(new Color) {
    noElements++;

    this->text = testEmptyString(text);
    this->className = testEmptyString(className);
    this->id = testEmptyString(id);

    this->isColored = isColored;
}

Element::Element(const Element& obj) : boxModel(new Box(*obj.boxModel)), color(new Color(*obj.color)) {
    noElements++;

    this->text = new char[strlen(obj.text) + 1];
    strcpy(this->text, obj.text);

    this->className = new char[strlen(obj.className) + 1];
    strcpy(this->className, obj.className);

    this->id = new char[strlen(obj.id) + 1];
    strcpy(this->id, obj.id);

    this->isColored = obj.isColored;
}

Element& Element::operator=(const Element& obj) {
    if (this == &obj) {
        return *this;
    }

    delete[] this->className;
    this->className = new char[strlen(obj.className) + 1];
    strcpy(this->className, obj.className);

    delete[] this->id;
    this->id = new char[strlen(obj.id) + 1];
    strcpy(this->id, obj.id);

    delete[] this->text;
    this->text = new char[strlen(obj.text) + 1];
    strcpy(this->text, obj.text);

    this->isColored = obj.isColored;

    delete boxModel;
    this->boxModel = new Box(*obj.boxModel);

    delete color;
    this->color = new Color(*obj.color);

    return *this;
}

Element::~Element() {
    noElements--;
    delete boxModel;
    delete color;
    delete[] className;
    delete[] id;
    delete[] text;
}

void Element::readString(std::istream& in, std::string textToPrint, char*& member) {
    char *buffer = new char[256];
    std::cout<<textToPrint;
    in>>buffer;

    delete[] member;
    member = new char[strlen(buffer) + 1];
    strcpy(member, buffer);

    delete[] buffer;
}

std::istream& operator>>(std::istream& in, Element& obj) {
    obj.readString(in,"Enter a text: ", obj.text);
    obj.readString(in, "Enter a class name: ", obj.className);
    obj.readString(in, "Enter an id: ", obj.id);

    in>>*obj.boxModel;
    in>>*obj.color;

    return in;
}

std::ostream &operator<<(std::ostream &out, const Element &obj) {
    out<<"Text: "<<obj.text<<"\n";
    out<<"Class Name: "<<obj.className<<"\n";
    out<<"Id:"<<obj.id<<"\n";

    out<<"Box model: "<<*obj.boxModel<<"\n";
    out<<"Color: "<<*obj.color;

    return out;
}

// selector class


class Selector {
    private:
        char* selectorString;
        int type;
        std::vector<Element> element;
        bool isEmpty;
    public:
        Selector();
        Selector(char* selectorString, bool cascades);
        Selector(const Selector &obj);
        Selector& operator=(const Selector &obj);
        ~Selector();
};

int main() {
    Element e;
    std::cin>>e;
    std::cout<<e;
    return 0;
}