#ifndef OPERATIONSERVICE_H
#define OPERATIONSERVICE_H
#include <unordered_map>
#include "../core/ISubject.h"
#include "../domain/Operation.h"
#include "../repository/IRepository.h"

class OperationService : public ISubject<Operation> {
private:
    std::shared_ptr<IRepository<Operation>> operation_repo_;
    // for every account_id store list of accounts which should be notified about operation
    std::unordered_map<int, std::vector<std::shared_ptr<IObserver<Operation>>>> subscribers_;

public:
    explicit OperationService(std::shared_ptr<IRepository<Operation>> op_repo);

    void Attach(int account_id, std::shared_ptr<IObserver<Operation>> observer) override;
    void Detach(int account_id, std::shared_ptr<IObserver<Operation>> observer) override;
    void NotifyOnAdd(int account_id, const Operation& data) override;
    void NotifyOnDelete(int account_id, const Operation& data) override;

    void AddOperation(std::unique_ptr<Operation> operation);
    void RemoveOperation(int operation_id);
};


#endif //OPERATIONSERVICE_H
