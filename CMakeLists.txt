cmake_minimum_required(VERSION 3.28)
project(Finance_App)

set(CMAKE_CXX_STANDARD 20)

add_executable(Finance_App src/main.cpp
        src/domain/BankAccount.cpp
        src/domain/BankAccount.h
        src/core/IObserver.h
        src/core/ISubject.h
        src/domain/Category.cpp
        src/domain/Category.h
        src/domain/Operation.cpp
        src/domain/Operation.h
        src/domain/OperationBuilder.cpp
        src/domain/OperationBuilder.h
        src/repository/IRepository.h
        src/storage/IStorage.h
        src/storage/InMemoryStorage.cpp
        src/storage/InMemoryStorage.h
        src/repository/OperationRepository.cpp
        src/repository/OperationRepository.h
        src/repository/BankAccountRepository.cpp
        src/repository/BankAccountRepository.h
        src/repository/CategoryRepository.cpp
        src/repository/CategoryRepository.h
        src/services/IIdGenerator.h
        src/services/SequentialIdGenerator.h
        src/services/DomainEntityFactory.cpp
        src/services/DomainEntityFactory.h
        src/services/OperationService.cpp
        src/services/OperationService.h
        src/facades/IAccountFacade.h
        src/facades/AccountFacade.cpp
        src/facades/AccountFacade.h
        src/facades/ICategoryFacade.h
        src/facades/CategoryFacade.cpp
        src/facades/CategoryFacade.h
        src/facades/IOperationFacade.h
        src/facades/OperationFacade.cpp
        src/facades/OperationFacade.h
        src/ui/ConsoleUI.cpp
        src/ui/ConsoleUI.h
        src/ui/InputHelper.h
        src/boost/di.hpp
        src/commands/ICommand.h
        src/commands/CreateAccountCommand.h
        src/commands/UpdateAccountNameCommand.h
        src/commands/RemoveAccountCommand.h
        src/analytics/IAnalyticsStrategy.h
        src/analytics/IncomeExpenseDifferenceStrategy.h
        src/analytics/GroupByCategoriesStrategy.h
        src/facades/IAnalyticsFacade.h
        src/facades/AnalyticsFacade.cpp
        src/facades/AnalyticsFacade.h
        src/commands/GenerateReportCommand.h
        src/commands/TimingDecorator.h
)
