#ifndef OPERATIONREPOSITORY_H
#define OPERATIONREPOSITORY_H
#include "IRepository.h"
#include "../storage/IStorage.h"
#include "../domain/Operation.h"

class OperationRepository : public IRepository<Operation> {
private:
    IStorage& storage_;

public:
    explicit OperationRepository(IStorage& storage);
    std::optional<std::shared_ptr<Operation>> FindById(int id) const override;
    std::vector<std::shared_ptr<Operation>> GetAll() const override;
    void Add(std::unique_ptr<Operation> element) override; // transfer of ownership
    void Remove(int id) override;
};

#endif //OPERATIONREPOSITORY_H
