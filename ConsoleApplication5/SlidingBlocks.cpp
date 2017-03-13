
#include "stdafx.h"

/**
* @author Dilek Arikan
* @date 11-03-2017
* @file SlidingBlocks.cpp
* @brief This is a program that simulates the game, Rush Hour (or Sliding Blocks).
**/

#include <iostream>
#include <cstdlib>
#include <queue>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

const int ROWS = 6;
const int COLS = 6;

/**
* @struct This structure is for keeping blocks. 
*
* Block has coordinates, size and orientation
*  (H for horizontal or V for vertical) information. 
*
**/
struct Block {
	int xPos;
	int yPos;
	int size;
	char orientation;
};

/**
*@struct This structure is to define nodes of graph. 
*
* A node is a 6x6 board on which blocks are placed.
* 
**/

struct Node {
	char boardNode[ROWS][COLS];
	int mark;
};

Block* readBlocks(int numBlocks);

void setBoard(char board[ROWS][COLS], Block *Blocks, int numBlocks);

bool moveForward(Block &current, char board[ROWS][COLS]);

bool moveBackward(Block &current, char board[ROWS][COLS]);

bool bfs(Node nodes, char board[ROWS][COLS], Block *Blocks, int numBlocks);

bool gameWon(Block goalBlock);

void clearBoard(char board[ROWS][COLS]);

Node Nodes(char board[ROWS][COLS]);


/**
* @main The program will loop through a process of getting input from the
* user and solving the specific problem it will then display the results
* and quit.
**/

int main() {
	// declare local variables
	Block *Blocks = NULL;
	Node nodes;
	char gameBoard[ROWS][COLS];
	int numBlocks = 7;

	// initialize the game board

	clearBoard(gameBoard);
	
	/*	for (int i = 0; i < ROWS; i++) {
	for (int j = 0; j < COLS; j++) {
	cout << gameBoard[i][j] << ' ';
	}
	cout << endl;
	}
	*/

	// read information of blocks
	Blocks = readBlocks(numBlocks);

	// set the game board and place blocks on the board
	setBoard(gameBoard, Blocks, numBlocks);

	// define board as a node for graph
	nodes = Nodes(gameBoard);
	setBoard(gameBoard, Blocks, numBlocks);
	// prints solution if BFS finds a solution
	if (bfs(nodes, gameBoard, Blocks, numBlocks)) {
		/*for (int i = 0; i < ROWS; i++) {
			for (int j = 0; j < COLS; j++) {
				cout << gameBoard[i][j] << ' ';
			}
			cout << endl;
		}*/
	}

	else
	{
		cout << "No solution found. " << endl;
	}

	return 0;
}

/**
* This function takes the information of blocks into
* the structure 'Blocks'.
* The function stores the blocks in array of blocks.
*
**/
Block* readBlocks(int numBlocks) {
	// create an array of Block structs of size numBlocks

	Block *Blocks = new Block[numBlocks];

	Blocks[0].size = 2;
	Blocks[0].orientation = 'H';
	Blocks[0].yPos = 2;
	Blocks[0].xPos = 1;

	Blocks[1].size = 2;
	Blocks[1].orientation = 'V';
	Blocks[1].yPos = 3;
	Blocks[1].xPos = 0;

	Blocks[2].size = 2;
	Blocks[2].orientation = 'V';
	Blocks[2].yPos = 5;
	Blocks[2].xPos = 0;

	Blocks[3].size = 2;
	Blocks[3].orientation = 'V';
	Blocks[3].yPos = 4;
	Blocks[3].xPos = 1;

	Blocks[4].size = 2;
	Blocks[4].orientation = 'H';
	Blocks[4].yPos = 5;
	Blocks[4].xPos = 2;

	Blocks[5].size = 3;
	Blocks[5].orientation = 'V';
	Blocks[5].yPos = 2;
	Blocks[5].xPos = 3;

	Blocks[6].size = 2;
	Blocks[6].orientation = 'V';
	Blocks[6].yPos = 2;
	Blocks[6].xPos = 4;

	return Blocks;
}

// create nodes structure

Node Nodes(char board[ROWS][COLS]) {

	Node nodes;

	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			nodes.boardNode[i][j] = board[i][j];
			nodes.mark = 0;
			//cout << nodes.boardNode[i][j] << ' ';
		}

	}

	return nodes;
}


/**
* This function places a 'C' on any space occupied by a block
* on the gameboard. Gameboard is a 2D 6x6 array.
*
**/

// initialize array 

