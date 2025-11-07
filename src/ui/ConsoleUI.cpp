#include "ConsoleUI.h"
#include <iostream>
#include "InputHelper.h"
#include "../facades/IAccountFacade.h"
#include "../facades/IOperationFacade.h"
#include "../facades/ICategoryFacade.h"
#include "../domain/BankAccount.h"
#include "../domain/Category.h"
#include "../domain/Operation.h"
#include "../commands/CreateAccountCommand.h"
#include "../commands/RemoveAccountCommand.h"
#include "../commands/UpdateAccountNameCommand.h"
#include "../facades/IAnalyticsFacade.h"
#include "../commands/GenerateReportCommand.h"
#include "../commands/TimingDecorator.h"


ConsoleUI::ConsoleUI(std::shared_ptr<IAccountFacade> acc_facade,
     std::shared_ptr<ICategoryFacade> cat_facade,
     std::shared_ptr<IOperationFacade> op_facade,
     std::shared_ptr<IAnalyticsFacade> analytics_facade)
         : account_facade_(std::move(acc_facade)),
           category_facade_(std::move(cat_facade)),
           operation_facade_(std::move(op_facade)),
           analytics_facade_(std::move(analytics_facade)) {}


void ConsoleUI::ShowMainMenu() {
    std::cout << "\n=== Main Menu ===" << std::endl;
    std::cout << "1. Manage Accounts" << std::endl;
    std::cout << "2. Manage Categories" << std::endl;
    std::cout << "3. Manage Operations" << std::endl;
    std::cout << "4. Analytics" << std::endl;
    std::cout << "5. Exit" << std::endl;
}

void ConsoleUI::ShowAccountsMenu() {
    std::cout << "\n--- Menu: Manage Accounts ---" << std::endl;
    std::cout << "1. List all accounts" << std::endl;
    std::cout << "2. Create a new account" << std::endl;
    std::cout << "3. Update an account's name" << std::endl;
    std::cout << "4. Remove an account" << std::endl;
    std::cout << "5. Back to Main Menu" << std::endl;
}

void ConsoleUI::ShowCategoriesMenu() {
    std::cout << "\n--- Menu: Manage Categories ---" << std::endl;
    std::cout << "1. List all categories" << std::endl;
    std::cout << "2. Create a new category" << std::endl;
    std::cout << "3. Update a category's name" << std::endl;
    std::cout << "4. Remove a category" << std::endl;
    std::cout << "5. Back to Main Menu" << std::endl;
}

void ConsoleUI::ShowOperationsMenu() {
    std::cout << "\n--- Menu: Manage Operations ---" << std::endl;
    std::cout << "1. List all operations" << std::endl;
    std::cout << "2. List operations for a specific account" << std::endl;
    std::cout << "3. Add an income operation" << std::endl;
    std::cout << "4. Add an expense operation" << std::endl;
    std::cout << "5. Update an operation" << std::endl;
    std::cout << "6. Remove an operation" << std::endl;
    std::cout << "7. Back to Main Menu" << std::endl;
}

void ConsoleUI::Run() {
    bool running = true;
    while(running) {
        ShowMainMenu();
        int choice = InputHelper::ReadInt("Enter your choice: ", 1, 5);
        switch (choice) {
            case 1: HandleAccountsChoice(); break;
            case 2: HandleCategoriesChoice(); break;
            case 3: HandleOperationsChoice(); break;
            case 4: HandleAnalyticsChoice(); break;
            case 5: running = false; break;
            default: break;
        }
    }
    std::cout << "Exiting the program...\n";
}

void ConsoleUI::HandleAccountsChoice() {
    bool in_submenu = true;
    while (in_submenu) {
        ShowAccountsMenu();
        int choice = InputHelper::ReadInt("Enter your choice: ", 1, 5);
        switch (choice) {
            case 1: HandleListAccounts(); break;
            case 2: HandleCreateAccount(); break;
            case 3: HandleUpdateAccountName(); break;
            case 4: HandleRemoveAccount(); break;
            case 5: in_submenu = false; break;
            default: break;
        }
    }
}

