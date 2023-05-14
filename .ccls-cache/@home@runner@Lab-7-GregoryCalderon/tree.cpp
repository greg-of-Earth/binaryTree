#include "tree.h"
#include <iostream>
#include <iomanip>

// constructor 
Tree::Tree(Node *n_root){
  this->root = n_root;
}


//copy constructor 
Tree::Tree(const Tree& ogTree) {
  if(ogTree.root==nullptr){
    this->root=nullptr;
  }else {
    try{
      this->root= new Node(*ogTree.root);
      if(ogTree.root->lftPtr!=nullptr){
        this->root->lftPtr = new Node(*ogTree.root->lftPtr);
      }else if(ogTree.root->rtPtr!=nullptr) {
        this->root->rtPtr = new Node(*ogTree.root->rtPtr);
      }
    }catch(bad_alloc& e){
      ExcptHndl();
    }
  }
}


// copy assignment constructo 
Tree& Tree::operator=(const Tree& ogTree){
  if(this != &ogTree) {
    Destroy(root);
  }
  try{
    if(ogTree.root!=nullptr){
      root = new Node(*ogTree.root);     
    }else if(ogTree.root->lftPtr!=nullptr){
        this->root->lftPtr = new Node(*ogTree.root->lftPtr);
      }else if(ogTree.root->rtPtr!=nullptr) {
        this->root->rtPtr = new Node(*ogTree.root->rtPtr);
      }
  }catch(bad_alloc& e){
    ExcptHndl();
  }
  return *this;
}

// destructor 
Tree::~Tree() {
  Destroy(root);
    root = nullptr;
}

// recursively destroy the tree. 
// Pre: pass dereference of pointer to parent 
//Post: destroy left side of tree. destroy right side of tree. destroy root. 
void Tree::Destroy(Node *&root) {
  if(root!=nullptr) {
    Destroy(root->lftPtr);
    Destroy(root->rtPtr);
    delete root;
  }
}

// add node to tree
//pre: takes word from an input file 
//post: creates new node if a node with that word does not exist and adds it into the tree alphabetically ELSE it increments the count for a node that contains that word 
void Tree::AddNode(const string word) {
  try{
    if(root==nullptr) {
      root = new Node(nullptr, nullptr, word);
      root->data.IncrementCnt();
    }else {
      Node *finder = root;
      AddNodeHelper(finder, word); // recursive helper function
    }
  }catch(exception& e){
      ExcptHndl();
  }
}

// add chld node to tree alphabetically
void Tree::AddNodeHelper(Node *finder, const string wrd){
  if(wrd < finder->data.GetWord()){ // if it goes on left side
    if(finder->lftPtr==nullptr){ // found left most leaf 
      finder->lftPtr= new Node(nullptr, nullptr, wrd); // put word to left
      finder->lftPtr->data.IncrementCnt();
    }else {
      AddNodeHelper(finder->lftPtr, wrd); //recursively call so can find leaf
    }
  }else if(wrd > finder->data.GetWord()){//if it goes on right s.t.
    if(finder->rtPtr==nullptr){
      finder->rtPtr= new Node(nullptr, nullptr, wrd);
      finder->rtPtr->data.IncrementCnt();
    }else {
      AddNodeHelper(finder->rtPtr, wrd); //recursively call so can find leaf
    }
  }else {
    finder->data.IncrementCnt();
  }
}

// print the tree from leftmost node to rightmost node (alphabetical)
void Tree::PrintTree(){
  Node* finder = root;
  if(finder!=nullptr) {
    PrintTreeHelper(finder);
  }else {
    cout << "TREE IS EMPTY.\n";
  }
  
}

  // print tree by recursively searching for node to print   
void Tree::PrintTreeHelper(Node* finder){
  if(finder!=nullptr){
    PrintTreeHelper(finder->lftPtr);
    cout << setfill('-') << setw(27) << "-" << setfill(' ') << "\n|" << finder->data.GetWord() << right << setw(27-finder->data.GetWord().length()-7) << fixed << "| " << setw(4) << finder->data.GetCnt() << " |" << "\n" << setfill('-') << setw(27) << "-" << setfill(' ')<< endl;
   
    PrintTreeHelper(finder->rtPtr);
  }
}

