#ifndef INMEMORYSTORAGE_H
#define INMEMORYSTORAGE_H
#include "IStorage.h"


class InMemoryStorage : public IStorage {
private:
    // private ctor for singletone pattern
    InMemoryStorage() = default;
    std::unordered_map<int, std::shared_ptr<BankAccount>> bank_accounts_;
    std::unordered_map<int, std::shared_ptr<Category>> categories_;
    std::unordered_map<int, std::shared_ptr<Operation>> operations_;

public:
    static InMemoryStorage& GetInstance();

    // forbid copying and assigment for singletone pattern
    InMemoryStorage(const InMemoryStorage&) = delete;
    InMemoryStorage& operator=(const InMemoryStorage&) = delete;

    std::unordered_map<int, std::shared_ptr<BankAccount>>&
        GetBankAccounts() override;
    std::unordered_map<int, std::shared_ptr<Category>>&
        GetCategories() override;
    std::unordered_map<int, std::shared_ptr<Operation>>&
        GetOperations() override;
};


#endif //INMEMORYSTORAGE_H
