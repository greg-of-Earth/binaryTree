#ifndef TREE
#define TREE
#include "node.h"

#include <string>

using namespace std;

class Tree {
  public:
    Tree(Node *root=nullptr);
    Tree(const Tree& ogTree);
    Tree& operator=(const Tree& ogTree);
    ~Tree();

    void Destroy(Node *&tree);
    void AddNode(const string word);
    void AddNodeHelper(Node*, const string word);
    void PrintTree(bool& isEmpty);
    void PrintTreeHelper(Node*);
    void NodeSearch(const string wrd, bool& isEmpty);
    Node* NodeSearchHelper(Node* &prevFinder, Node* &finder, const string wrd);
    void ExcptHndl();


  private:
    Node *root = nullptr;
};

#endif