void Tree::ExcptHndl(){
  cerr << "ERROR. INSUFFICIENT MEMORY.";
  Destroy(root);
  root=nullptr;
}


//funciton to find a node by search by its word data piece and deleting it when found
// pre: user input "wrd" to search for 
//post: recusively calls helper function that searches through tree and uses logical predecessor to replace node being deleted
void Tree::NodeSearch(const string wrd) {
  Node* finder = root;
  Node* prevFinder = finder;

  if(finder!=nullptr){ // something is in tree
    finder = NodeSearchHelper(prevFinder, finder, wrd);  // recusively search for word
  }else {
    cerr << "TREE IS EMPTY";
  }
  
}


//Pre: takes a type string variable called wrd to search for, a pointer to track the parent node passed by reference and a pointer to track the node we want to delete passed by reference 
//Post: deletes the node containing wrd and restructures the tree
Node* Tree::NodeSearchHelper(Node* &prevFinder, Node* &finder, const string wrd) {
  if(finder!=nullptr){
    if (wrd < finder->data.GetWord()) {
        prevFinder = finder;
        finder->lftPtr = NodeSearchHelper(prevFinder, finder->lftPtr, wrd);
    } else if (wrd > finder->data.GetWord()) {
        prevFinder = finder;
        finder->rtPtr = NodeSearchHelper(prevFinder, finder->rtPtr, wrd);
    } else if(wrd == finder->data.GetWord()){ // wrd == node->data.GetWord()
        
        if (finder->lftPtr == nullptr && finder->rtPtr == nullptr) { // leaf node
            if (finder == root) { // root node
                root = nullptr;
            } else if (prevFinder->lftPtr == finder) { // left leaf node
                prevFinder->lftPtr = nullptr;
            
            } else if (prevFinder->rtPtr == finder) { // right leaf node
                prevFinder->rtPtr = nullptr;
              
            }
            delete finder;
            finder = nullptr;
        } else if (finder->lftPtr != nullptr) { // if node to delete has a right child
            Node* temp = finder->lftPtr; // temp is right child of found
            prevFinder = finder;
            // if the right child of node to be changed has left child, find the leftmost leaf 
            if(temp->rtPtr != nullptr){
                while (temp->rtPtr != nullptr) { // while right child of found has a left child
                    prevFinder=temp;// keep track of the parent of the node we are going to reassign so we can reassign its pointers later 
                    temp = temp->rtPtr; // find the left most child of the right child of the node we are deleting 
                }
                
                if(temp->lftPtr != nullptr) { // the node we will be using to replace has right children so need to reassign to replacement nodes parents left edge
                   finder->data.SetWord(temp->data.GetWord());// replace word of node to delete 
                finder->data.SetCnt(temp->data.GetCnt()); // replace count of node to delete
                  prevFinder->rtPtr=temp->lftPtr; // set the parent of replacement node to the right subtree of replacement node
                }else { // replacement node does not have any children and itself is a leaf so reassing its parents left edge 
                   finder->data.SetWord(temp->data.GetWord());// replace word of node to delete 
                finder->data.SetCnt(temp->data.GetCnt()); // replace count of node to delete
                  prevFinder->rtPtr= nullptr;
                }
                
                delete temp; // delete the isolated node 
            } else if(temp->lftPtr == nullptr && temp->rtPtr == nullptr){ // the left child of found is a leaf node
              
                finder->data.SetWord(temp->data.GetWord());// replace node to delete 
                finder->data.SetCnt(temp->data.GetCnt());
                finder->lftPtr = nullptr; // set the right pointer of the parent node to null
                delete temp;
            } 
        }else if(finder->lftPtr == nullptr && finder->rtPtr != nullptr) {
          Node* temp = finder->rtPtr;
          prevFinder->rtPtr = temp;
          delete finder;
          finder = nullptr;
    
        }
    }
  }else{ // word is not in tree
    cerr << "WORD NOT FOUND\n";
  }
    prevFinder= finder;
    return finder;
  
}


