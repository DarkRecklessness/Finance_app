#ifndef OPERATIONBUILDER_H
#define OPERATIONBUILDER_H
#include "Operation.h"

class OperationBuilder {
private:
    // accumulative fields
    // require
    int id_;
    OperationType type_;
    std::optional<int> bank_account_id_;
    std::optional<double> amount_;
    std::optional<int> category_id_;
    std::optional<std::chrono::year_month_day> date_;
    // optional
    std::optional<std::string> description_;

public:
    OperationBuilder(int id, OperationType type);

    OperationBuilder& SetAccountId(int account_id);
    OperationBuilder& SetAmount(double amount);
    OperationBuilder& SetCategoryId(int category_id);
    OperationBuilder& SetDate(const std::chrono::year_month_day& date);
    OperationBuilder& SetDescription(const std::string& description);

    Operation Build();
};


#endif //OPERATIONBUILDER_H
