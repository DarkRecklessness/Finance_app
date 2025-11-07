#include "OperationBuilder.h"

OperationBuilder::OperationBuilder(int id, OperationType type)
    : id_(id), type_(type) {}

OperationBuilder& OperationBuilder::SetAccountId(int account_id) {
    bank_account_id_ = account_id;
    return *this;
}

OperationBuilder& OperationBuilder::SetAmount(double amount) {
    if (amount < 0) {
        throw std::invalid_argument("Operation amount must be a positive number.");
    }
    amount_ = amount;
    return *this;
}

OperationBuilder& OperationBuilder::SetCategoryId(int category_id) {
    category_id_ = category_id;
    return *this;
}

OperationBuilder& OperationBuilder::SetDate(const std::chrono::year_month_day& date) {
    if (!date.ok()) {
        throw std::invalid_argument("Invalid date provided.");
    }
    date_ = date;
    return *this;
}

OperationBuilder& OperationBuilder::SetDescription(const std::string& description) {
    description_ = description;
    return *this;
}

Operation OperationBuilder::Build() {
    if (!bank_account_id_ || !amount_ || !category_id_ || !date_) {
        throw std::runtime_error("Failed to build Operation: Not all required fields were set.");
    }

    return {id_, type_, *bank_account_id_, *amount_,
                     *category_id_, *date_, description_};
}