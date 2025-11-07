#ifndef TIMINGDECORATOR_H
#define TIMINGDECORATOR_H
#include "ICommand.h"
#include <memory>
#include <chrono>
#include <iostream>


class TimingDecorator : public ICommand {
private:
    std::unique_ptr<ICommand> wrapped_command_;

public:
    explicit TimingDecorator(std::unique_ptr<ICommand> command)
        : wrapped_command_(std::move(command)) {}

    bool Execute() override {
        auto start = std::chrono::high_resolution_clock::now();

        bool result = wrapped_command_->Execute();

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        std::cout << "\n[STATISTICS] Execution time: " << duration.count() << " ms.\n";

        return result;
    }
};


#endif //TIMINGDECORATOR_H
