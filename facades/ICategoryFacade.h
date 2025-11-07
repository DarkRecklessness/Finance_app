#ifndef ICATEGORYFACADE_H
#define ICATEGORYFACADE_H
#include <string>
#include <vector>
#include <memory>
#include <optional>

class Category;
class IOperationFacade;

class ICategoryFacade {
public:
    virtual ~ICategoryFacade() = default;

    virtual void SetOperationFacade(std::shared_ptr<IOperationFacade> op_facade) = 0;
    virtual void Initialize() = 0;

    virtual bool CreateCategory(const std::string& name) = 0;
    virtual bool UpdateCategoryName(int category_id, const std::string& new_name) = 0;
    virtual bool RemoveCategory(int category_id) = 0;
    virtual std::optional<std::shared_ptr<Category>> GetCategory(int category_id) const = 0;
    virtual std::vector<std::shared_ptr<Category>> GetAllCategories() const = 0;
    virtual std::string GetLastErrorMessage() const = 0;
};


#endif //ICATEGORYFACADE_H
