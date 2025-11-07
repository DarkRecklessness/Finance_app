#include "CategoryRepository.h"

CategoryRepository::CategoryRepository(IStorage& storage)
    : storage_(storage) {}

std::optional<std::shared_ptr<Category>> CategoryRepository::FindById(int id) const {
    auto& map = storage_.GetCategories();
    auto it = map.find(id);

    if (it == map.end()) {
        return std::nullopt;
    }

    return it->second;
}

std::vector<std::shared_ptr<Category>> CategoryRepository::GetAll() const {
    auto& map = storage_.GetCategories();
    std::vector<std::shared_ptr<Category>> res;
    res.reserve(map.size());

    for (auto& [id, ptr] : map) {
        res.push_back(ptr);
    }

    return res;
}

void CategoryRepository::Add(std::unique_ptr<Category> element) {
    auto& map = storage_.GetCategories();
    map[element->Id()] = std::move(element);
}

void CategoryRepository::Remove(int id) {
    auto& map = storage_.GetCategories();
    map.erase(id);
}