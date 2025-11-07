#include "BankAccount.h"

BankAccount::BankAccount(int id, const std::string& name)
    : id_(id), name_(name), balance_(0.0) {}

int BankAccount::Id() const {
    return id_;
}

const std::string& BankAccount::Name() const {
    return name_;
}

double BankAccount::Balance() const {
    return balance_;
}

void BankAccount::ChangeName(const std::string& new_name) {
    name_ = new_name;
}

void BankAccount::OnAdd(const Operation& data) {
    if (data.BankAccountId() != Id()) return;

    if (data.Type() == OperationType::INCOME) {
        balance_ += data.Amount();
    } else {
        balance_ -= data.Amount();
    }
}

void BankAccount::OnDelete(const Operation& data) {
    if (data.BankAccountId() != Id()) return;

    if (data.Type() == OperationType::INCOME) {
        balance_ -= data.Amount();
    } else {
        balance_ += data.Amount();
    }
}