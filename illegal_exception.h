//
// Created by adries on 2021-03-23.
//

#ifndef TRIE_ILLEGAL_EXCEPTION_H
#define TRIE_ILLEGAL_EXCEPTION_H

#include <string>

class illegal_exception {
private:
    std::string _msg; // Message of error
public:
    illegal_exception(const std::string msg);
    std::string getMsg() const; // Return the error message
};

#endif //TRIE_ILLEGAL_EXCEPTION_H
