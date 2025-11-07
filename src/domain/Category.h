#ifndef CATEGORY_H
#define CATEGORY_H
#include <string>
class Category {
private:
    int id_;
    std::string name_;

public:
    Category(int id, const std::string& name);
    int Id() const;
    const std::string& Name() const;
    void ChangeName(const std::string& new_name);
};


#endif //CATEGORY_H
