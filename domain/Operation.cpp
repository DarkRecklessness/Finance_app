#include "Operation.h"

Operation::Operation(int id, OperationType type,
        int account_id, double amount, int category_id,
        const std::chrono::year_month_day& date,
        const std::optional<std::string>& description)
            : id_(id),
            type_(type),
            bank_account_id_(account_id),
            amount_(amount),
            category_id_(category_id),
            date_(date),
            description_(description) {}

int Operation::Id() const {
    return id_;
}

OperationType Operation::Type() const {
    return type_;
}

int Operation::BankAccountId() const {
    return bank_account_id_;
}

double Operation::Amount() const {
    return amount_;
}

int Operation::CategoryId() const {
    return category_id_;
}

const std::chrono::year_month_day& Operation::Date() const {
    return date_;
}

const std::optional<std::string>& Operation::Description() const {
    return description_;
}