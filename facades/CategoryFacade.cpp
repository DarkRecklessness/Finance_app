#include "CategoryFacade.h"
#include "IOperationFacade.h"

CategoryFacade::CategoryFacade(
    std::shared_ptr<IRepository<Category>> category_repo,
    std::shared_ptr<IRepository<Operation>> operation_repo,
    std::shared_ptr<DomainEntityFactory> entity_factory,
    std::shared_ptr<IIdGenerator> id_generator)
    : category_repo_(std::move(category_repo)),
      operation_repo_(std::move(operation_repo)),
      entity_factory_(std::move(entity_factory)),
      id_generator_(std::move(id_generator))
{}

void CategoryFacade::SetOperationFacade(std::shared_ptr<IOperationFacade> op_facade) {
    operation_facade_ = op_facade;
}

void CategoryFacade::Initialize() {
    if (category_repo_->FindById(UNCATEGORIZED_ID)) return;

    int id = id_generator_->GetNextId();
    auto uncategorized = entity_factory_->CreateCategory(id, "Uncategorized");
    category_repo_->Add(std::move(uncategorized));
}

bool CategoryFacade::CreateCategory(const std::string& name) {
    try {
        int new_id = id_generator_->GetNextId();
        auto new_category_ptr = entity_factory_->CreateCategory(new_id, name);
        category_repo_->Add(std::move(new_category_ptr));
        return true;

    } catch (const std::exception& e) {
        last_error_message_ = e.what();
        return false;
    }
}

bool CategoryFacade::UpdateCategoryName(int category_id, const std::string& new_name) {
    try {
        if (new_name.empty()) {
            throw std::invalid_argument("New category name cannot be empty.");
        }
        if (category_id == UNCATEGORIZED_ID) {
            throw std::runtime_error("Cannot edit the default 'Uncategorized' category.");
        }

        auto category_opt = category_repo_->FindById(category_id);
        if (!category_opt) {
            throw std::runtime_error("Category with this ID not found.");
        }

        (*category_opt)->ChangeName(new_name);
        return true;

    } catch (const std::exception& e) {
        last_error_message_ = e.what();
        return false;
    }
}

bool CategoryFacade::RemoveCategory(int category_id) {
    try {
        if (category_id == UNCATEGORIZED_ID) {
            throw std::runtime_error("Cannot remove the default 'Uncategorized' category.");
        }
        if (!category_repo_->FindById(category_id)) {
            throw std::runtime_error("Category with this ID not found.");
        }

        auto op_facade = operation_facade_.lock();
        if (!op_facade) {
            throw std::runtime_error("OperationFacade is not set. Bad config.");
        }

        auto all_operations = operation_repo_->GetAll();
        for (const auto& op : all_operations) {
            if (op->CategoryId() == category_id) {
                bool success = op_facade->UpdateOperation(op->Id(), op->BankAccountId(),
                    UNCATEGORIZED_ID, op->Amount(), op->Date(), op->Description());
                if (!success) {
                    throw std::runtime_error("Failed to update an operation during category removal.");
                }
            }
        }

        category_repo_->Remove(category_id);
        return true;

    } catch (const std::exception& e) {
        last_error_message_ = e.what();
        return false;
    }
}

std::optional<std::shared_ptr<Category>> CategoryFacade::GetCategory(int category_id) const {
    return category_repo_->FindById(category_id);
}

std::vector<std::shared_ptr<Category>> CategoryFacade::GetAllCategories() const {
    return category_repo_->GetAll();
}

std::string CategoryFacade::GetLastErrorMessage() const {
    return last_error_message_;
}