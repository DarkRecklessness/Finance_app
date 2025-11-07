#include "BankAccountRepository.h"

BankAccountRepository::BankAccountRepository(IStorage& storage)
    : storage_(storage) {}

std::optional<std::shared_ptr<BankAccount>> BankAccountRepository::FindById(int id) const {
    auto& map = storage_.GetBankAccounts();
    auto it = map.find(id);

    if (it == map.end()) {
        return std::nullopt;
    }

    return it->second;
}

std::vector<std::shared_ptr<BankAccount>> BankAccountRepository::GetAll() const {
    auto& map = storage_.GetBankAccounts();
    std::vector<std::shared_ptr<BankAccount>> res;
    res.reserve(map.size());

    for (auto& [id, ptr] : map) {
        res.push_back(ptr);
    }

    return res;
}

void BankAccountRepository::Add(std::unique_ptr<BankAccount> element) {
    auto& map = storage_.GetBankAccounts();
    map[element->Id()] = std::move(element);
}

void BankAccountRepository::Remove(int id) {
    auto& map = storage_.GetBankAccounts();
    map.erase(id);
}