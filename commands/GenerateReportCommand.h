#ifndef GENERATEREPORTCOMMAND_H
#define GENERATEREPORTCOMMAND_H
#include "ICommand.h"
#include "../facades/IAnalyticsFacade.h"
#include <string>
#include <memory>
#include <iostream>

class GenerateReportCommand : public ICommand {
private:
    std::shared_ptr<IAnalyticsFacade> facade_;
    std::string report_key_;

public:
    GenerateReportCommand(std::shared_ptr<IAnalyticsFacade> facade, const std::string& report_key)
        : facade_(std::move(facade)), report_key_(report_key) {}

    bool Execute() override {
        std::string report = facade_->GenerateReport(report_key_);
        std::cout << "\n--- Report Results ---\n";
        std::cout << report;
        std::cout << "---------------------\n";
        return true;
    }
};


#endif //GENERATEREPORTCOMMAND_H
