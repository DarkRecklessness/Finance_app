#ifndef INCOMEEXPENSEDIFFERENCESTRATEGY_H
#define INCOMEEXPENSEDIFFERENCESTRATEGY_H
#include "IAnalyticsStrategy.h"
#include "../domain/Operation.h"

class IncomeExpenseDifferenceStrategy : public IAnalyticsStrategy {
public:
    std::string Generate(
        const std::vector<std::shared_ptr<const Operation>>& operations,
        const IRepository<Category>& category_repo) const override {

        double total_income = 0.0;
        double total_expense = 0.0;

        for (const auto& op : operations) {
            if (op->Type() == OperationType::INCOME) {
                total_income += op->Amount();
            } else {
                total_expense += op->Amount();
            }
        }

        std::string report = "--- Income/Expense Report ---\n";
        report += "Total Income: " + std::to_string(total_income) + '\n';
        report += "Total Expense: " + std::to_string(total_expense) + '\n';
        report += "Difference: " + std::to_string(total_income - total_expense) + '\n';
        return report;
    }
};


#endif //INCOMEEXPENSEDIFFERENCESTRATEGY_H