void ConsoleUI::HandleCategoriesChoice() {
    bool in_submenu = true;
    while (in_submenu) {
        ShowCategoriesMenu();
        int choice = InputHelper::ReadInt("Enter your choice: ", 1, 5);
        switch (choice) {
            case 1: HandleListCategories(); break;
            case 2: HandleCreateCategory(); break;
            case 3: HandleUpdateCategoryName(); break;
            case 4: HandleRemoveCategory(); break;
            case 5: in_submenu = false; break;
            default: break;
        }
    }
}

void ConsoleUI::HandleOperationsChoice() {
    bool in_submenu = true;
    while (in_submenu) {
        ShowOperationsMenu();
        int choice = InputHelper::ReadInt("Enter your choice: ", 1, 7);
        switch (choice) {
            case 1: HandleListAllOperations(); break;
            case 2: HandleListOperationsForAccount(); break;
            case 3: HandleAddIncome(); break;
            case 4: HandleAddExpense(); break;
            case 5: HandleUpdateOperation(); break;
            case 6: HandleRemoveOperation(); break;
            case 7: in_submenu = false; break;
            default: break;
        }
    }
}

void ConsoleUI::HandleCreateAccount() {
    std::cout << "\n--- Create a New Account ---\n";
    std::string name = InputHelper::ReadString("Enter the account name: ");

    auto command = std::make_unique<CreateAccountCommand>(account_facade_, name);

    if (command->Execute()) {
        std::cout << "Account created successfully!\n";
    } else {
        std::cout << "Error: " << account_facade_->GetLastErrorMessage() << '\n';
    }
}

void ConsoleUI::HandleListAccounts() {
    std::cout << "\n--- List of All Accounts ---\n";
    const auto accounts = account_facade_->GetAllAccounts();

    if (accounts.empty()) {
        std::cout << "No accounts found.\n";
        return;
    }

    const int id_width = 5;
    const int name_width = 20;
    const int balance_width = 15;

    std::cout << "------------------------------------------\n";
    std::cout << std::left
              << std::setw(id_width) << "ID"
              << std::setw(name_width) << "| Name"
              << std::setw(balance_width) << "| Balance" << std::endl;
    std::cout << "------------------------------------------\n";

    for (size_t i = 0; i < accounts.size(); ++i) {
        std::cout << std::left
                  << std::setw(id_width) << i + 1
                  << std::setw(name_width) << ("| " + accounts[i]->Name())
                  << std::setw(balance_width) << ("| " + std::to_string(accounts[i]->Balance())) << std::endl;
    }
    std::cout << "------------------------------------------\n";
}

void ConsoleUI::HandleUpdateAccountName() {
    std::cout << "\n--- Update Account Name ---\n";
    auto accounts = account_facade_->GetAllAccounts();

    if (accounts.empty()) {
        std::cout << "No accounts available to update.\n";
        return;
    }

    HandleListAccounts();

    int choice = InputHelper::ReadInt("Enter your choice: ", 1, static_cast<int>(accounts.size()));
    int account_id_to_update = accounts[choice - 1]->Id();

    std::string new_name = InputHelper::ReadString("Enter the new name for the account: ");

    auto command = std::make_unique<UpdateAccountNameCommand>(account_facade_, account_id_to_update, new_name);

    if (command->Execute()) {
        std::cout << "Account name updated successfully!\n";
    } else {
        std::cout << "Error: " << account_facade_->GetLastErrorMessage() << std::endl;
    }
}

void ConsoleUI::HandleRemoveAccount() {
    std::cout << "\n--- Remove an Account ---\n";
    auto accounts = account_facade_->GetAllAccounts();

    if (accounts.empty()) {
        std::cout << "No accounts available to remove.\n";
        return;
    }

    HandleListAccounts();

    int choice = InputHelper::ReadInt("Enter your choice: ", 1, static_cast<int>(accounts.size()));
    int account_id_to_remove = accounts[choice - 1]->Id();

    std::string confirmation = InputHelper::ReadString(
        "WARNING: This will also remove all related operations. Are you sure? (yes/no): "
    );
    if (confirmation != "yes") {
        std::cout << "Removal cancelled.\n";
        return;
    }

    auto command = std::make_unique<RemoveAccountCommand>(account_facade_, account_id_to_remove);

    if (command->Execute()) {
        std::cout << "Account removed successfully!\n";
    } else {
        std::cout << "Error: " << account_facade_->GetLastErrorMessage() << std::endl;
    }
}

