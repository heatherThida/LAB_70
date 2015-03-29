/*
 * Robert Bayer & Davis Allen
 * COEN 70 Lab #10 // Tuesday 9:15 - 12:00
 * TA Patrick
 *
 * Filename: cell.h
 * (Header is dependent of graph.h, main.cpp is program to run.)
 *
 * This file includes the Cell class used to create individual cells of the maze.
 * */

using namespace std;

class Cell{
    
public:

    Cell();
    ~Cell();
    //Accessors & Mutators
    Cell* getParent();
    void setParent(Cell *);
    
    int getColor();
    void setColor(int c);
    
    Cell* getUp();
    Cell* getDown();
    Cell* getLeft();
    Cell* getRight();
    
    bool isVisited();
    void setVisited(bool);
    
    bool hasChild();
    
    void setUp(Cell*);
    void setDown(Cell*);
    void setLeft(Cell*);
    void setRight(Cell*);
    
    //Public Variables
    bool walls[4]; //boolean variables say whether walls exist around the cell
    int numVisit;   //stores the order in which cells are visited
    int direction;  //stores the direction of the cell that sent the cursor to the current cell (used in the solve function of graph)
    
protected:
    Cell *up;
    Cell *down;
    Cell *left;
    Cell *right;
    int color;
    Cell * parent;
    bool visited;
    
};



Cell::Cell()
{
	up = NULL;
	down = NULL;
	left = NULL;
	right = NULL;
	parent = NULL;
    color = 0;
    visited = false;
    //start all cells with 4 walls
    for(int i=0; i<4; i++){
        walls[i] = true;
    }
    //assume no one will run a maze with over 3,000 width
    numVisit = 10000000;
    //set direction outside possible values (1-4)
    direction = 5;
}

Cell::~Cell()
{
    up = NULL;
	down = NULL;
	left = NULL;
	right = NULL;
	parent = NULL;
}


Cell* Cell::getParent()
{
    return parent;
}

void Cell::setParent(Cell* c)
{
	parent = c;
	return;
}

int Cell::getColor()
{
	return color;
}

void Cell::setColor(int c)
{
	color = c;
    return;
}

Cell* Cell::getUp(){
    return up;
}

Cell* Cell::getDown(){
    return down;
}
Cell* Cell::getLeft(){
    return left;
}
Cell* Cell::getRight(){
    return right;
}


void Cell::setUp(Cell * c){
    up = c;
    return;
}

void Cell::setDown(Cell* c){
    down = c;
    return;
}
void Cell::setLeft(Cell* c){
    left = c;
    return;
}
void Cell::setRight(Cell* c){
    right = c;
    return;
}

bool Cell::isVisited(){
    return visited;
}
void Cell::setVisited(bool entry){
    visited = entry;
    return;
}
//returns whether a cell has a child by checking each directional pointer that is not null -- used in the perfect print
bool Cell::hasChild(){
    if(left != NULL && left->parent == this)
        return true;
    if(right != NULL && right->parent == this)
        return true;
    if(up != NULL && up->parent == this)
        return true;
    if(down != NULL && down->parent == this)
        return true;
    return false;
}


