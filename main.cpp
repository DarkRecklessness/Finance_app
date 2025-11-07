#include <iostream>
#include <memory>

// Low-level services and memory storage
#include "storage/IStorage.h"
#include "storage/InMemoryStorage.h"
#include "services/IIdGenerator.h"
#include "services/SequentialIdGenerator.h"
#include "services/DomainEntityFactory.h"

// Repositories
#include "repository/IRepository.h"
#include "repository/BankAccountRepository.h"
#include "repository/CategoryRepository.h"
#include "repository/OperationRepository.h"

// Services and analytics
#include "services/OperationService.h"
#include "analytics/GroupByCategoriesStrategy.h"
#include "analytics/IncomeExpenseDifferenceStrategy.h"

// Facades
#include "facades/IAccountFacade.h"
#include "facades/AccountFacade.h"
#include "facades/ICategoryFacade.h"
#include "facades/CategoryFacade.h"
#include "facades/IOperationFacade.h"
#include "facades/OperationFacade.h"
#include "facades/IAnalyticsFacade.h"
#include "facades/AnalyticsFacade.h"

// UI
#include "ui/ConsoleUI.h"

// DI-container
#include "boost/di.hpp"

namespace di = boost::di;

int main() {
    try {
        const auto injector = di::make_injector(
            // Link simple interfaces with implementation
            di::bind<IIdGenerator>.to<SequentialIdGenerator>(),
            di::bind<IRepository<BankAccount>>.to<BankAccountRepository>(),
            di::bind<IRepository<Category>>.to<CategoryRepository>(),
            di::bind<IRepository<Operation>>.to<OperationRepository>(),

            di::bind<IAccountFacade>.to<AccountFacade>(),
            di::bind<IOperationFacade>.to<OperationFacade>(),
            di::bind<IAnalyticsFacade>.to<AnalyticsFacade>(),

            // Cycle-bulding
            di::bind<ICategoryFacade>.to([](const auto& injector) -> std::shared_ptr<ICategoryFacade> {
                auto category_facade = injector.template create<std::shared_ptr<CategoryFacade>>();

                // Create dependency for the category_facade further configuration
                auto operation_facade = injector.template create<std::shared_ptr<IOperationFacade>>();

                category_facade->SetOperationFacade(operation_facade);
                return category_facade;
            }),

            // Link with singltone
            di::bind<IStorage>.to(InMemoryStorage::GetInstance())
        );

        // DI configure ConsoleUI
        auto app = injector.create<ConsoleUI>();

        // System init
        auto category_facade = injector.create<std::shared_ptr<ICategoryFacade>>();
        category_facade->Initialize();

        // Base analytics strategy
        auto analytics_facade = injector.create<std::shared_ptr<IAnalyticsFacade>>();
        analytics_facade->RegisterStrategy("Income and Expense", std::make_shared<IncomeExpenseDifferenceStrategy>());
        analytics_facade->RegisterStrategy("Group by category", std::make_shared<GroupByCategoriesStrategy>());

        app.Run();

    } catch (const std::exception& e) {
        std::cerr << "A critical error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
