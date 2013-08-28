//t3solver.cpp
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <list>
#include "GameNode.h"
using namespace std;

class t3solver {
public:
  GameNode rootBoard;
  int numNodes;
  int treeHeight;
  int treeWidth;
  vector<GameNode*> preOrder;
  vector<GameNode*> postOrder;
  vector<GameNode*> levelOrder;
  vector<GameNode*> inversePreOrder; //FOR BONUS PROBLEM
  //GameNode head; //FOR BONUS PROBLEM
  GameNode tail; //FOR BONUS PROBLEM
  
  //t3solver constructor that takes in the rootBoard in serialized form
  t3solver(string serializedBoard) {
    rootBoard.setBoard(serializedBoard);
    rootBoard.setLevel(0);
    tail.it = tail.children.begin();
    numNodes = 1;    
  }
  
  //CreateGameTree always starts with rootNode so it is overloaded to allow for recursion
  void CreateGameTree() {
    preOrder.clear();
    postOrder.clear();
    levelOrder.clear();
    inversePreOrder.clear();
    CreateGameTree(&rootBoard);}
  //overloaded CreateGameTree creates GameTree and preOrder postOrder vectors.
  void CreateGameTree(GameNode *node) {
    preOrder.push_back(node); //called before recursive call to create proper preOrder order
    //node->children.push_back(head); //FOR BONUS PROBLEM
    if(!(node->isLeaf())) {
      for(int i=0; i<3; i++) {
	for(int j=0; j<3;j++) {
	  if (node->board[i][j] == '*') {
	    node->setNumChildren(node->getNumChildren()+1);
	    GameNode *newNode = new GameNode();
	    numNodes++;
	    //set parts of newNode appropriately
	    newNode->setParent(node);
	    node
	      ->children.push_back(newNode); //FOR BONUS PROBLEM
	    newNode->setLevel((node->getLevel())+1);
	    newNode->setBoard(node->getBoard());
	    //use the appropriate character, depending on who's turn it is
	    if (node->turnX) {newNode->setMove(i, j, 'X');}
	    else {newNode->setMove(i, j, 'O');}
	    CreateGameTree(newNode); //recursive call
	  }}}}
    postOrder.push_back(node); //called after recrusive call to create proper postOrder order
    //record the GameTree height and its number of nodes
    if (treeHeight < node->getLevel()) {treeHeight = node->getLevel();}
    //numNodes = preOrder.size();
    
    node->children.push_back(&tail); //FOR BONUS PROBLEM
    node->it = node->children.begin(); //FOR BONUS PROBLEM
    node->currChild = node->children.front(); //FOR BONUS PROBLEM
  }
  
  //postFind returns the int position of a node in the postOrder list matching the given pointer node
  int postFind(GameNode *node) {
    for (int unsigned i=0; i<postOrder.size(); i++) {
      if (postOrder[i] == node) {return i;}
    }
    return -1;
  }
  
  //Order Traversals
  
  //PreOrderTraversal prints the Game Tree out in PreOrder
  void PreOrderTraversal() {
    if(preOrder.size() != 0) { //if to error catch
      cout << "-----------PreOrder Traversal-------------" << endl;
      cout << "------------------------------------------" << endl;
      cout << "Order Number\t" << "Board Layout\t" << "Node Level" << endl;
      //PreOrder vector was created by pushing a node first, and then calling the recursive call  
      for(int unsigned i=0; i<preOrder.size(); i++) {
	cout << i+1 << ":\t\t" << (preOrder[i])->getBoard() << "\t" << (preOrder[i])->getLevel() << endl;}
      cout << "------------------------------------------" << endl;
    }
    else cout << "Cannot print PreOrder. GameTree not created yet." << endl;
  }
  