void ConsoleUI::HandleCreateCategory() {
    std::cout << "\n--- Create a New Category ---\n";
    std::string name = InputHelper::ReadString("Enter the category name: ");

    if (category_facade_->CreateCategory(name)) {
        std::cout << "Category created successfully!\n";
    } else {
        std::cout << "Error: " << category_facade_->GetLastErrorMessage() << std::endl;
    }
}

void ConsoleUI::HandleListCategories() {
    std::cout << "\n--- List of All Categories ---\n";
    auto categories = category_facade_->GetAllCategories();

    if (categories.empty()) {
        std::cout << "No categories found.\n";
        return;
    }

    const int id_width = 5;
    const int name_width = 20;

    std::cout << "------------------------------------------\n";
    std::cout << std::left
              << std::setw(id_width) << "ID"
              << std::setw(name_width) << "| Name" << std::endl;
    std::cout << "------------------------------------------\n";

    for (size_t i = 0; i < categories.size(); ++i) {
        std::cout << std::left
                  << std::setw(id_width) << i + 1
                  << std::setw(name_width) << ("| " + categories[i]->Name()) << std::endl;
    }
    std::cout << "------------------------------------------\n";
}

void ConsoleUI::HandleUpdateCategoryName() {
    std::cout << "\n--- Update Category Name ---\n";
    auto categories = category_facade_->GetAllCategories();
    if (categories.empty()) {
        std::cout << "No categories available to update.\n";
        return;
    }

    HandleListCategories();

    int choice = InputHelper::ReadInt("Enter your choice: ", 1, static_cast<int>(categories.size()));
    int category_id_to_update = categories[choice - 1]->Id();

    std::string new_name = InputHelper::ReadString("Enter the new name for the category: ");

    if (category_facade_->UpdateCategoryName(category_id_to_update, new_name)) {
        std::cout << "Category name updated successfully!\n";
    } else {
        std::cout << "Error: " << category_facade_->GetLastErrorMessage() << std::endl;
    }
}

void ConsoleUI::HandleRemoveCategory() {
    std::cout << "\n--- Remove a Category ---\n";
    auto categories = category_facade_->GetAllCategories();
    if (categories.empty()) {
        std::cout << "No categories available to remove.\n";
        return;
    }

    HandleListCategories();

    int choice = InputHelper::ReadInt("Enter your choice: ", 1, static_cast<int>(categories.size()));
    int category_id_to_remove = categories[choice - 1]->Id();

    std::string confirmation = InputHelper::ReadString(
        "WARNING: This will reassign all related operations to 'Uncategorized'. Are you sure? (yes/no): "
    );
    if (confirmation != "yes") {
        std::cout << "Removal cancelled.\n";
        return;
    }

    if (category_facade_->RemoveCategory(category_id_to_remove)) {
        std::cout << "Category removed successfully!\n";
    } else {
        std::cout << "Error: " << category_facade_->GetLastErrorMessage() << std::endl;
    }
}


void ConsoleUI::PrintOperationsTable(const std::vector<std::shared_ptr<const Operation>>& operations) {
    const int id_width = 4;
    const int type_width = 8;
    const int amount_width = 15;
    const int account_name_width = 18;
    const int category_name_width = 19;
    const int desc_width = 20;

    std::cout << "--------------------------------------------------------------------------------\n";
    std::cout << std::left
              << std::setw(id_width) << "ID"
              << std::setw(type_width) << "Type"
              << std::setw(amount_width) << "Amount"
              << std::setw(account_name_width) << "Account name"
              << std::setw(category_name_width) << "Category name"
              << std::setw(desc_width) << "Description" << std::endl;
    std::cout << "--------------------------------------------------------------------------------\n";

    for (size_t i = 0; i < operations.size(); ++i) {
        std::cout << std::left
                  << std::setw(id_width) << i + 1
                  << std::setw(type_width) << (operations[i]->Type() == OperationType::INCOME ? "Income" : "Expense")
                  << std::setw(amount_width) << operations[i]->Amount()
                  << std::setw(account_name_width) << (*account_facade_->GetAccount(operations[i]->BankAccountId()))->Name()
                  << std::setw(category_name_width) << (*category_facade_->GetCategory(operations[i]->CategoryId()))->Name()
                  << std::setw(desc_width) << operations[i]->Description().value_or("-")
                  << std::endl;
    }
    std::cout << "--------------------------------------------------------------------------------\n";
}

