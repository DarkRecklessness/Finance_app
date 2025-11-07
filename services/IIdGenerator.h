#ifndef IIDGENERATOR_H
#define IIDGENERATOR_H

class IIdGenerator {
public:
    virtual ~IIdGenerator() = default;
    virtual int GetNextId() = 0;
};

#endif //IIDGENERATOR_H
