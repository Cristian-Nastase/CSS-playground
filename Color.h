#ifndef COLOR_H
#define COLOR_H

#include <map>
#include <string>
#include <iostream>

class Color {
private:
    static int noColors;
    const int id;
    static const std::map<char, std::string> colorMap;
    char currentColor;
    float opacity;

    static void resetColor();
public:
    Color();
    Color(char currentColor, float opacity);
    Color(const Color& obj);
    Color& operator=(const Color& obj);
    ~Color() = default;

    char getCurrentColor() const;
    float getOpacity() const;

    void setCurrentColor(char color);

    friend std::istream& operator>>(std::istream& in, Color& obj);
    friend std::ostream& operator<<(std::ostream& out, const Color& obj);

    void printColored(const std::string& text) const;
};

#endif