void setBoard(char board[ROWS][COLS], Block *Blocks, int numBlocks) {

	int counter = 0;

	for (int row = 0; row < ROWS; row++) {
		// initialize the arrays columns
		for (int col = 0; col < COLS; col++) {
			// give each element an 'X'
			board[row][col] = 'X';

		}

	}

	// loop through blocks and represent them on the board
	for (int i = 0; i < numBlocks; i++) {
		// case: orientation is verticle
		if (Blocks[i].orientation == 'V') {
			// place the Block
			while (counter < Blocks[i].size) {
				board[Blocks[i].yPos - counter][Blocks[i].xPos] = 'C';
				counter++;
			}
			// reset counter
			counter = 0;
		}
		// case: orientation is horizontal
		if (Blocks[i].orientation == 'H') {
			// place the Block
			while (counter < Blocks[i].size) {
				board[Blocks[i].yPos][Blocks[i].xPos + counter] = 'C';
				counter++;
			}
			// reset counter
			counter = 0;
		}
	}
}



/**
* This function will move a single block forward
*
* The function moves a single block forward, for vertical Blocks this means
* the Block will be moved up and for horizontal blocks it means it will be moved
* to the right. The Block is only moved forward one square.
*
**/
bool moveForward(Block &current, char board[ROWS][COLS]) {
	// case: Block is vertical
	if (current.orientation == 'V') {
		// check if there is anything in front of the Block
		if (current.yPos - current.size >= 0 
			&& board[current.yPos - current.size][current.xPos] != 'C') {
			// move Block up one square
			current.yPos--;

			// return successfull
			return true;
		}
	}
	// case: Block is horizontal
	if (current.orientation == 'H') {
		// check if there is anything in front of the Block
		if (current.xPos + (current.size - 1) <= (COLS - 1) 
			&& board[current.yPos][current.xPos + current.size] != 'C') {
			// move the Block one square left
			current.xPos++;
			// return successfull
			return true;
		}
	}
	return false;
}

/**
* This function will move a single Block backwards
*
* The function moves a single block backward, for vertical blocks this means
* the Block will be moved down and for horizontal blocks it means it will be moved
* to the left. The Block is only moved backward one square.
*
**/
bool moveBackward(Block &current, char board[ROWS][COLS]) {
	// case: Block is vertical
	if (current.orientation == 'V') {
		// check if there is anything in front of the Block
	if (current.yPos + 1 <= (ROWS - 1) && board[current.yPos + 1][current.xPos] != 'C') {
			// move Block up one square
			current.yPos++;

			// return success
			return true;
		}
	}
	// case: Block is horizontal
	if (current.orientation == 'H') {
		// check if there is anything in front of the Block
	if (current.xPos - 1 >= 0 && board[current.yPos][current.xPos - 1] != 'C') {
			// move the Block one square left
			current.xPos--;
			// return success
			return true;
		}
	}
	return false;
}

/**
*
* This function will use BFS in order to solve the problem.
* It will use 2-Dim 6x6 array as nodes and keep nodes in a queue.
* Children are created with implementation of moveForward
* and moveBackward actions.
**/

bool bfs(Node nodes, char board[ROWS][COLS], Block *Blocks, int numBlocks) {

	queue<Node> q; // create a queue
	q.push(nodes); // put first node into the queue

	while (!q.empty()) {
		Node u = q.front(); // pull a node from the beginning of the queue
		q.pop();
		if (gameWon(Blocks[0])) {
			return true;
			break;
		}
		for (int i = 0; i < numBlocks; i++) {
			if (moveForward(Blocks[i], u.boardNode) && (u.mark=0)) {
				q.push(u);
				u.mark = 1;
			}
			else if (moveBackward(Blocks[i], u.boardNode) && (u.mark = 0)) {
				q.push(u);
				u.mark = 1;
			}
			for (int i = 0; i < ROWS; i++) {
				for (int j = 0; j < COLS; j++) {
					cout << u.boardNode[i][j] << ' ';
				}
				cout << endl;
			}
		}
		u.mark = 2;

	}
	return true;
}

/**
*
* This function will check the position of the goal block and
* test whether it is in a winning position or not
*
**/
bool gameWon(Block goalBlock) {
	if ((goalBlock.xPos + (goalBlock.size - 1)) == ROWS - 1) {
		return true;
	}
	return false;
}

/**
*
* This function will clear the current values
* in a 2D array and set all elements t 'X'
**/
void clearBoard(char board[ROWS][COLS]) {
	// loop through rows
	for (int i = 0; i < ROWS; i++) {
		// loop through columns
		for (int j = 0; j < COLS; j++) {
			board[i][j] = 'X';

		}
	}
}
