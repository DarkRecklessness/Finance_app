#ifndef CATEGORYFACADE_H
#define CATEGORYFACADE_H
#include "ICategoryFacade.h"
#include "../repository/IRepository.h"
#include "../services/DomainEntityFactory.h"
#include "../services/IIdGenerator.h"

class Category;
class Operation;

class CategoryFacade : public ICategoryFacade {
private:
    std::shared_ptr<IRepository<Category>> category_repo_;
    std::shared_ptr<IRepository<Operation>> operation_repo_;
    std::shared_ptr<DomainEntityFactory> entity_factory_;
    std::shared_ptr<IIdGenerator> id_generator_;

    std::weak_ptr<IOperationFacade> operation_facade_;
    mutable std::string last_error_message_;

    const int UNCATEGORIZED_ID = 1;

public:
    explicit CategoryFacade(
        std::shared_ptr<IRepository<Category>> category_repo,
        std::shared_ptr<IRepository<Operation>> operation_repo,
        std::shared_ptr<DomainEntityFactory> entity_factory,
        std::shared_ptr<IIdGenerator> id_generator
    );

    void SetOperationFacade(std::shared_ptr<IOperationFacade> op_facade) override;
    void Initialize() override;
    bool CreateCategory(const std::string& name) override;
    bool UpdateCategoryName(int category_id, const std::string& new_name) override;
    bool RemoveCategory(int category_id) override;
    std::optional<std::shared_ptr<Category>> GetCategory(int category_id) const override;
    std::vector<std::shared_ptr<Category>> GetAllCategories() const override;
    std::string GetLastErrorMessage() const override;
};


#endif //CATEGORYFACADE_H
