#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H
#include <string>
#include "../core/IObserver.h"
#include "Operation.h"


class BankAccount : public IObserver<Operation> {
private:
    int id_;
    std::string name_;
    double balance_;

public:
    BankAccount(int id, const std::string& name);
    int Id() const;
    const std::string& Name() const;
    double Balance() const;
    void ChangeName(const std::string& new_name);
    void OnAdd(const Operation& data) override;
    void OnDelete(const Operation &deleted_data) override;
};


#endif //BANKACCOUNT_H
