#ifndef UPDATEACCOUNTNAMECOMMAND_H
#define UPDATEACCOUNTNAMECOMMAND_H
#include "ICommand.h"
#include "../facades/IAccountFacade.h"
#include <string>
#include <memory>

class UpdateAccountNameCommand : public ICommand {
private:
    std::shared_ptr<IAccountFacade> facade_;
    int account_id_;
    std::string new_name_;

public:
    UpdateAccountNameCommand(std::shared_ptr<IAccountFacade> facade, int account_id, std::string new_name)
        : facade_(std::move(facade)), account_id_(account_id), new_name_(std::move(new_name)) {}

    bool Execute() override {
        return facade_->UpdateAccountName(account_id_, new_name_);
    }
};


#endif //UPDATEACCOUNTNAMECOMMAND_H
