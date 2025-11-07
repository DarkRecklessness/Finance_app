#ifndef DOMAINENTITYFACTORY_H
#define DOMAINENTITYFACTORY_H
#include <string>
#include <memory>
#include "../domain/BankAccount.h"
#include "../domain/Category.h"
#include "../domain/OperationBuilder.h"

class DomainEntityFactory {
public:
    std::unique_ptr<BankAccount> CreateBankAccount(int id, const std::string& name) const;
    std::unique_ptr<Category> CreateCategory(int id, const std::string& name) const;
};

#endif //DOMAINENTITYFACTORY_H
