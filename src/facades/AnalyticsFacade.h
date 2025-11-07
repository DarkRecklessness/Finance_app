#ifndef ANALYTICSFACADE_H
#define ANALYTICSFACADE_H
#include "IAnalyticsFacade.h"
#include "IOperationFacade.h"
#include "unordered_map"

class AnalyticsFacade : public IAnalyticsFacade {
private:
    std::shared_ptr<IOperationFacade> operation_facade_;
    std::shared_ptr<IRepository<Category>> category_repo_;
    std::unordered_map<std::string, std::shared_ptr<IAnalyticsStrategy>> strategies_;

public:
    explicit AnalyticsFacade(
        std::shared_ptr<IOperationFacade> op_facade,
        std::shared_ptr<IRepository<Category>> cat_repo
    );

    void RegisterStrategy(const std::string& key, std::shared_ptr<IAnalyticsStrategy> strategy) override;
    std::vector<std::string> GetAvailableReportKeys() const override;
    std::string GenerateReport(const std::string& key) override;
};



#endif //ANALYTICSFACADE_H
