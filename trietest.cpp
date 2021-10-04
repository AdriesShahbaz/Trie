#include <iostream>
#include <string.h>
#include <string>
#include <boost/algorithm/string.hpp>

#include "Trie.h"
#include "illegal_exception.h"

int main() {
    std::string line;

    Trie t;

    while (true) {
        if (std::cin.eof()) {
            break;
        }

        getline(std::cin, line);

        if (line == "exit") {
            break;
        }

        int pos = line.find(" ");
        std::string cmd = line.substr(0, pos);
        std::string obj = line.substr((pos + 1));

        Node *tmp = t.getRoot();

        if (cmd == "i") {
            try {
                bool res = true;
                t.insertWord(tmp, obj, 0, res);
                // If the insertion was successful
                // increase the number of words in the Trie
                if (res == true) {
                    t.increaseNumberOfWords();
                }
            }
            catch (illegal_exception& e) {
                std::cout << e.getMsg() << std::endl;
            }
        }
        else if (cmd == "e") {
            try {
                bool res = true;
                t.deleteWord(tmp, obj, 0, res);
                // If the deletion was successful
                // decrease the number of words in the Trie
                if (res == true)
                    t.decreaseNumberOfWords();
            }
            catch (illegal_exception& e) {
                std::cout << e.getMsg() << std::endl;
            }
        }
        else if (cmd == "s") {
            try {
                std::string tmpS = "";
                int pos = 0;
                t.searchWord(tmp, obj, tmpS, pos);
                std::cout << tmpS << std::endl;
            }
            catch (illegal_exception& e) {
                std::cout << e.getMsg() << std::endl;
            }
        }
        else if (cmd == "print") {
            std::string recursiveWord = "";
            std::string output = "";
            t.print(tmp, recursiveWord, output);
            boost::trim(output);
            if (output != "") {
                std::cout << output << std::endl;
            }
        }
        else if (cmd == "autocomplete") {
            obj = obj.substr(0, obj.length()-1);
            std::string recursiveWord = "";
            std::string output = "";
            Node *base = nullptr;
            t.findNode(tmp, base, obj, recursiveWord, 0);
            if (base != nullptr) {
                t.print(base, recursiveWord, output);
                boost::trim(output);
                if (output != "") {
                    std::cout << output << std::endl;
                }
            }
        }
        else if (cmd == "empty") {
            std::cout << "empty " << t.isEmpty() << std::endl;
        }
        else if (cmd == "clear") {
            t.clear(tmp);
            t.setNumberOfWords(0); // Reset the number of words to 0
            t.newRoot(); // Since clear removed all Nodes, create a new root Node
            std::cout << "success" << std::endl;
        }
        else if (cmd == "size") {
            std::cout << "number of words is " << t.getNumberOfWords() << std::endl;
        }
        else {
            std::cout << "Not a valid command" << std::endl;
        }
    }
    return 0;
}
