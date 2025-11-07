#ifndef ISTORAGE_H
#define ISTORAGE_H
#include <memory>
#include <unordered_map>

class BankAccount;
class Category;
class Operation;

class IStorage {
public:
    virtual ~IStorage() = default;
    virtual std::unordered_map<int, std::shared_ptr<BankAccount>>&
        GetBankAccounts() = 0;
    virtual std::unordered_map<int, std::shared_ptr<Category>>&
        GetCategories() = 0;
    virtual std::unordered_map<int, std::shared_ptr<Operation>>&
        GetOperations() = 0;
};

#endif //ISTORAGE_H
