#include "DomainEntityFactory.h"

std::unique_ptr<BankAccount> DomainEntityFactory::CreateBankAccount(int id, const std::string& name) const {
    if (name.empty()) {
        throw std::invalid_argument("Bank account name cannot be empty.");
    }

    return std::make_unique<BankAccount>(id, name);
}

std::unique_ptr<Category> DomainEntityFactory::CreateCategory(int id, const std::string& name) const {
    if (name.empty()) {
        throw std::invalid_argument("Category name cannot be empty.");
    }

    return std::make_unique<Category>(id, name);
}