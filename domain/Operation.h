#ifndef OPERATION_H
#define OPERATION_H
#include <string>
#include <chrono>

enum class OperationType {
    INCOME,
    EXPENSE
};

class OperationBuilder;

class Operation {
private:
    int id_;
    OperationType type_;
    int bank_account_id_;
    double amount_;
    std::chrono::year_month_day date_;
    int category_id_;
    std::optional<std::string> description_;

    // only OperationBuilder can call the ctor
    Operation(int id, OperationType type, int account_id,
              double amount, int category_id,
              const std::chrono::year_month_day& date,
              const std::optional<std::string>& description);

    friend class OperationBuilder;

public:
    Operation() = delete;

    int Id() const;
    OperationType Type() const;
    int BankAccountId() const;
    double Amount() const;
    int CategoryId() const;
    const std::chrono::year_month_day& Date() const;
    const std::optional<std::string>& Description() const;
};


#endif //OPERATION_H
