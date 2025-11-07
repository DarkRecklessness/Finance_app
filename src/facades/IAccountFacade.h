#ifndef IACCOUNTFACADE_H
#define IACCOUNTFACADE_H
#include <string>
#include <vector>
#include <memory>
#include <optional>

class BankAccount;

class IAccountFacade {
public:
    virtual ~IAccountFacade() = default;

    virtual bool CreateAccount(const std::string& name) = 0;
    virtual bool UpdateAccountName(int account_id, const std::string& new_name) = 0;
    virtual bool RemoveAccount(int account_id) = 0;
    virtual std::optional<std::shared_ptr<BankAccount>> GetAccount(int account_id) const = 0;
    virtual std::vector<std::shared_ptr<BankAccount>> GetAllAccounts() const = 0;
    virtual std::string GetLastErrorMessage() const = 0;
};


#endif //IACCOUNTFACADE_H
