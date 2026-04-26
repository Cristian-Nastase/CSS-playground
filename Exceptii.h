#ifndef EXCEPTII_H
#define EXCEPTII_H

#include <exception>
#include <string>

class ValoareInvalidaException : public std::exception {
    std::string mesaj;
public:
    ValoareInvalidaException(const std::string& mesaj = "A fost introdusa o valoare care nu e naturala.") : mesaj(mesaj) {}

    const char* what() const noexcept override {
        return mesaj.c_str();
    }
};

class VectorInvalidException : public std::exception {
    std::string mesaj;
public:
    VectorInvalidException(const std::string& mesaj = "Vector invalid pentru folosinta") : mesaj(mesaj) {}

    const char* what() const noexcept override {
        return mesaj.c_str();
    }
};

class CuloareInvalidaException : public std::exception {
    std::string mesaj;
public:
    CuloareInvalidaException(const std::string& mesaj = "Nu exista aceasta culoare") : mesaj(mesaj) {}

    const char* what() const noexcept override {
        return mesaj.c_str();
    }
};

class TextInvalidException : public std::exception {
    std::string mesaj;
public:
    TextInvalidException(const std::string& mesaj = "Textul nu este valid") : mesaj(mesaj) { }

    const char* what() const noexcept override {
        return mesaj.c_str();
    }
};

class FisierException : public std::exception {
    std::string mesaj;
public:
    FisierException(const std::string& mesaj = "Fisierul nu poate fi deschis") : mesaj(mesaj) { }

    const char* what() const noexcept override {
        return mesaj.c_str();
    }
};

#endif