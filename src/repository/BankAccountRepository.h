#ifndef BANKACCOUNTREPOSITORY_H
#define BANKACCOUNTREPOSITORY_H
#include "IRepository.h"
#include "../storage/IStorage.h"
#include "../domain/BankAccount.h"

class BankAccountRepository : public IRepository<BankAccount> {
private:
    IStorage& storage_;

public:
    explicit BankAccountRepository(IStorage& storage);
    std::optional<std::shared_ptr<BankAccount>> FindById(int id) const override;
    std::vector<std::shared_ptr<BankAccount>> GetAll() const override;
    void Add(std::unique_ptr<BankAccount> element) override; // transfer of ownership
    void Remove(int id) override;
};

#endif //BANKACCOUNTREPOSITORY_H
