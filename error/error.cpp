//
// Created by 20580 on 2023/1/3.
//

#include "error.h"

void exitWithErrorCode(const ErrorOrSuccess& res, std::ostream& out) {
//    std::string v = res.as<std::string>();
    out << "Error Code: " << res.code() << "\n";
}