  //PostOrderTraversal prints the Game Tree out in PostOrder
  void PostOrderTraversal() {
    if(postOrder.size() != 0) { //if to error catch
      cout << "-----------PostOrder Traversal------------" << endl;
      cout << "------------------------------------------" << endl;
      cout << "Order Number\t" << "Board Layout\t" << "Node Level" << endl;
      //PostOrder vector was created by calling the recursive call first, then pushing the node
      for(int unsigned i=0; i<postOrder.size(); i++) {
	cout << i+1 << ":\t\t" << (postOrder[i])->getBoard() << "\t" << (postOrder[i])->getLevel() << endl;}
      cout << "------------------------------------------" << endl;
    }
    else cout << "Cannot print PostOrder. GameTree not created yet." << endl;
  }
  
  //LevelOrderTraversal prints the Game Tree out in LevelOrder
  void LevelOrderTraversal() {
    CreateLevelOrder();
    if(preOrder.size() != 0) { //if to error catch
      cout << "-----------LevelOrder Traversal-----------" << endl;
      cout << "------------------------------------------" << endl;
      cout << "Order Number\t" << "Board Layout\t" << "Node Level" << endl;
      for (int unsigned i=0; i<levelOrder.size(); i++) {
	cout << i+1 << ":\t\t" << levelOrder[i]->getBoard() << "\t" << (levelOrder[i])->getLevel() << endl;}
      cout << "------------------------------------------" << endl;
    }
    else cout << "Cannot create LevelOrder. GameTree not created yet." << endl;
  }
  
  //CreateLevelOrder creates a vector with nodes in LevelOrder by looking at each nodes treeLevel(used in LevelOrderTraversal and PrintTree
  void CreateLevelOrder() {
    if(preOrder.size() != 0) { //if to error catch
      for(int i=0; i<=treeHeight; i++) {
	for (int unsigned j=0; j<preOrder.size(); j++) {
	  if(preOrder[j]->getLevel() == i) {
	    levelOrder.push_back(preOrder[j]);
	  }}}}
  }
  
  
  //PrintMoves prints the moves from the given board to a leaf
  void PrintMoves(string serializedBoard) {
    if(preOrder.size() != 0) { //if to error catch
      cout << "Player Moves for board: " << serializedBoard << endl;
      for(int unsigned i=0; i<preOrder.size(); i++) {
	if (preOrder[i]->getBoard() == serializedBoard) {
	  if (preOrder[i]->leaf) {
	    cout << "\tThis board is already finished.\n\t" << preOrder[i]->winner() << endl;
	    return;}
	  for(int j=1; j <= treeHeight; i++) {
	    //We can traverse the preOrder of the Game Tree from the given board until a leaf is found	  
	    if (preOrder[i]->turnX) {cout << "\tPlayer X Move: " << preOrder[i+j]->getBoard() << endl;}
	    else if (!(preOrder[i]->turnX)) {cout << "\tPlayer O Move: " << preOrder[i+j]->getBoard() << endl;}
	    if(preOrder[i+j]->leaf) {
	      cout << "\t" << preOrder[i+j]->winner() << endl;
	      return;}
	  }}}
      cout << "\tThis board is not in the GameTree." << endl;
    }
    else cout << "Cannot print moves of board. GameTree not created yet." << endl;
  }
  
  //PrintTree prints the Game Tree
  void PrintTree() {
    //CreateLevelOrder();
    if(preOrder.size() != 0) { //if to error catch
      cout << "--------------The Game Tree---------------" << endl;
      cout << "------------------------------------------" << endl;
      for (int unsigned i=0; i<preOrder.size(); i++) {
	preOrder[i]->count = 0;
	cout << "[" <<preOrder[i]->getBoard() << "]" << endl;
	if(preOrder[i] != preOrder.back()) {
	  cout << "      ";
	  cout << "|";
	  //else cout << " ";
	  for (int j=0; j<(preOrder[i+1]->getLevel())-1; j++) {cout << "           |";}
	  cout << "---->";}
      }
      cout << "------------------------------------------" << endl;
    }
    else cout << "Cannot print GameTree. GameTree not created yet." << endl;
  }
  
