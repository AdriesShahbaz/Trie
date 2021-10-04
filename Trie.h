//
// Created by adries on 2021-03-23.
//

#ifndef TRIE_TRIE_H
#define TRIE_TRIE_H

#define CHARACTERS 26
#include <string>
#include "Node.h"

class Trie {
private:
    Node *_root; // The root node of the Trie
    unsigned int _numberOfWords; // The number of words in the Trie

public:
    Trie();

    ~Trie();

    Node* getRoot() const; // Return the root Node

    void newRoot(); // Create a new root Node

    unsigned int getNumberOfWords() const; // Return the number of words in the Trie

    void increaseNumberOfWords(); // Increases the number of words in the Trie

    void decreaseNumberOfWords(); // Decreases the number of words in the Trie

    void setNumberOfWords(unsigned int const newSize); // Sets the number of words in the Trie

    bool isEmpty() const; // Checks to see if the Trie is empty

    bool isNoChildren(const Node *curr) const; // Checks to see if a Node has any children

    bool isInvalidChar(const unsigned int i) const; // Checks to see if a character is invalid

    void insertWord(Node *curr, const std::string word, unsigned int pos, bool &res); // Inserts a word into the Trie

    void searchWord(Node *curr, const std::string word, std::string &recursiveWord, unsigned int pos) const; // Searches for a word in the Trie

    Node * deleteWord(Node *curr, const std::string word, unsigned int pos, bool &res); // Deletes a word from the Trie

    void print(Node *curr, std::string &recursiveWord, std::string &output);

    void findNode(Node *curr, Node *&foundNode, const std::string prefix, std::string &rootWord,  unsigned int pos) const; // Returns the node of the Prefix

    void clear(Node *curr); // Removes all Nodes from Trie (including root)
};

#endif //TRIE_TRIE_H
