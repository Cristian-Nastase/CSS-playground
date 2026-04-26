#ifndef MENU_H
#define MENU_H

#include "Selector.h"
#include "Color.h"
#include "Box.h"

class Menu {
private:
    Selector selectorObj;

    Color* readColor();
    Box* readBox();

    void printGoodbye();
public:
    Menu() = default;
    ~Menu() = default;

    void run();
    void playgroundMenu();
    void descriptionMenu();
    void removeElementsMenu();
    void createOrDuplicateMenu();
    void createElementsMenu();
    void duplicateMenu();
    void elementsMenu();
    void valueMenu();
    void selectorMenu();
};


#endif