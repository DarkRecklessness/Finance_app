#ifndef ISUBJECT_H
#define ISUBJECT_H
#include <memory>

template <typename T>
class IObserver;

template <typename T>
class ISubject {
public:
    virtual ~ISubject() = default;
    virtual void Attach(int id, std::shared_ptr<IObserver<T>> observer) = 0;
    virtual void Detach(int id, std::shared_ptr<IObserver<T>> observer) = 0;
    virtual void NotifyOnAdd(int id, const T& data) = 0;
    virtual void NotifyOnDelete(int id, const T& data) = 0;
};

#endif //ISUBJECT_H
