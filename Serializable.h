#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <string>

class Serializable {
public:
    virtual std::string serialize() const = 0;
    virtual void deserialize(const std::string& data) = 0;
    virtual ~Serializable() = default;
};

#endif