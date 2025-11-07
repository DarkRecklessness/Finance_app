#include "Category.h"

Category::Category(int id, const std::string& name)
    : id_(id), name_(name) {}

int Category::Id() const {
    return id_;
}

const std::string& Category::Name() const {
    return name_;
}

void Category::ChangeName(const std::string& new_name) {
    name_ = new_name;
}