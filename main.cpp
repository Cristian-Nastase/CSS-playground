#include <iostream>
#include <map>
#include <vector>

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

    delete[] this->padding;
    this->padding = returnVector(1.0);
    for (int i = 0; i < 4; i++) {
        this->padding[i] = obj.padding[i];
    }

    delete[] this->margin;
    this->margin = returnVector(1.0);
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

class Color {
private:
    static const std::map<char, char*> colorMap;
    static const char* endString;
    char currentColor;
    bool active;
public:
    Color();
    Color(char currentColor, bool active);
    Color(const Color& obj);
    Color& operator=(const Color& obj);
    ~Color();

    char getCurrentColor() const;
    char* getEndString() const;

    void printColored(const char* text) const;
};

Color::Color() {
    colorMap.insert({"R", "Dsalut"});

    currentColor = "W";
    active = true;
}

void Color::printColored(const char* text) const {
    if (!this->active)
        return;

    char key = this->getCurrentColor();
    const char* color = colorMap.at(key);

    std::cout<<color<<text<<endString;
}

char Color::getCurrentColor() const {
    return this->currentColor;
}

char* Color::getEndString() const {
    return this->endString;
}

class Element {
private:
    static int noElements;
    char* text;
    const char* className;
    const char* id;
    bool isColored;
    Box& boxModel;
    Color& color;
public:

};

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
    float padding[4], margin[4];
    for (int i = 0; i < 4; i++) {
        padding[i] = 1.2;
        margin[i] = 2.1;
    }

    float border = 2.5;
    Box a(padding, margin, border), b = a, c;
    c = a;
    std::cout<<"\033[33m"<<&a<<" "<<&b<<" "<<&c;
}