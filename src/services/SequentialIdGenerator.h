#ifndef SEQUENTIALIDGENERATOR_H
#define SEQUENTIALIDGENERATOR_H
#include "IIdGenerator.h"

class SequentialIdGenerator : public IIdGenerator {
private:
    int current_id_ = 1;
public:
    int GetNextId() override {
        return current_id_++;
    }
};

#endif //SEQUENTIALIDGENERATOR_H
