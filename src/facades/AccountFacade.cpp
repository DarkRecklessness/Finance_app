#include "AccountFacade.h"

AccountFacade::AccountFacade(
    std::shared_ptr<IRepository<BankAccount>> account_repo,
    std::shared_ptr<IRepository<Operation>> operation_repo,
    std::shared_ptr<DomainEntityFactory> entity_factory,
    std::shared_ptr<IIdGenerator> id_generator,
    std::shared_ptr<OperationService> operation_service)
    : account_repo_(std::move(account_repo)),
      operation_repo_(std::move(operation_repo)),
      entity_factory_(std::move(entity_factory)),
      id_generator_(std::move(id_generator)),
      operation_service_(std::move(operation_service))
{}

bool AccountFacade::CreateAccount(const std::string& name) {
    try {
        int new_id = id_generator_->GetNextId();
        auto new_account_ptr = entity_factory_->CreateBankAccount(new_id, name);
        account_repo_->Add(std::move(new_account_ptr));

        auto saved_account = account_repo_->FindById(new_id);
        if (saved_account) {
            operation_service_->Attach(new_id, *saved_account);
        } else {
            throw std::runtime_error("Failed to get account after creation.");
        }

        return true;

    } catch (const std::exception& e) {
        last_error_message_ = e.what();
        return false;
    }
}

bool AccountFacade::UpdateAccountName(int account_id, const std::string& new_name) {
    try {
        if (new_name.empty()){
            throw std::invalid_argument("New account name cannot be empty.");
        }

        auto account_opt = account_repo_->FindById(account_id);
        if (!account_opt) {
            throw std::runtime_error("Account with specified ID not found.");
        }

        (*account_opt)->ChangeName(new_name);
        return true;
    } catch (const std::exception& e) {
        last_error_message_ = e.what();
        return false;
    }
}

bool AccountFacade::RemoveAccount(int account_id) {
    try {
        auto account_to_delete = account_repo_->FindById(account_id);
        if (!account_to_delete) {
            throw std::runtime_error("Account with specified ID not found.");
        }

        auto all_operations = operation_repo_->GetAll();
        std::vector<int> ops_to_delete_idx;
        for (const auto& op : all_operations) {
            if (op->BankAccountId() == account_id) {
                ops_to_delete_idx.push_back(op->Id());
            }
        }
        for (int op_id : ops_to_delete_idx) {
            operation_service_->RemoveOperation(op_id);
        }

        operation_service_->Detach(account_id, *account_to_delete);
        account_repo_->Remove(account_id);

        return true;
    } catch (const std::exception& e) {
        last_error_message_ = e.what();
        return false;
    }
}

std::optional<std::shared_ptr<BankAccount>> AccountFacade::GetAccount(int account_id) const {
    return account_repo_->FindById(account_id);
}

std::vector<std::shared_ptr<BankAccount>> AccountFacade::GetAllAccounts() const {
    return account_repo_->GetAll();
}

std::string AccountFacade::GetLastErrorMessage() const {
    return last_error_message_;
}