void ConsoleUI::HandleListAllOperations() {
    std::cout << "\n--- List of All Operations ---\n";
    auto operations = operation_facade_->GetAllOperations();

    if (operations.empty()) {
        std::cout << "No operations found.\n";
        return;
    }

    PrintOperationsTable(operations);
}

void ConsoleUI::HandleListOperationsForAccount() {
    std::cout << "\n--- List Operations for an Account ---\n";
    auto accounts = account_facade_->GetAllAccounts();

    if (accounts.empty()) {
        std::cout << "No accounts available.\n";
        return;
    }

    std::cout << "Choose an account to view its operations:" << std::endl;
    for (size_t i = 0; i < accounts.size(); ++i) {
        std::cout << i + 1 << ". " << accounts[i]->Name() << std::endl;
    }

    int choice = InputHelper::ReadInt("Enter choice: ", 1, static_cast<int>(accounts.size()));
    int account_id = accounts[choice - 1]->Id();

    auto operations = operation_facade_->GetOperationsForAccount(account_id);

    if (operations.empty()) {
        std::cout << "No operations found for this account.\n";
        return;
    }

    PrintOperationsTable(operations);
}

void ConsoleUI::HandleAddIncome() {
    std::cout << "\n--- Add Income Operation ---\n";
    auto accounts = account_facade_->GetAllAccounts();

    if (accounts.empty()) {
        std::cout << "Error: No accounts available. Please create an account first.\n";
        return;
    }

    std::cout << "Choose an account to add income to:" << std::endl;
    for (size_t i = 0; i < accounts.size(); ++i) {
        std::cout << i + 1 << ". " << accounts[i]->Name() << std::endl;
    }

    int acc_choice = InputHelper::ReadInt("Enter choice: ", 1, static_cast<int>(accounts.size()));
    int account_id = accounts[acc_choice - 1]->Id();

    auto categories = category_facade_->GetAllCategories();

    if (categories.empty()) {
        std::cout << "Error: No categories available. Please create a category first.\n";
        return;
    }

    std::cout << "Choose a category for this income:" << std::endl;
    for (size_t i = 0; i < categories.size(); ++i) {
        std::cout << i + 1 << ". " << categories[i]->Name() << std::endl;
    }

    int cat_choice = InputHelper::ReadInt("Enter choice: ", 1, static_cast<int>(categories.size()));
    int category_id = categories[cat_choice - 1]->Id();

    double amount = InputHelper::ReadDouble("Enter amount: ");
    std::string description_str = InputHelper::ReadString("Enter description (optional): ");
    std::optional<std::string> description = (description_str.empty() ? std::nullopt : std::optional(description_str));
    auto today = std::chrono::floor<std::chrono::days>(std::chrono::system_clock::now());

    if (operation_facade_->AddIncome(account_id, category_id, amount, today, description)) {
        std::cout << "Income operation added successfully!\n";
    } else {
        std::cout << "Error: " << operation_facade_->GetLastErrorMessage() << std::endl;
    }
}

void ConsoleUI::HandleAddExpense() {
    std::cout << "\n--- Add Expense Operation ---\n";
    auto accounts = account_facade_->GetAllAccounts();

    if (accounts.empty()) {
        std::cout << "Error: No accounts available.\n";
        return;
    }

    std::cout << "Choose an account to add expense to:" << std::endl;
    for (size_t i = 0; i < accounts.size(); ++i) {
        std::cout << i + 1 << ". " << accounts[i]->Name() << std::endl;
    }

    int acc_choice = InputHelper::ReadInt("Enter choice: ", 1, static_cast<int>(accounts.size()));
    int account_id = accounts[acc_choice - 1]->Id();

    auto categories = category_facade_->GetAllCategories();
    if (categories.empty()) {
        std::cout << "Error: No categories available.\n";
        return;
    }

    std::cout << "Choose a category for this expense:" << std::endl;
    for (size_t i = 0; i < categories.size(); ++i) {
        std::cout << i + 1 << ". " << categories[i]->Name() << std::endl;
    }

    int cat_choice = InputHelper::ReadInt("Enter choice: ", 1, static_cast<int>(categories.size()));
    int category_id = categories[cat_choice - 1]->Id();

    double amount = InputHelper::ReadDouble("Enter amount: ");
    std::string description_str = InputHelper::ReadString("Enter description (optional): ");
    std::optional<std::string> description = (description_str.empty() ? std::nullopt : std::optional(description_str));
    auto today = std::chrono::floor<std::chrono::days>(std::chrono::system_clock::now());

    if (operation_facade_->AddExpense(account_id, category_id, amount, today, description)) {
        std::cout << "Expense operation added successfully!\n";
    } else {
        std::cout << "Error: " << operation_facade_->GetLastErrorMessage() << std::endl;
    }
}

