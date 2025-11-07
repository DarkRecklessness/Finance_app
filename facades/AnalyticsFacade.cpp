#include "AnalyticsFacade.h"

AnalyticsFacade::AnalyticsFacade(
    std::shared_ptr<IOperationFacade> op_facade,
    std::shared_ptr<IRepository<Category>> cat_repo)
    : operation_facade_(std::move(op_facade)),
      category_repo_(std::move(cat_repo))
{}

void AnalyticsFacade::RegisterStrategy(const std::string& key, std::shared_ptr<IAnalyticsStrategy> strategy) {
    strategies_[key] = std::move(strategy);
}

std::vector<std::string> AnalyticsFacade::GetAvailableReportKeys() const {
    std::vector<std::string> keys;
    keys.reserve(strategies_.size());
    for (const auto& [key, analytic] : strategies_) {
        keys.push_back(key);
    }
    return keys;
}

std::string AnalyticsFacade::GenerateReport(const std::string& key) {
    auto it = strategies_.find(key);
    if (it == strategies_.end()) {
        return "Error: Report with key '" + key + "' not found.";
    }

    auto all_ops = operation_facade_->GetAllOperations();
    return it->second->Generate(all_ops, *category_repo_);
}