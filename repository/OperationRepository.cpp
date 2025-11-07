#include "OperationRepository.h"

OperationRepository::OperationRepository(IStorage& storage)
    : storage_(storage) {}

std::optional<std::shared_ptr<Operation>> OperationRepository::FindById(int id) const {
    auto& map = storage_.GetOperations();
    auto it = map.find(id);

    if (it == map.end()) {
        return std::nullopt;
    }

    return it->second;
}

std::vector<std::shared_ptr<Operation>> OperationRepository::GetAll() const {
    auto& map = storage_.GetOperations();
    std::vector<std::shared_ptr<Operation>> res;
    res.reserve(map.size());

    for (auto& [id, ptr] : map) {
        res.push_back(ptr);
    }

    return res;
}

void OperationRepository::Add(std::unique_ptr<Operation> element) {
    auto& map = storage_.GetOperations();
    map[element->Id()] = std::move(element);
}

void OperationRepository::Remove(int id) {
    auto& map = storage_.GetOperations();
    map.erase(id);
}