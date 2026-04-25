#include "Box.h"

#include <limits>
#include <vector>

int Box::noBoxes = 0;

std::vector<int> Box::returnVector(int value) {
    return std::vector<int>{value, value, value, value};
}

Box::Box() : id(noBoxes++) {
    padding = returnVector(1);
    margin = returnVector(1);
    border = 1;

    updateWidth(0);
    updateHeight();
    updateAspectRatio();
}

Box::Box(const std::vector<int> &padding, const std::vector<int> &margin, int border) : id(noBoxes++) {
    if (padding.size() != 4) {
        return;
    }

    this->padding = padding;

    if (margin.size() != 4) {
        return;
    }

    this->margin = margin;

    this->border = border;

    updateWidth(0);
    updateHeight();
    updateAspectRatio();
}

Box::Box(const Box &obj) : id(noBoxes++) {
    this->padding = obj.padding;
    this->margin = obj.margin;
    this->border = obj.border;

    this->width = obj.width;
    this->height = obj.height;
    this->aspectRatio = obj.aspectRatio;
}

Box &Box::operator=(const Box &obj) {
    if (this == &obj) {
        return *this;
    }

    this->padding = obj.padding;
    this->margin = obj.margin;
    this->border = obj.border;

    this->width = obj.width;
    this->height = obj.height;
    this->aspectRatio = obj.aspectRatio;

    return *this;
}

std::vector<int> Box::getPadding() const {
    return padding;
}

std::vector<int> Box::getMargin() const {
    return margin;
}

int Box::getBorder() const {
    return border;
}

int Box::getWidth() const {
    return width;
}

int Box::getHeight() const {
    return height;
}

void Box::setPadding(const std::vector<int> &padding) {
    if (padding.size() != 4)
        return;

    this->padding = padding;
}

void Box::setMargin(const std::vector<int> &margin) {
    if (margin.size() != 4) {
        return;
    }

    this->margin = margin;
}

void Box::setBorder(int border) {
    this->border = border;
}

void Box::setTextLength(int textLength) {
    updateWidth(textLength);
}

void Box::updateWidth(int textLength) {
    width = padding[1] + padding[3] + margin[1] + margin[3] + 2 * border + textLength;
}

void Box::updateHeight() {
    height = padding[0] + padding[2] + margin[0] + margin[2] + 2 * border + 1;
}

void Box::updateAspectRatio() {
    aspectRatio = static_cast<double>(width) / height;
}

int Box::readInt(std::istream &in) {
    int temp;

    while (!(in >> temp) || temp < 0) {
        std::cout << "Enter only natural numbers.\n";
        in.clear();
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return temp;
}

std::istream &operator>>(std::istream &in, Box &obj) {
    std::cout << "Padding (4 values -> top, right, bottom, left): ";
    for (int i = 0; i < 4; i++) {
        obj.padding[i] = Box::readInt(in);
    }

    std::cout << "Margin (4 values -> top, right, bottom, left): ";
    for (int i = 0; i < 4; i++) {
        obj.margin[i] = Box::readInt(in);
    }

    std::cout << "Border (1 value): ";
    obj.border = Box::readInt(in);

    return in;
}

std::ostream &operator<<(std::ostream &out, const Box &obj) {
    out << "Padding: ";
    for (int i = 0; i < 4; i++) {
        out << obj.padding[i] << " ";
    }

    out << "\n";

    out << "Margin: ";
    for (int i = 0; i < 4; i++) {
        out << obj.margin[i] << " ";
    }

    out << "\n";
    out << "Border: " << obj.border << "\n";

    out << "Aspect ratio: " << obj.aspectRatio << "\n";

    return out;
}