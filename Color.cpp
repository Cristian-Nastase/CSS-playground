#include <iostream>
#include <map>
#include <vector>
#include <limits>
#include "Color.h"

#include "Exceptii.h"

const std::map<char, std::string> Color::colorMap = {
    {'R', "\033[0;31m"},
    {'W', "\033[0;37m"},
    { 'Y', "\033[0;33m"},
    { 'G', "\033[0;32m"},
    { 'B', "\033[0;34m"},
    { 'P', "\033[0;35m"},
    { 'C', "\033[0;36m"}
};

int Color::noColors = 0;

Color::Color() : id(noColors++) {;
    currentColor = 'W';
    opacity = 1.0;
}

Color::Color(char currentColor, float opacity) : id(noColors++) {
    this->currentColor = currentColor;
    this->opacity = opacity;
}

Color::Color(const Color& obj) : id(noColors++) {
    this->currentColor = obj.currentColor;
    this->opacity = obj.opacity;
}

Color& Color::operator=(const Color& obj) {
    if (this == &obj) {
        return *this;
    }

    this->currentColor = obj.currentColor;
    this->opacity = obj.opacity;

    return *this;
}

char Color::getCurrentColor() const {
    return this->currentColor;
}

float Color::getOpacity() const {
    return this->opacity;
}

void Color::setCurrentColor(char color) {
    if (!colorMap.count(color)) {
        std::cout<<"Not a registered color, defaults to white -> "<<color;
        this->currentColor = 'W';
        throw CuloareInvalidaException();
    }

    this->currentColor = color;
}

std::istream& operator>>(std::istream& in, Color& obj) {
    std::vector<char> options;
    for (auto color: Color::colorMap) {
        options.push_back(color.first);
        std::cout<<options.size()<<". "<<color.first<<"\n";
    }

    std::cout<<"Select a color: ";

    int option;

    while (!(in >> option) || option == 0 || option > options.size()) {
        std::cout << "Not a possible option, try again\n";
        in.clear();
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    char colorChoosed = options[option - 1];

    obj.setCurrentColor(colorChoosed);

    std::cout<<"Enter the opacity (float): ";
    in>>obj.opacity;
    in.ignore();

    return in;
}


std::ostream& operator<<(std::ostream& out, const Color& obj) {
    out<<obj.getCurrentColor()<<"\nOpacity: "<<obj.opacity;
    return out;
}

void Color::resetColor() {
    std::cout<<"\033[0m";
}

void Color::printColored(const std::string& text) const {
    std::string color = colorMap.at(this->currentColor);

    std::cout<<color<<text;
    resetColor();
}