//
// Created by adries on 2021-03-26.
//

#include "Node.h"
#include <iostream>

Node::Node() {
    _isWord = false;
    _size = 0;

    // Initialize all of the pointers to nullptr
    for (std::size_t i = 0; i < CHARACTERS; i++) {
        _childNode[i] = nullptr;
    }
}

bool Node::isWord() const {
    return _isWord;
}

void Node::setIsWord(bool const state) {
    _isWord = state;
}

unsigned int Node::getSize() const {
    return _size;
}

void Node::increaseSize() {
    _size++;
}

void Node::decreaseSize() {
    _size--;
}

Node* Node::getChildNode(unsigned int const idx) const {
    return _childNode[idx];
}

void Node::newChildNode(unsigned int const idx) {
    _childNode[idx] = new Node();
}

void Node::setChildNode(Node *const newNode, unsigned int const idx) {
    _childNode[idx] = newNode;
}
