#ifndef IANALYTICSSTRATEGY_H
#define IANALYTICSSTRATEGY_H
#include <vector>
#include <memory>
#include <string>
#include "../repository/IRepository.h"

class Operation;
class Category;

class IAnalyticsStrategy {
public:
    virtual ~IAnalyticsStrategy() = default;
    virtual std::string Generate(
        const std::vector<std::shared_ptr<const Operation>>& operations,
        const IRepository<Category>& category_repo) const = 0;
};


#endif //IANALYTICSSTRATEGY_H
