//
// Created by adries on 2021-03-23.
//

#include "Trie.h"
#include "Node.h"
#include "illegal_exception.h"
#include <iostream>
#define CHARACTERS 26
#define ASCII_OFFSET 97

Trie::Trie() {
    _numberOfWords = 0;
    _root = new Node();
}


Node* Trie::getRoot() const {
    return _root;
}

void Trie::newRoot() {
    _root = new Node();
}

void Trie::increaseNumberOfWords() {
    _numberOfWords++;
}

void Trie::decreaseNumberOfWords() {
    if (_numberOfWords > 0)
        _numberOfWords--;
}

void Trie::setNumberOfWords(const unsigned int newSize) {
    _numberOfWords = newSize;
}

unsigned int Trie::getNumberOfWords() const {
    return _numberOfWords;
}

bool Trie::isNoChildren(const Node *curr) const {
    for (std::size_t i = 0; i < CHARACTERS; ++i) {
        if (curr->getChildNode(i)) {
            return false;
        }
    }
    return true;
}

bool Trie::isEmpty() const {
    if (_numberOfWords > 0) {
        return false;
    }
    return true;
}

bool Trie::isInvalidChar(const unsigned int i) const {
    if (i > 25 || i < 0) {
        return true;
    }
    return false;
}

void Trie::insertWord(Node *curr, const std::string word, unsigned int pos, bool &res) {
    // Keep recursing as long as the word has not reached an end
    if (pos < word.length()) {
        int idx = word[pos] - 'a';
        if (isInvalidChar(idx)) {
            throw illegal_exception("illegal argument");
        }

        // If the letter Mode doesn't exist, create it
        // and increase the size of the current Node
        if (curr->getChildNode(idx) == nullptr ) {
            curr->newChildNode(idx);
            curr->increaseSize();
        }

        insertWord(curr->getChildNode(idx), word, pos + 1, res);
    }

    // Once the word has reached the end
    else {

        // Check for duplicate
        if (curr->isWord() == true) {
            std::cout << "failure" << std::endl;
            res = false;
        }
        else {
            curr->setIsWord(true);
            std::cout << "success" << std::endl;
            res = true;
        }
    }
}

void Trie::searchWord(Node *curr, const std::string word, std::string &recursiveWord, unsigned int pos) const {
    // Keep recursing as long as the word has not reached an end
    if (pos < word.length()) {
        int idx = word[pos] - 'a';
        if (isInvalidChar(idx)) {
            throw illegal_exception("illegal argument");
        }

        // If the character Node exists, add the letter to the recursiveWord
        // and add 1 to pos (depth)
        if (curr->getChildNode(idx) != nullptr) {
            recursiveWord += idx + ASCII_OFFSET;
            pos++;
            searchWord(curr->getChildNode(idx), word, recursiveWord, pos);
        }

        // If the character Node doesn't exist, fails
        else {
            recursiveWord = "not found";
        }
    }

    // If the word reaches the end and that Node is a word, success
    else if (pos == word.length()) {
        if (curr->isWord() == true) {
            recursiveWord = "found " + recursiveWord;
        } else {
            recursiveWord = "not found";
        }
    }
    else {
        recursiveWord = "not found";
    }
}

Node* Trie::deleteWord(Node *curr, const std::string word, unsigned int pos, bool &res) {
    // If the current Node is nullptr, check for illegal argument
    if (curr == nullptr) {
        for (int i = 0; i < word.length(); i++) {
            if (isInvalidChar(word[i] - 'a'))
                throw illegal_exception("illegal argument");
        }
        std::cout << "failure" << std::endl;
        res = false;
    }
    else {
        // Once the recursion reaches the word length
        // Check to see if the Node is a word
        if (pos == word.length()) {
            if (curr->isWord()) {
                curr->setIsWord(false);
                std::cout << "success" << std::endl;
                res = true;
            }
            else {
                std::cout << "failure" << std::endl;
                res = false;
            }

            // If that Node was a leaf, delete the Node
            if (isNoChildren(curr)) {
                curr->decreaseSize();
                delete (curr);
                curr = nullptr;
            }

            return curr;

        }

        int idx = word[pos] - 'a';
        if (isInvalidChar(idx)) {
            throw illegal_exception("illegal argument");
        }

        curr->setChildNode(deleteWord(curr->getChildNode(idx), word, pos + 1, res), idx);

        // If the Node is a leaf, not a word and not the last word in the Trie
        // Delete the Node (usually only enter this case if the previous Node was a leaf
        // which results in a leaving a leaf behind that isn't a word)
        if (isNoChildren(curr) && curr->isWord() == false && getNumberOfWords() > 1) {
            curr->decreaseSize();
            delete (curr);
            curr = nullptr;
        }

        return curr;
    }
    return curr;
}

void Trie::print(Node *currNode, std::string &recursiveWord, std::string &output) {
    if (currNode->isWord()) {
        output += recursiveWord + " ";
    }

    for (std::size_t i = 0; i < CHARACTERS; i++) {
        char character = i + ASCII_OFFSET;
        if (currNode->getChildNode(i)) {
            recursiveWord += character;
            print(currNode->getChildNode(i), recursiveWord, output);
            recursiveWord.pop_back();
        }
    }
}

//void Trie::print(Node *curr, std::string &rootWord, std::string &recursiveWord, std::string &output, unsigned int pos) const {
//    // Once the recursion reaches a words length
//    // Check to see if the Node is a word
//    if (curr->isWord()) {
//        output += recursiveWord + " ";
//
//        // If the word was a leaf, make the recursiveWord
//        // equal to the leafs rootWord
//        if (isNoChildren(curr)) {
//            recursiveWord = rootWord;
//        }
//    }
//
//    std::size_t i = 0;
//
//    for (i; i < CHARACTERS; ++i) {
//        if (curr->getChildNode(i)) {
//
//            // If the Node has more that one child
//            // make the current word the rootWord
//            if (curr->getSize() > 1) {
//                rootWord = recursiveWord;
//            }
//            recursiveWord += i + ASCII_OFFSET;
//            print(curr->getChildNode(i), rootWord, recursiveWord, output, pos + 1);
//        }
//    }
//
//    // Once we finish all of the words for a letter (from root)
//    // we reset the values of rootWord and recursiveWord
//    if (pos == 1) {
//        rootWord = "";
//        recursiveWord = "";
//    }
//}

void Trie::findNode(Node *curr, Node*& foundNode, const std::string prefix, std::string &rootWord, unsigned int pos) const {
    // Keep recursing until we are at the end of the word
    if (pos < prefix.length()) {
        int idx = prefix[pos] - 'a';
        if (isInvalidChar(idx)) {
            throw illegal_exception("illegal argument");
        }
        // Go through the nodes, adding each character to the rootWord
        if (curr->getChildNode(idx) != nullptr) {
            rootWord += idx + ASCII_OFFSET;
            findNode(curr->getChildNode(idx), foundNode, prefix, rootWord, pos + 1);
        }
    }

    // Once we reach the end of the word, we set that Node as the foundNode
    if (pos == prefix.length()) {
        foundNode = curr;
    }
}


void Trie::clear(Node *curr) {

    // If the Node is a leaf delete it and return
    if (isNoChildren(curr)) {
        delete (curr);
        curr = nullptr;
        return;
    }

    // Recursivley loop through Nodes and delete them
    for (std::size_t i = 0; i < CHARACTERS; i++) {
        if (curr->getChildNode(i)) {
            clear(curr->getChildNode(i));
            curr->setChildNode(nullptr, i);
        }
    }
    delete (curr);
}

Trie::~Trie() {
    // Clear from the root
    clear(_root);
}
