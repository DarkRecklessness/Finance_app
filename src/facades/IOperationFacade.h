#ifndef IOPERATIONFACADE_H
#define IOPERATIONFACADE_H
#include <string>
#include <vector>
#include <memory>
#include <optional>
#include <chrono>

class Operation;

class IOperationFacade {
public:
    virtual ~IOperationFacade() = default;

    virtual bool AddIncome(int account_id, int category_id, double amount,
                           const std::chrono::year_month_day& date,
                           const std::optional<std::string>& description) = 0;

    virtual bool AddExpense(int account_id, int category_id, double amount,
                            const std::chrono::year_month_day& date,
                            const std::optional<std::string>& description) = 0;

    virtual bool UpdateOperation(int operation_id, int new_account_id, int new_category_id,
                                 double new_amount, const std::chrono::year_month_day& new_date,
                                 const std::optional<std::string>& new_description) = 0;

    virtual bool RemoveOperation(int operation_id) = 0;

    virtual std::optional<std::shared_ptr<const Operation>> GetOperation(int operation_id) const = 0;
    virtual std::vector<std::shared_ptr<const Operation>> GetAllOperations() const = 0;
    virtual std::vector<std::shared_ptr<const Operation>> GetOperationsForAccount(int account_id) const = 0;

    virtual std::string GetLastErrorMessage() const = 0;
};


#endif //IOPERATIONFACADE_H
