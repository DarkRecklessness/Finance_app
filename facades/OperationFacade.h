#ifndef OPERATIONFACADE_H
#define OPERATIONFACADE_H
#include "IOperationFacade.h"
#include "../repository/IRepository.h"
#include "../services/IIdGenerator.h"
#include "../services/OperationService.h"

class OperationFacade : public IOperationFacade {
private:
    std::shared_ptr<IRepository<Operation>> operation_repo_;
    std::shared_ptr<IIdGenerator> id_generator_;
    std::shared_ptr<OperationService> operation_service_;

    mutable std::string last_error_message_;

    bool AddOperation(int account_id, int category_id, double amount,
                   const std::chrono::year_month_day& date,
                   const std::optional<std::string>& description, OperationType type);

public:
    explicit OperationFacade(
        std::shared_ptr<IRepository<Operation>> operation_repo,
        std::shared_ptr<IIdGenerator> id_generator,
        std::shared_ptr<OperationService> operation_service
    );

    bool AddIncome(int account_id, int category_id, double amount,
                   const std::chrono::year_month_day& date,
                   const std::optional<std::string>& description) override;

    bool AddExpense(int account_id, int category_id, double amount,
                    const std::chrono::year_month_day& date,
                    const std::optional<std::string>& description) override;

    bool UpdateOperation(int operation_id, int new_account_id, int new_category_id,
                         double new_amount, const std::chrono::year_month_day& new_date,
                         const std::optional<std::string>& new_description) override;

    bool RemoveOperation(int operation_id) override;

    std::optional<std::shared_ptr<const Operation>> GetOperation(int operation_id) const override;
    std::vector<std::shared_ptr<const Operation>> GetAllOperations() const override;
    std::vector<std::shared_ptr<const Operation>> GetOperationsForAccount(int account_id) const override;

    std::string GetLastErrorMessage() const override;
};


#endif //OPERATIONFACADE_H