void ConsoleUI::HandleUpdateOperation() {
    std::cout << "\n--- Update an Operation ---\n";

    HandleListAllOperations();
    auto operations = operation_facade_->GetAllOperations();
    if (operations.empty()) {
        return;
    }

    int idx = InputHelper::ReadInt("Enter the ID of the operation to update: ", 1, static_cast<int>(operations.size()));
    int op_id = operations[idx - 1]->Id();

    std::cout << "Enter new details for the operation:" << std::endl;

    HandleListAccounts();
    auto accounts = account_facade_->GetAllAccounts();
    idx = InputHelper::ReadInt("Enter new account ID: ", 1, static_cast<int>(accounts.size()));
    int new_account_id = accounts[idx - 1]->Id();

    HandleListCategories();
    auto categories = category_facade_->GetAllCategories();
    idx = InputHelper::ReadInt("Enter new category ID: ", 1, static_cast<int>(categories.size()));
    int new_category_id = categories[idx - 1]->Id();

    double new_amount = InputHelper::ReadDouble("Enter new amount: ");
    std::string new_desc_str = InputHelper::ReadString("Enter new description (optional): ");
    std::optional<std::string> new_desc = new_desc_str.empty() ? std::nullopt : std::optional(new_desc_str);
    auto today = std::chrono::floor<std::chrono::days>(std::chrono::system_clock::now());

    if (operation_facade_->UpdateOperation(op_id, new_account_id, new_category_id, new_amount, today, new_desc)) {
        std::cout << "Operation updated successfully!\n";
    } else {
        std::cout << "Error: " << operation_facade_->GetLastErrorMessage() << std::endl;
    }
}

void ConsoleUI::HandleRemoveOperation() {
    std::cout << "\n--- Remove an Operation ---\n";

    HandleListAllOperations();
    auto operations = operation_facade_->GetAllOperations();
    if (operations.empty()) {
        return;
    }

    int idx = InputHelper::ReadInt("Enter the ID of the operation to remove: ", 1, static_cast<int>(operations.size()));
    int op_id = operations[idx - 1]->Id();

    if (operation_facade_->RemoveOperation(op_id)) {
        std::cout << "Operation removed successfully!\n";
    } else {
        std::cout << "Error: " << operation_facade_->GetLastErrorMessage() << std::endl;
    }
}

void ConsoleUI::ShowAnalyticsMenu() {
    std::cout << "\n--- Analytics Menu ---\n";
    auto report_keys = analytics_facade_->GetAvailableReportKeys();
    if (report_keys.empty()) {
        std::cout << "No reports available.\n";

    } else {
        std::cout << "Please choose a report to generate:" << std::endl;
        for (size_t i = 0; i < report_keys.size(); ++i) {
            std::cout << i + 1 << ". " << report_keys[i] << std::endl;
        }
    }

    std::cout << report_keys.size() + 1 << ". Back to Main Menu" << std::endl;
}

void ConsoleUI::HandleAnalyticsChoice() {
    bool in_submenu = true;
    while (in_submenu) {
        auto report_keys = analytics_facade_->GetAvailableReportKeys();
        ShowAnalyticsMenu();

        int choice = InputHelper::ReadInt("Enter your choice: ", 1, static_cast<int>(report_keys.size()) + 1);

        if (choice == report_keys.size() + 1) {
            in_submenu = false;
            continue;
        }

        std::string using_decorator = InputHelper::ReadString(
            "Measure execution time for this report? (yes/no): "
        );
        bool measure_time = (using_decorator == "yes");

        const std::string& chosen_key = report_keys[choice - 1];

        std::unique_ptr<ICommand> command = std::make_unique<GenerateReportCommand>(analytics_facade_, chosen_key);

        if (measure_time) {
            command = std::make_unique<TimingDecorator>(std::move(command));
        }

        command->Execute();
    }
}