#include <iostream>

using namespace std;

class Selector {
    private:
        static int blocksNumber;
        int* specificity;
        char* selectorString;
        bool cascades;
        bool compoundSelector;
    public:
        Selector();
        Selector(char* selectorString, bool cascades);
        Selector(const Selector &selector);
        Selector& operator=(const Selector &selector);
        ~Selector();
};

class Property {
    private:
        static double totalNumber;
        const int line;
        char* name;
        bool affectsRendering;
        int valuesAcceptedNumber;
    public:
        Property();
        Property(char* name, bool affectsRendering);
        Property(char* name, bool affectsRendering, int valuesAcceptedNumber);
        Property(const Property &property);
        Property& operator=(const Property &property);
        ~Property();
};

class Value {
    private:
        float* numericValues;
        char valueType;
        char* measureOfUnit;
        bool multipleValues;
    public:
    Value();
    Value(float* numericValues, char valueType);
    Value(float* numericValues, char valueType, char* measureOfUnit);
    Value(float* numericValues, char valueType, char* measureOfUnit, bool multipleValues);
    Value(const Value& value);
    Value& operator=(const Value& value);
    ~Value();
};

class Function {
    private:
        static int totalNumber;
        const int id;
        const bool inLine;
        char* name;
        int argumentsAccepted;
        char* returnType;
    public:
        Function();
        Function(char* name);
        Function(char* name, int argumentsAccepted, char* returnType);
        Function(char* name, bool inLine, int argumentsAccepted, char* returnType);
        Function(const Function &function);
        Function& operator=(const Function &function);
        ~Function();
};

int main() {

}