#ifndef IREPOSITORY_H
#define IREPOSITORY_H
#include <memory>
#include <optional>
#include <vector>


template <typename T>
class IRepository {
public:
    virtual ~IRepository() = default;
    virtual std::optional<std::shared_ptr<T>> FindById(int id) const = 0;
    virtual std::vector<std::shared_ptr<T>> GetAll() const = 0;
    virtual void Add(std::unique_ptr<T> element) = 0; // transfer of ownership
    virtual void Remove(int id) = 0;
};


#endif //IREPOSITORY_H
