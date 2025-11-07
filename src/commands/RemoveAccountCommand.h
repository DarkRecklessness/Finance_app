#ifndef REMOVEACCOUNTCOMMAND_H
#define REMOVEACCOUNTCOMMAND_H
#include "ICommand.h"
#include "../facades/IAccountFacade.h"
#include <memory>

class RemoveAccountCommand : public ICommand {
private:
    std::shared_ptr<IAccountFacade> facade_;
    int account_id_;

public:
    RemoveAccountCommand(std::shared_ptr<IAccountFacade> facade, int account_id)
        : facade_(std::move(facade)), account_id_(account_id) {}

    bool Execute() override {
        return facade_->RemoveAccount(account_id_);
    }
};


#endif //REMOVEACCOUNTCOMMAND_H
