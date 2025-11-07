#include "OperationService.h"

#include "../core/IObserver.h"

OperationService::OperationService(std::shared_ptr<IRepository<Operation>> op_repo)
    : operation_repo_(std::move(op_repo)) {}

void OperationService::Attach(int account_id, std::shared_ptr<IObserver<Operation>> observer) {
    subscribers_[account_id].push_back(observer);
}

void OperationService::Detach(int account_id, std::shared_ptr<IObserver<Operation>> observer) {
    if (subscribers_.find(account_id) == subscribers_.end()) {
        return;
    }

    auto& observers = subscribers_[account_id];
    auto it = find(observers.begin(), observers.end(), observer);
    if (it == observers.end()) {
        return;
    }

    observers.erase(it);
}

void OperationService::NotifyOnAdd(int account_id, const Operation& data) {
    if (subscribers_.find(account_id) == subscribers_.end()) {
        return;
    }

    auto& observers = subscribers_[account_id];
    for (const auto& ptr : observers) {
        ptr->OnAdd(data);
    }
}

void OperationService::NotifyOnDelete(int account_id, const Operation& data) {
    if (subscribers_.find(account_id) == subscribers_.end()) {
        return;
    }

    auto& observers = subscribers_[account_id];
    for (const auto& ptr : observers) {
        ptr->OnDelete(data);
    }
}

void OperationService::AddOperation(std::unique_ptr<Operation> operation) {
    int account_id = operation->BankAccountId();
    const auto& data = *operation;

    operation_repo_->Add(std::move(operation));
    NotifyOnAdd(account_id, data);
}

void OperationService::RemoveOperation(int operation_id) {
    auto op_to_delete_opt = operation_repo_->FindById(operation_id);
    if (!op_to_delete_opt) {
        return;
    }

    int account_id = (*op_to_delete_opt)->BankAccountId();
    const auto& data = **op_to_delete_opt;

    operation_repo_->Remove(operation_id);
    NotifyOnDelete(account_id, data);
}