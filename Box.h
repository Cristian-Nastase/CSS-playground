#ifndef BOX_H
#define BOX_H

#include <iostream>
#include <vector>

class Box {
private:
    static int noBoxes;
    const int id;
    std::vector<int> padding;
    std::vector<int> margin;
    int border;

    int width;
    int height;
    double aspectRatio;

    static std::vector<int> returnVector(int value);

    static int readInt(std::istream& in);
public:
    Box();
    Box(const std::vector<int>& padding, const std::vector<int>& margin, int border);
    Box(const Box &obj);
    Box& operator=(const Box &obj);
    ~Box() = default;

    std::vector<int> getPadding() const;
    std::vector<int> getMargin() const;
    int getBorder() const;
    int getWidth() const;
    int getHeight() const;

    void setPadding(const std::vector<int>& padding);
    void setMargin(const  std::vector<int>& margin);
    void setBorder(int border);
    void setTextLength(int textLength);

    void updateWidth(int textLength);
    void updateHeight();
    void updateAspectRatio();

    friend std::istream& operator>>(std::istream& in, Box& obj);
    friend std::ostream& operator<<(std::ostream& out, const Box& obj);
};

#endif