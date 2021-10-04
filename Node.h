//
// Created by adries on 2021-03-26.
//

#ifndef TRIE_NODE_H
#define TRIE_NODE_H

#define CHARACTERS 26

class Node{
private:
    bool _isWord; // Check to see if current node is end of word
    unsigned int _size; // Size of a node (how many childs it has)
    Node *_childNode[CHARACTERS]; // Array of 26 pointers (each representing a character)
public:
    Node();

    bool isWord() const; // Returns the value of _isWord

    void setIsWord(bool const state); // Sets the value of _isWord

    unsigned int getSize() const; // Returns the value of _size

    void decreaseSize(); // Decreases _size

    void increaseSize(); // Increases _size

    Node* getChildNode(unsigned int const idx) const; // Returns the Node at the index

    void newChildNode(unsigned int const idx); // Makes a new Node at the index

    void setChildNode(Node* const newNode, unsigned int const idx); // Sets the Node at the index
};

#endif //TRIE_NODE_H
