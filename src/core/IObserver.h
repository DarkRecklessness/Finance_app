#ifndef IOBSERVER_H
#define IOBSERVER_H

template <typename T>
class IObserver {
public:
    virtual ~IObserver() = default;
    virtual void OnAdd(const T& data) = 0;
    virtual void OnDelete(const T& deleted_data) = 0;
};

#endif //IOBSERVER_H
