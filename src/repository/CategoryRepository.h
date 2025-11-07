#ifndef CATEGORYREPOSITORY_H
#define CATEGORYREPOSITORY_H
#include "IRepository.h"
#include "../storage/IStorage.h"
#include "../domain/Category.h"

class CategoryRepository : public IRepository<Category> {
private:
    IStorage& storage_;

public:
    explicit CategoryRepository(IStorage& storage);
    std::optional<std::shared_ptr<Category>> FindById(int id) const override;
    std::vector<std::shared_ptr<Category>> GetAll() const override;
    void Add(std::unique_ptr<Category> element) override; // transfer of ownership
    void Remove(int id) override;
};

#endif //CATEGORYREPOSITORY_H
