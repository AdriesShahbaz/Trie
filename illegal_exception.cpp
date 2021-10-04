//
// Created by adries on 2021-03-23.
//

#include "illegal_exception.h"

illegal_exception::illegal_exception(const std::string msg) {
    _msg = msg;
}

std::string illegal_exception::getMsg() const {
    return _msg;
}