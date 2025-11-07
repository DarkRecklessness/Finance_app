#include "OperationFacade.h"
#include "../domain/OperationBuilder.h"

OperationFacade::OperationFacade(
    std::shared_ptr<IRepository<Operation>> operation_repo,
    std::shared_ptr<IIdGenerator> id_generator,
    std::shared_ptr<OperationService> operation_service)
    : operation_repo_(std::move(operation_repo)),
      id_generator_(std::move(id_generator)),
      operation_service_(std::move(operation_service)) {}


bool OperationFacade::AddOperation(int account_id, int category_id, double amount,
                   const std::chrono::year_month_day& date,
                   const std::optional<std::string>& description, OperationType type) {
    try {
        int new_id = id_generator_->GetNextId();

        OperationBuilder builder(new_id, type);
        builder.SetAccountId(account_id)
               .SetCategoryId(category_id)
               .SetAmount(amount)
               .SetDate(date);
        if (description) {
            builder.SetDescription(*description);
        }

        auto op = std::make_unique<Operation>(builder.Build());
        operation_service_->AddOperation(std::move(op));
        return true;

    } catch (const std::exception& e) {
        last_error_message_ = e.what();
        return false;
    }
}

bool OperationFacade::AddIncome(int account_id, int category_id, double amount,
                                const std::chrono::year_month_day& date,
                                const std::optional<std::string>& description) {
    return AddOperation(account_id, category_id, amount, date, description, OperationType::INCOME);
}

bool OperationFacade::AddExpense(int account_id, int category_id, double amount,
                                const std::chrono::year_month_day& date,
                                const std::optional<std::string>& description) {
    return AddOperation(account_id, category_id, amount, date, description, OperationType::EXPENSE);
}

bool OperationFacade::UpdateOperation(int operation_id, int new_account_id, int new_category_id,
                                      double new_amount, const std::chrono::year_month_day& new_date,
                                      const std::optional<std::string>& new_description) {
    try {
        auto old_op = operation_repo_->FindById(operation_id);
        if (!old_op) {
            throw std::runtime_error("Operation to update not found.");
        }
        OperationType type = (*old_op)->Type();

        operation_service_->RemoveOperation(operation_id);

        OperationBuilder builder(operation_id, type);
        builder.SetAccountId(new_account_id)
               .SetCategoryId(new_category_id)
               .SetAmount(new_amount)
               .SetDate(new_date);
        if (new_description) {
            builder.SetDescription(*new_description);
        }

        auto op = std::make_unique<Operation>(builder.Build());
        operation_service_->AddOperation(std::move(op));

        return true;

    } catch (const std::exception& e) {
        last_error_message_ = e.what();
        return false;
    }
}

bool OperationFacade::RemoveOperation(int operation_id) {
    try {
        if (!operation_repo_->FindById(operation_id)) {
            throw std::runtime_error("Operation with this ID not found.");
        }

        operation_service_->RemoveOperation(operation_id);
        return true;

    } catch (const std::exception& e) {
        last_error_message_ = e.what();
        return false;
    }
}

std::optional<std::shared_ptr<const Operation>> OperationFacade::GetOperation(int operation_id) const {
    return operation_repo_->FindById(operation_id);
}

std::vector<std::shared_ptr<const Operation>> OperationFacade::GetAllOperations() const {
    auto all_ops_mutable = operation_repo_->GetAll();
    //return all_ops_mutable;
    return {all_ops_mutable.begin(), all_ops_mutable.end()};
}

std::vector<std::shared_ptr<const Operation>> OperationFacade::GetOperationsForAccount(int account_id) const {
    auto all_ops = operation_repo_->GetAll();
    std::vector<std::shared_ptr<const Operation>> result;
    for (const auto& op : all_ops) {
        if (op->BankAccountId() == account_id) {
            result.push_back(op);
        }
    }
    return result;
}

std::string OperationFacade::GetLastErrorMessage() const {
    return last_error_message_;
}