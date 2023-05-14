#include "node.h"
#include "Info.h"

 
Node::Node(Node *l_ptr, Node *r_ptr, const Info &n_data) {
  lftPtr = l_ptr;
  rtPtr=r_ptr;
  data = n_data;
}

