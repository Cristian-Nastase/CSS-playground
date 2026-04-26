#include <iostream>
#include <map>
#include <vector>
#include <limits>

#include "BlockElement.h"
#include "Element.h"
#include "Box.h"
#include "Color.h"
#include "InlineElement.h"
#include "Selector.h"


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

void Menu::printGoodbye() {
    BlockElement element("Goodbye!", "", "", true);
    Color* color = new Color('R', 1.0);
    element.setColor(color);
    element.render();
}

void Menu::run() {
    while (true) {
        std::cout<<"\n~ Welcome to CSS playground ~\n";
        std::cout<<"0. Exit\n";
        std::cout<<"1. Enter the playground\n";
        std::cout<<"2. Description\n\n";

        int option;
        std::cout<<"-> ";
        std::cin>>option;
        std::cin.ignore();

        switch (option) {
            case 0:
                printGoodbye();
                return;
            case 1:
                playgroundMenu();
                break;
            case 2:
                descriptionMenu();
                break;
            default:
                std::cout<<"Invalid option, try again. \n";
        }
    }
}

void Menu::playgroundMenu() {
    while (true) {
        std::cout<<"\n~ Playground ~\n";
        std::cout<<"0. Exit\n";
        std::cout<<"1. Elements\n";
        std::cout<<"2. Selector\n";
        std::cout<<"3. Print elements\n";

        std::cout<<"\n-> ";
        int option;
        std::cin>>option;
        std::cin.ignore();

        switch (option) {
            case 0:
                return;
            case 1:
                elementsMenu();
                break;
            case 2:
                selectorMenu();
                break;
            case 3:
                selectorObj.printElements();
                break;
            default:
                std::cout<<"Invalid option, try again.\n";
        }
    }
}

void Menu::descriptionMenu() {
    std::cout<<"\n~ Description ~\n";
    std::cout<<"\nThis project aims to simulate the rendering of a basic paragraph element, with it's box model and color contained in it.\nIt also has the feature to modify parts of the styling by class or id selectors.\n";
}

void Menu::removeElementsMenu() {
    selectorObj.listElements();

    if (selectorObj.getVectorSize() == 0) {
        return;
    }

    while (true) {
        std::cout<<"\nWhich element do you want to remove? -> ";
        int option;
        std::cin>>option;
        std::cin.ignore();

        if (!option || option < 0 || option > selectorObj.getVectorSize()) {
            std::cout<<"Not a valid option, try again.\n";
            continue;
        }

        selectorObj.removeElement(option - 1);
        return;
    }
}

void Menu::createOrDuplicateMenu() {
    while (true) {
        std::cout<<"\n~ Elements ~ \n";
        std::cout<<"0. Exit\n";
        std::cout<<"1. Create new element\n";
        std::cout<<"2. Duplicate already existing element\n";

        std::cout<<"\n -> ";
        int option;
        std::cin>>option;

        switch (option) {
            case 0:
                return;
            case 1:
                createElementsMenu();
                break;
            case 2:
                duplicateMenu();
                break;
            default:
                std::cout<<"Invalid option, try again\n";
        }
    }
}

void Menu::createElementsMenu() {
    while (true) {
        std::cout<<"\nWhat type of element do you want to create? ->";
        std::cout<<"\n0. Block";
        std::cout<<"\n1. Inline\n";
        std::cout<<"-> ";
        int option;
        std::cin>>option;
        std::cin.ignore();

        if (option != 0 && option != 1) {
            std::cout<<"Not a valid option, try again.\n";
            continue;
        }

        selectorObj.createElement(option);
        return;
    }
}

void Menu::duplicateMenu() {
    selectorObj.listElements();

    if (selectorObj.getVectorSize() == 0) {
        return;
    }

    while (true) {
        std::cout<<"\nWhich element do you want to clone? -> ";
        int option;
        std::cin>>option;
        std::cin.ignore();

        if (!option || option < 0 || option > selectorObj.getVectorSize()) {
            std::cout<<"Not a valid option, try again.\n";
            continue;
        }

        selectorObj.copyElement(option - 1);
        return;
    }
}

