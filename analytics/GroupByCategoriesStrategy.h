#ifndef GROUPBYCATEGORIESSTRATEGY_H
#define GROUPBYCATEGORIESSTRATEGY_H
#include "IAnalyticsStrategy.h"
#include <unordered_map>
#include "../domain/Operation.h"
#include "../domain/Category.h"

class GroupByCategoriesStrategy : public IAnalyticsStrategy {
public:
    std::string Generate(
        const std::vector<std::shared_ptr<const Operation>>& operations,
        const IRepository<Category>& category_repo) const override {

        std::unordered_map<int, double> category_totals;

        for (const auto& op : operations) {
            double amount = ((op->Type() == OperationType::INCOME) ? op->Amount() : -op->Amount());
            category_totals[op->CategoryId()] += amount;
        }

        std::string report = "--- Group by Category Report ---\n";
        for (const auto& [id, amount] : category_totals) {
            auto category_name = category_repo.FindById(id).value()->Name();
            report += category_name + ": " + std::to_string(amount) + '\n';
        }
        return report;
    }
};


#endif //GROUPBYCATEGORIESSTRATEGY_H
