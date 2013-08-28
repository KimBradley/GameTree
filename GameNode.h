//GameNode.h
#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <iostream>
using namespace std;

class GameNode {
 public:
  char board[3][3];
  GameNode *parent;
  int treeLevel;
  int numChildren;
  int count; //used in printing out the shape of the tree
  bool leaf;
  bool turnX;
  list<GameNode*> children; //USED FOR BONUS PROBLEM
  list<GameNode*>::iterator it; //USED FOR BONUS PROBLEM
  GameNode *currChild; //USED FOR BONUS PROBLEM
  int tag; //USED FOR BONUS PROBLEM
  
  //GameNode constructor
  GameNode() {
    setBoard("*** *** ***");
    parent = 0;
    treeLevel = 0;
    numChildren = 0;
    count = 0;
    leaf = false;
    turnX = true;
  }
  
//setters
  //setParent sets parent pointer to given GameNode pointer
  void setParent(GameNode *par) {parent = par;}
  //setLevel sets the treeLevel
  void setLevel(int level) {treeLevel = level;}
  //setNumChildren sets the numChildren
  void setNumChildren(int num) {numChildren = num;}
  //setBoard sets the board to the given serialized board
  void setBoard(string serializedBoard) {
    int count = 0;
    //error check
    if ((serializedBoard.size() != 11)) {
      cout << "Board String given is not long enough." << endl;
      return;}
    for(int i=0; i<3; i++) {
      for(int j=0; j<3; j++) {
	//error check
	if (!((serializedBoard.at(count) == 'X')||
	      (serializedBoard.at(count) == 'O')||
	      (serializedBoard.at(count) == ' ')||
	      (serializedBoard.at(count) == '*'))) {
	  cout << "Board String given contains incorrect symbols." << endl;
	  return;}
	if (serializedBoard.at(count) == ' ') {count++;}
	board[i][j] = serializedBoard.at(count);
	count++;
      }}
  }
  //setMove sets the given char to the given position
  void setMove(int i, int j, char x) {
    board[i][j] = x;
    leaf = isLeaf();
    if(x == 'X') {turnX = false;}
    if(x == 'O') {turnX = true;}
  } 
  
//getters
  //getBoard returns board in serialized form 
  string getBoard() {
    string serBoard = "";
    for(int i=0; i<3; i++) {
      for(int j=0; j<3; j++) {
	serBoard += board[i][j];
      }
      if (i != 2){serBoard += ' ';}
    }
    return serBoard;
  }
  //getChar returns char at given position
  char getChar(int i, int j) {return board[i][j];}
  //getLevel returns the level the node is on its tree
  int getLevel() {return treeLevel;}
  //getNumChildren returns the number of children the node has
  int getNumChildren() {return numChildren;}
  //getParent returns pointer to parent node
  GameNode* getParent() {return parent;}
  
  //isLeaf returns true if win or draw, false if otherwise.
  bool isLeaf() {
    //check verticals
    for (int j=0; j<3; j++) {
      if(board[0][j] != '*') {
	if((board[0][j] == board[1][j]) && (board[0][j] == board[2][j]))
	  {return true;}
      }}
    //check horizontals
    for (int i=0; i<3; i++) {
      if(board[i][0] != '*') {
	if((board[i][0] == board[i][1]) && (board[i][0] == board[i][2]))
	  {return true;}
      }}
    //check diagonals
    if ((board[0][0] != '*') && (board[0][0] == board[1][1]) && (board[0][0] == board[2][2]))
      {return true;}
    if ((board[0][2] != '*') && (board[0][2] == board[1][1]) && (board[0][2] == board[2][0]))
      {return true;}
    //check draw
    for (int i=0; i<3; i++) {
      for (int j=0; j<3; j++) {
	if (board[i][j] == '*') {return false;}
      }}
    return true;
    
  }
  
  //winner returns outcome of game, returns "NULL" if not leaf
  string winner() {
    if (leaf) {
      //check verticals
      for (int j=0; j<3; j++) {
	if(board[0][j] != '*') {
	  if((board[0][j] == board[1][j]) && (board[0][j] == board[2][j])) {
	    if (board[0][j] == 'X'){return "Player X won!";}
	    else return "Player O won!";}
	}}
      //check horizontals
      for (int i=0; i<3; i++) {
	if(board[i][0] != '*') {
	  if((board[i][0] == board[i][1]) && (board[i][0] == board[i][2])) {
	    if (board[i][0] == 'X'){return "Player X won!";}
	    else return "Player O won!";}
	}}
      //check diagonals
      if ((board[0][0] != '*') && (board[0][0] == board[1][1]) && (board[0][0] == board[2][2])) {
	if (board[0][0] == 'X'){return "Player X won!";}
	else return "Player O won!";}
      if ((board[0][2] != '*') && (board[0][2] == board[1][1]) && (board[0][2] == board[2][0])) {
	if (board[0][2] == 'X'){return "Player X won!";}
	else return "Player O won!";}
      else return "It's a draw!";
    }
    //if method reaches this return statement, then GameNode is not a leaf
    return "NULL";
  }
  
  //isMatch returns true if the given serialized board matched GameNode board
  bool isMatch(string serializedBoard) {
    int count = 0;
    for (int i=0; i<3; i++) {
      for (int j=0; j<3; j++) {
	if (serializedBoard.at(count) == ' ') {count++;}
	if(board[i][j] != serializedBoard.at(count)) {return false;}
	count++;
      }}
    return true;
  }
  
  
///////////////THE FOLLOWING CODE IS ONLY FOR THE BONUS PROBLEM///////////////
  
  //setChild sets the given pointer to currChild                                                              
  void setChild(GameNode *node) {currChild = node;}

};