void Menu::elementsMenu() {
    while (true) {
        std::cout<<"\n~ Elements ~ \n";
        std::cout<<"0. Exit\n";
        std::cout<<"1. Create element\n";
        std::cout<<"2. List elements\n";
        std::cout<<"3. Remove element\n";

        std::cout<<"\n -> ";
        int option;
        std::cin>>option;

        switch (option) {
            case 0:
                return;
            case 1:
                createOrDuplicateMenu();
                break;
            case 2:
                selectorObj.listElements();
                break;
            case 3:
                removeElementsMenu();
                break;
            default:
                std::cout<<"Invalid option, try again\n";
        }
    }
}

Color* Menu::readColor() {
    Color* color = new Color;
    std::cin>>*color;
    return color;
}

Box* Menu::readBox() {
    Box* box = new Box;
    std::cin>>*box;
    return box;
}

void Menu::valueMenu() {
    std::vector<Element*> elements = selectorObj.returnTargetedElements();

    if (elements.empty()) {
        std::cout<<"\n! No elements targeted.\n";
        return;
    }

    for (int i = 0; i < elements.size(); i++) {
        std::cout<<"\n- Element "<<i+1<<": \n\n"<<*elements[i]<<"\n";
    }

    while (true) {
        std::cout<<"\nWhat do you want to change?\n";
        std::cout<<"0. Nothing\n";
        std::cout<<"1. Box Model\n";
        std::cout<<"2. Color\n";

        std::cout<<" -> ";
        int option;
        std::cin>>option;
        std::cin.ignore();
        std::cout<<"\n";

        switch (option) {
            case 0:
                return;
            case 1: {
                Box* readBox = this->readBox();
                for (int i = 0; i < elements.size(); i++) {
                    Box* elementBox = new Box;
                    *elementBox = *readBox;
                    elements[i]->setBox(elementBox);
                }
                delete readBox;
                break;
            }
            case 2: {
                Color* readColor = this->readColor();
                for (int i = 0; i < elements.size(); i++) {
                    Color* elementColor = new Color;
                    *elementColor = *readColor;
                    elements[i]->setColor(elementColor);
                }
                delete readColor;
                break;
            }


        }
    }
}

void Menu::selectorMenu() {
    while (true) {
        std::cout<<"\n~ Selector ~\n";
        std::cout<<"0. Exit\n";
        std::cout<<"1. View string\n";
        std::cout<<"2. Change string\n";
        std::cout<<"3. View elements affected\n";
        std::cout<<"4. Change values\n";

        std::cout<<"\n-> ";
        int option;
        std::cin>>option;
        std::cin.ignore();

        switch (option) {
            case 0:
                return;
            case 1:
                std::cout<<"\nSelector: "<<selectorObj.getSelectorString()<<" (selector type: ";
                switch (selectorObj.getType()) {
                    case 'C':
                            std::cout<<"Class";
                            break;
                    case 'I':
                            std::cout<<"Id";
                            break;
                    default:
                            std::cout<<"*";
                }
                std::cout<<")\n";
                break;
            case 2:
                std::cin>>selectorObj;
                break;
            case 3: {
                std::vector<Element*> elements = selectorObj.returnTargetedElements();

                if (elements.empty()) {
                    std::cout<<"\n! No elements targeted.\n";
                    break;
                }

                for (int i = 0; i < elements.size(); i++) {
                    std::cout<<"\n- Element "<<i<<": \n"<<*elements[i]<<"\n";
                }
            }
                break;
            case 4:
                valueMenu();
                break;
            default:
                std::cout<<"Invalid option, try again. \n";
        }
    }
}

int main() {
    Menu menu;
    menu.run();
    return 0;
}