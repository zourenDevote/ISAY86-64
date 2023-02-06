//
// Created by 20580 on 2023/1/3.
//

#ifndef Y8664_ERROR_H
#define Y8664_ERROR_H

#include <iostream>
#include <memory>

class ErrorOrSuccess {
public:
    template<class T>
    ErrorOrSuccess(int statue, T value) : statue(statue), value(new Data<T>(value)) {}
    template<class T>
    ErrorOrSuccess(const ErrorOrSuccess& v) : statue(v.statue), value(v.value) {}
    [[nodiscard]] int code() const { return statue; };
public:
    template<class V>
    V as() { return dynamic_cast<Data<V>*>(value.get())->value; }
private:
    class Base {
    public:
        virtual ~Base() = default;
    };

    template<class T>
    class Data : public Base {
    public:
        explicit Data(T v) : value(v) {}
        T value;
    };
    std::shared_ptr<Base> value;
    const int statue;
};

void exitWithErrorCode(const ErrorOrSuccess& res, std::ostream& out = std::cout);


#endif //Y8664_ERROR_H
