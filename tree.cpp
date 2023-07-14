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
void Tree::PrintTree(bool& isEmpty){
  Node* finder = root;
  if(finder!=nullptr) {
    PrintTreeHelper(finder);
  }else {
    cout << "TREE IS EMPTY.\n";
    isEmpty = true;
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
void Tree::NodeSearch(const string wrd, bool& isEmpty) {
  Node* finder = root;
  Node* prevFinder = finder;

  if(finder!=nullptr){ // something is in tree
    finder = NodeSearchHelper(prevFinder, finder, wrd);  // recusively search for word
  }else {
    cerr << "TREE IS EMPTY";
    isEmpty=true;
  }
  
}


Node* Tree::NodeSearchHelper(Node* &prevFinder, Node* &finder, const string wrd) {
  if(finder!=nullptr){
    if (wrd < finder->data.GetWord()) {
        prevFinder = finder;
        finder->lftPtr = NodeSearchHelper(prevFinder, finder->lftPtr, wrd);
    } else if (wrd > finder->data.GetWord()) {
        prevFinder = finder;
        finder->rtPtr = NodeSearchHelper(prevFinder, finder->rtPtr, wrd);


    } else if(wrd == finder->data.GetWord()){ // wrd == node->data.GetWord()
        // NO CHILDREN

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


          // IF HAS LEFT CHILD 
        } else if (finder->lftPtr != nullptr) { // if node to delete has a LEFT child
		

            Node* temp = finder->lftPtr; // temp is LEFT child of found
            prevFinder = finder;

            // if the LEFT child(TEMP) of node to be DELETED has RIGHT child, find the RIGHTmost leaf AND MAKE IT TEMP

            if(temp->rtPtr != nullptr){
                while (temp->rtPtr != nullptr) { // 
                    prevFinder=temp;// keep track of the parent of the node we are going to reassign so we can reassign its pointers later 
                    temp = temp->rtPtr; // find the left most child of the right child of the node we are deleting 
                }

                // AT THIS POINT, THE NODE TO DELETE HAS A LEFT CHILD AND THAT LEFT CHILD HAS RIGHT CHILDREN. TEMP IS THE RIGHTMOST CHILD AND PREV IS ITS PARENT

                if(temp->lftPtr != nullptr) { // the node we will be using to replace has right children so need to reassign to replacement nodes parents left edge
                  //IF THAT RIGHTMOST CHILD HAS LEFT CHILDREN WE WILL SET OUR NODE TO DELETE TO TEMP(RIGHTMOST CHILD) AND HAVE TEMPS PARENT RIGHT POINTER POINT TO THOSE LEFT CHILDREN

		  finder->data.SetWord(temp->data.GetWord());// replace word of node to delete WITH RIGHTMOST NODE 
                  finder->data.SetCnt(temp->data.GetCnt()); // replace count of node to delete
                  prevFinder->rtPtr=temp->lftPtr; // set the parent of replacement node to the right subtree of replacement node

                }else { // OTHERWISE TEMP(RIGHTMOST CHILD) HAS NO CHILDREN SO SET NODE TO DELETE TO TEMP AND SET ITS PARENT TO NULLPTR
                  finder->data.SetWord(temp->data.GetWord());// replace word of node to delete 
                  finder->data.SetCnt(temp->data.GetCnt()); // replace count of node to delete

		
                  prevFinder->rtPtr= temp->lftPtr;
                  delete temp; // delete the isolated node 
			//prevFinder->rtPtr= temp->rtPtr; // IF TEMP IS RIGHTMOST CHILD THEN ITS RIGHT CHILD IS NULLPTR. AND IF PREVFINDER IS ROOT THIS SHOULD REDIRECT TO RIGHT SUBTREE
                }
                }else if(temp->rtPtr == nullptr && temp->lftPtr !=nullptr){ // THE NODE TO DELETE HAS A LEFT CHILD THAT HAS NO RIGHT CHILDREN BUT DOES HAVE LEFT CHILDREN SO JUST REPLACE THE NODE TODELETE WITH THE LEFT CHILD 
		   finder->data.SetWord(temp->data.GetWord());// replace word of node to delete
		   finder->data.SetCnt(temp->data.GetCnt()); // replace count of node to delete
		   finder->lftPtr = temp->lftPtr;
              delete temp; // delete the isolated node 
                
                
            
              
            } else if(temp->lftPtr == nullptr && temp->rtPtr == nullptr){ // LEFT CHILD OF NODE TO DELETE IS A LEAF 
              
                finder->data.SetWord(temp->data.GetWord());// replace node to delete 
                finder->data.SetCnt(temp->data.GetCnt());
                prevFinder->lftPtr=nullptr;
                finder->lftPtr = nullptr; // SET THE LEFT POINTER OF NODE TO DELETE TO WHAT TEMP LEFTPTR IS POINTING TO (NULLPTR)
		// THE RIGHT POINTER OF FINDER SHOULD STILL POINT TO WHAT IT WAS ORIGINALLY POINTING TO. THIS SHOULD HANDLE THE CASE FOR WHEN NODE TO DELETE IS ROOT AND REPLACING IT WITH LEFT NODE WHICH IS A LEAF

                delete temp; // DELETE THE TEMP 
            } 
     
        }else if(finder->lftPtr == nullptr && finder->rtPtr != nullptr) { // NODE TO DELETE ONLY HAS RIGHT CHILDREN
		// WHAT IF IT IS THE ROOT?? IF IT IS THE ROOT THE TEMP IS A LEAF. ALSO PREVFINDER IS INITIALLIZED TO THE ROOT 
          if(finder == root){
            Node* temp = finder;
            prevFinder = finder;
            finder = finder->rtPtr;
            root = finder;
            delete temp;
          }
          else{
            Node* temp = finder;
            finder = finder->rtPtr;
            prevFinder->rtPtr = finder;
            delete temp;
          }
         
        }
    }
  }else{ // word is not in tree
    cerr << "WORD NOT FOUND\n";
  }
    prevFinder= finder;
    return finder;
  
}



