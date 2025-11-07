#include "InMemoryStorage.h"

InMemoryStorage& InMemoryStorage::GetInstance() {
    static InMemoryStorage instance;
    return instance;
}

std::unordered_map<int, std::shared_ptr<BankAccount>>& InMemoryStorage::GetBankAccounts() {
    return bank_accounts_;
}

std::unordered_map<int, std::shared_ptr<Category>>& InMemoryStorage::GetCategories() {
    return categories_;
}

std::unordered_map<int, std::shared_ptr<Operation>>& InMemoryStorage::GetOperations() {
    return operations_;
}