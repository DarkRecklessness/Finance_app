#ifndef ACCOUNTFACADE_H
#define ACCOUNTFACADE_H
#include "IAccountFacade.h"
#include "../repository/IRepository.h"
#include "../services/DomainEntityFactory.h"
#include "../services/IIdGenerator.h"
#include "../services/OperationService.h"

class AccountFacade : public IAccountFacade {
private:
    std::shared_ptr<IRepository<BankAccount>> account_repo_;
    std::shared_ptr<IRepository<Operation>> operation_repo_;
    std::shared_ptr<DomainEntityFactory> entity_factory_;
    std::shared_ptr<IIdGenerator> id_generator_;
    std::shared_ptr<OperationService> operation_service_;
    mutable std::string last_error_message_;

public:
    explicit AccountFacade(
        std::shared_ptr<IRepository<BankAccount>> account_repo,
        std::shared_ptr<IRepository<Operation>> operation_repo,
        std::shared_ptr<DomainEntityFactory> entity_factory,
        std::shared_ptr<IIdGenerator> id_generator,
        std::shared_ptr<OperationService> operation_service
    );

    bool CreateAccount(const std::string& name) override;
    bool UpdateAccountName(int account_id, const std::string& new_name) override;
    bool RemoveAccount(int account_id) override;
    std::optional<std::shared_ptr<BankAccount>> GetAccount(int account_id) const override;
    std::vector<std::shared_ptr<BankAccount>> GetAllAccounts() const override;
    std::string GetLastErrorMessage() const override;
};


#endif //ACCOUNTFACADE_H
