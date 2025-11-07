#ifndef IANALYTICSFACADE_H
#define IANALYTICSFACADE_H
#include "../analytics/IAnalyticsStrategy.h"

class IAnalyticsFacade {
public:
    virtual ~IAnalyticsFacade() = default;

    virtual void RegisterStrategy(const std::string& key, std::shared_ptr<IAnalyticsStrategy> strategy) = 0;

    virtual std::vector<std::string> GetAvailableReportKeys() const = 0;
    virtual std::string GenerateReport(const std::string& key) = 0;
};


#endif //IANALYTICSFACADE_H
