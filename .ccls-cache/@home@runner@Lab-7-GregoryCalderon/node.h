#ifndef NODE
#define NODE
#include "Info.h"
#include <string>

using namespace std;

class Node {
  public:
    Node(Node *lftPtr=nullptr, Node *rtPtr = nullptr, const Info &data = Info());
    
    friend class Tree;
    
  private: 
    Node *lftPtr = nullptr;
    Node *rtPtr = nullptr;
    Info data;

};

#endif