  ///////////////FOLLOWING CODE IS MY ATTEMPT AT THE BONUS PROBLEM///////////////
  
  //LinkInversionTraversal traverses the GameTree and prints out the nodes in preOrder.
  void LinkInversionTraversal() {
    if(preOrder.size() != 0) {
      GameNode *q = &rootBoard;
      GameNode *p = &tail;
      GameNode *temp1 = p;
      GameNode *temp2 = p;
      while (true) {
	//descend as far as possible to the left of the current node
	while (q != &tail) {
	  inversePreOrder.push_back(q);
	  //descend to left
	  temp1 = p;
	  temp2 = q;
	  p = q;
	  q->setChild(*(q->it));
	  q = q->currChild;
	  if (q != &tail) {++(temp2->it);}
	  temp2->setChild(temp1);
	}
	//ascend as far as possible before next branch
	while ((*(p->it) == &tail) && p != &rootBoard) {
	  temp1 = p;
	  temp2 = q;
	  q = p;
	  p = p->currChild;
	  if(p->currChild != &rootBoard){temp1->setChild(temp2);}
	}
	if (p == &tail) {return;}
	else {
	  //descend to next child
	  temp1 = p;
	  temp2 = q;
	  p->setChild(*(p->it));
	  q = p->currChild;
	  q->setChild(temp1);
	  ++(temp1->it);
	}
      }
      cout << "GameTree not created yet." << endl;
    }
  }
  

};

int main() {
  cout << "------------------------------------------" << endl;
  t3solver *solver = new t3solver("X** *** *O*");
  
  cout << "Root Board: " << solver->rootBoard.getBoard() << endl;
  solver->PrintTree();
  solver->PreOrderTraversal();
  solver->PostOrderTraversal();
  solver->LevelOrderTraversal();
  cout << "\n";
  
  solver->CreateGameTree();
  
  solver->PrintTree();
  
  cout << "\n";
  solver->PreOrderTraversal();
  cout << "\n";
  solver->PostOrderTraversal();
  cout << "\n";
  solver->LevelOrderTraversal();
  
  cout << "\n------------------------------------------" << endl;
  cout << "Number of nodes in GameTree: " << solver->numNodes << endl;
  cout << "------------------------------------------" << endl;
  
  solver->PrintMoves("X** *** XO*"); //node with height=1
  cout << "------------------------------------------" << endl;
  solver->PrintMoves("X** *** *O*"); //root node
  cout << "------------------------------------------" << endl;
  solver->PrintMoves("OXO OXX XOX"); //node not included in GameTree
  cout << "------------------------------------------" << endl;
  solver->PrintMoves("XXX OOX OOX"); //node that is already a leaf 
  
  cout << "------------------------------------------" << endl;
  cout << "------------------------------------------" << endl;
  
  cout << "<<<<<<<<<<<<<ATTEMPT AT BONUS>>>>>>>>>>>>>" << endl;
  
  ///////////////THE FOLLOWING CODE IS MY ATTEMPT AT THE BONUS PROBLEM///////////////
 
 //t3solver *bonus = new t3solver("X*X *OO O*X");
  t3solver *bonus = new t3solver("X** *** *O*");
  bonus->CreateGameTree();
  bonus->LinkInversionTraversal();
  
  
  if(bonus->inversePreOrder.size() != 0) { //if to error catch
    cout << "-------Inverse LevelOrder Traversal-------" << endl;
    cout << "Order Number\t" << "Board Layout\t" << "Node Level" << endl;
    cout << "------------------------------------------" << endl;
    for (int unsigned i=0; i<bonus->inversePreOrder.size(); i++) {
      cout << i+1 << ":\t\t" << bonus->inversePreOrder[i]->getBoard() << "\t" << (bonus->inversePreOrder[i])->getLevel() << endl;}
    cout << "------------------------------------------" << endl;
    
    cout << "------------------------------------------" << endl;
    cout << "------------------------------------------" << endl;
    cout << "-------------------END--------------------" << endl;
  }  
  return 0;
}
