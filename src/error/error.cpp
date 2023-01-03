//
// Created by 20580 on 2023/1/3.
//

#include "error/error.h"

template<class T>
ErrorOrSuccess::ErrorOrSuccess(int statue, T value) :
            statue(statue), value(new Data<T>(value)){}

template<class T> ErrorOrSuccess::ErrorOrSuccess(const ErrorOrSuccess &v)
        : statue(v.statue), value(v.value){}

template<class T>
T ErrorOrSuccess::as() {
    return *dynamic_cast<Data<T>*>(value.get())->value;
}

void exitWithErrorCode(const ErrorOrSuccess& res, std::ostream& out) {
//    std::string v = res.as<std::string>();
    out << "Error Code: " << res.code() << "\n";
}