#ifndef CREATEACCOUNTCOMMAND_H
#define CREATEACCOUNTCOMMAND_H
#include "ICommand.h"
#include "../facades/IAccountFacade.h"
#include <string>
#include <memory>

class CreateAccountCommand : public ICommand {
private:
    std::shared_ptr<IAccountFacade> facade_;
    std::string account_name_;

public:
    CreateAccountCommand(std::shared_ptr<IAccountFacade> facade, std::string name)
        : facade_(std::move(facade)), account_name_(std::move(name)) {}

    bool Execute() override {
        return facade_->CreateAccount(account_name_);
    }
};


#endif //CREATEACCOUNTCOMMAND_H
