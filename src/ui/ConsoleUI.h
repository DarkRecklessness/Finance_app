#ifndef CONSOLEUI_H
#define CONSOLEUI_H
#include <memory>
#include <vector>


class IAccountFacade;
class ICategoryFacade;
class IOperationFacade;
class Operation;
class IAnalyticsFacade;

class ConsoleUI {
private:
    std::shared_ptr<IAccountFacade> account_facade_;
    std::shared_ptr<ICategoryFacade> category_facade_;
    std::shared_ptr<IOperationFacade> operation_facade_;
    std::shared_ptr<IAnalyticsFacade> analytics_facade_;

    void ShowMainMenu();
    void ShowAccountsMenu();
    void ShowCategoriesMenu();
    void ShowOperationsMenu();
    void ShowAnalyticsMenu();

    void HandleAccountsChoice();
    void HandleCategoriesChoice();
    void HandleOperationsChoice();
    void HandleAnalyticsChoice();

    // === CRUD Operations ===
    // -- BankAccount Handlers --
    void HandleCreateAccount();
    void HandleListAccounts();
    void HandleUpdateAccountName();
    void HandleRemoveAccount();

    // -- Category Handlers --
    void HandleCreateCategory();
    void HandleListCategories();
    void HandleUpdateCategoryName();
    void HandleRemoveCategory();

    // -- Operation Handlers --
    void HandleAddIncome();
    void HandleAddExpense();
    void HandleListAllOperations();
    void HandleListOperationsForAccount();
    void HandleUpdateOperation();
    void HandleRemoveOperation();

    void PrintOperationsTable(const std::vector<std::shared_ptr<const Operation>>& operations);

public:
    explicit ConsoleUI(
        std::shared_ptr<IAccountFacade> acc_facade,
        std::shared_ptr<ICategoryFacade> cat_facade,
        std::shared_ptr<IOperationFacade> op_facade,
        std::shared_ptr<IAnalyticsFacade> analytics_facade
    );

    void Run();
};


#endif //CONSOLEUI_H
