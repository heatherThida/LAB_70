/*
 * Robert Bayer & Davis Allen
 * COEN 70 Lab #10 // Tuesday 9:15 - 12:00
 * TA Patrick
 *
 * Filename: graph.h
 * (Header is dependent on cell.h, main.cpp is program to run.)
 *
 * This file includes the necessary codes to create a maze, print it, solve it, print the order in which it was traversed, and print the best/quickest possible way to solve it
 * */

#include <iostream>
#include <stack>
#include <cmath>
#include <cstdlib>


#include "cell.h"

using namespace std;

class Graph
{
public:
    Graph(int userInput);
    void makeGrid();
    void createMaze();
    void print();
    void solve();
    void perfectPrint();
    void solvedPrint();
protected:
    Cell* bPointer;
    //create a CellStack (LIFO) to hold a list of cell locations
    stack<int> s;
    int numCells;
    int totalCells;
    int currentRow;
    int currentColumn;
    int direction;
    /*
     0 == right
     1 == top
     2 == left
     3 == bottom
     */
    int cellsFound;
};

Graph::Graph(int userInput)
{
	numCells = userInput;
    //set TotalCells= number of cells in grid
	totalCells = userInput * userInput;
	bPointer = NULL;
    //these could have been local to the createMaze function... hindsight 20/20
	currentRow = 0;
	currentColumn = 0;
}



void Graph::createMaze()
{
    //create "grid" array
    bPointer = new Cell[numCells*numCells];
    
    //choose the starting cell and call it currentCell
    int currentCell = 0;
    
    //set visitedCells = 1
    int visitedCells = 1;
    
    bPointer[currentCell].setVisited(true);
    srand(time(NULL));
    while(visitedCells < totalCells)
    {
        //update currentRow and Current Column
        currentRow = floor(currentCell/numCells);
        currentColumn = currentCell % numCells;
        
        //find all neighbors of CurrentCell with all walls intact
        int possibilities[4];
        int posSize = 0;
       
        if(currentColumn > 0)
        {
            //check left
            if(bPointer[currentCell].walls[2] == true && !bPointer[currentCell-1].isVisited())
            {
                possibilities[posSize] = currentCell-1;
                posSize++;
            }
        }
        if(currentColumn < numCells-1)
        {
            //check right
            if(bPointer[currentCell].walls[0] == true && !bPointer[currentCell+1].isVisited())
            {
                possibilities[posSize] = currentCell+1;
                posSize++;
            }
        }
        if(currentRow > 0)
        {
            //check top
            if(bPointer[currentCell].walls[1] == true && !bPointer[currentCell-numCells].isVisited())
            {
                possibilities[posSize] = currentCell - numCells;
                posSize++;
            }
        }
        if(currentRow < numCells-1)
        {
            //check bottom
            if(bPointer[currentCell].walls[3] == true && !bPointer[currentCell+numCells].isVisited())
            {
                possibilities[posSize] = currentCell + numCells;
                posSize++;
            }
        }
        
        
        //if(one or more found choose one at random)
        if(posSize >= 1)
        {
            
            // produces random number of array
            int randomNum = rand() % posSize; //maybe just possize
            
            int found = possibilities[randomNum];
            
            //knock down the wall between it and CurrentCell
            //push CurrentCell location on the CellStack
            //make the new cell CurrentCell
            //add 1 to VisitedCells
            
            //if found is left of currentCell
            if(currentCell-1 == found){
                bPointer[currentCell].setLeft(&bPointer[found]);
                bPointer[currentCell].walls[2] = false;
                bPointer[found].walls[0] = false;
                bPointer[found].setRight(&bPointer[currentCell]);
                bPointer[found].setVisited(true);
                s.push(currentCell);
                currentCell -=1;
                visitedCells++;
            }
            
            //if found is top of currentCell
            if(currentCell - numCells == found){
                bPointer[currentCell].setUp(&bPointer[found]);
                bPointer[currentCell].walls[1] = false;
                bPointer[found].walls[3] = false;
                bPointer[found].setDown(&bPointer[currentCell]);
                bPointer[found].setVisited(true);
                s.push(currentCell);
                currentCell -= numCells;
                visitedCells++;
            }
            
            //if found is right of currentCell
            if(currentCell+1 == found){
                bPointer[currentCell].setRight(&bPointer[found]);
                bPointer[currentCell].walls[0] = false;
                bPointer[found].walls[2] = false;
                bPointer[found].setLeft(&bPointer[currentCell]);
                bPointer[found].setVisited(true);
                s.push(currentCell);
                currentCell += 1;
                visitedCells++;
            }
            
            //if found is bottom of currentCell
            if(currentCell+numCells == found){
                bPointer[currentCell].setDown(&bPointer[found]);
                bPointer[currentCell].walls[3] = false;
                bPointer[found].setUp(&bPointer[currentCell]);
                bPointer[found].walls[1] = false;
                bPointer[found].setVisited(true);
                s.push(currentCell);
                currentCell += numCells;
                visitedCells++;
            }
            
        }
        else
        {
            //pop the most recent cell entry off the CellStack
            //make it CurrentCell
            currentCell = s.top();
            s.pop();
        }
        
    }
    
}

void Graph::print(){
    //print the top row of + & - w/ a space for the maze's entry
    cout << "+ ";
    for(int i = 0; i < numCells-1; i++)
        cout << "+-";
    cout << "+" << endl;
    
    //print the rest of the maze , taking into account when the user is allowed to pass through a wall (pointer exists)
    int currentRow = 0;
    Cell* currentCell;
    
    for(int j=0; j<numCells-1; j++){
        cout << "|";
        for(int i=currentRow; i<currentRow+numCells; i++){
            currentCell = &bPointer[i];
            cout << " ";
            if(currentCell->getRight() == NULL)
                cout << "|";
            else
                cout << " ";
                
                
        }
        cout << endl;
        
        cout << "+";
        for(int i=currentRow; i<currentRow+numCells; i++){
            currentCell = &bPointer[i];
            if(currentCell->getDown() == NULL)
                cout << "-";
            else
                cout << " ";
            cout << "+";
                
        }
        cout << endl;
            
        currentRow+=numCells;
    }
    
    //print the last row, again leaving a space for the maze's exit
    cout << "|";
    for(int i=currentRow; i<currentRow+numCells; i++){
        currentCell = &bPointer[i];
        cout << " ";
        if(currentCell->getRight() == NULL)
            cout << "|";
        else
            cout << " ";
        
        
    }
    cout << endl;
    
    for(int i=0; i<numCells-1; i++)
       cout << "+-";
    cout<<"+ +" << endl;
}

//function to solve the maze
//Highlights include: setting direction, parent for quick solve function, and setting numVisit to print the order in which the maze was traversed
void Graph::solve(){
    int current = 0;
    int num = 0;
    
    //while you haven't found the exit..
    while(current != totalCells-1){
        //if it's the first time visiting a cell, give it a visit number and increment the num counter
        if(bPointer[current].numVisit == 10000000){
            bPointer[current].numVisit = num;
            num++;
        }
        
        //if you can go left, and you didnt just come from the left, try going that direction
        if(bPointer[current].getLeft() != NULL && bPointer[current].getColor() == 0 && bPointer[current].direction != 2){
            bPointer[current-1].setParent(&bPointer[current]);
            bPointer[current-1].direction = 0;
            bPointer[current].setColor(1);
            current = current-1;
            continue;
        }
        //if you can't go left, mark that you tried using the color variable
        else if (bPointer[current].getColor() == 0)
            bPointer[current].setColor(1);
        
        //if you can go right, and you didnt just come from the right, try going that direction
        if(bPointer[current].getRight() != NULL && bPointer[current].getColor() == 1 && bPointer[current].direction != 0){
            bPointer[current+1].setParent(&bPointer[current]);
            bPointer[current+1].direction = 2;
            bPointer[current].setColor(2);
            current = current+1;
            continue;
        }
        //if you can't go right, mark that you tried left and right using the color variable
        else if (bPointer[current].getColor() == 1)
            bPointer[current].setColor(2);
        
        //if you can go up, and you didnt just come from the top, try going that direction
        if(bPointer[current].getUp() != NULL && bPointer[current].getColor() == 2 && bPointer[current].direction != 1){
            bPointer[current-numCells].setParent(&bPointer[current]);
            bPointer[current-numCells].direction = 3;
            bPointer[current].setColor(3);
            current = current - numCells;
            continue;
        }
        //if you can't go up, mark that you tried left, right, and up using the color variable
        else if (bPointer[current].getColor() == 2)
            bPointer[current].setColor(3);
        
        //if you can go down, and you didnt just come from the bottom, try going that direction
        if(bPointer[current].getDown() != NULL && bPointer[current].getColor() == 3 && bPointer[current].direction != 3){
            bPointer[current+numCells].setParent(&bPointer[current]);
            bPointer[current+numCells].direction = 1;
            bPointer[current].setColor(4);
            current = current + numCells;
            continue;
        }
        //if you can't go down, mark that you tried every direction using the color variable
        else if (bPointer[current].getColor() == 3){
            bPointer[current].setColor(4);
        }
        
        //if you can't go in any new direction, remove the parent pointer and go backwards until you find another path
        if((bPointer[current].getColor() == 4)){
            //remove parent pointer and go back somehow
            bPointer[current].setParent(NULL);
            
            //go back to the cell that called you using the cell's direction variable, which stores what direction the cursor came from
            switch (bPointer[current].direction) {
                case 0:
                    current += 1;
                    break;
                case 1:
                    current -= numCells;
                    break;
                case 2:
                    current -= 1;
                    break;
                case 3:
                    current += numCells;
                    break;
                default:
                    break;
            }
        }

    }
    //put the last number into the last (exit) cell
    bPointer[current].numVisit = num;
    
    
}

//same as normal print, except for commented region
void Graph::solvedPrint(){
    cout << "+ ";
    for(int i = 0; i < numCells-1; i++)
        cout << "+-";
    cout << "+" << endl;
    
    int currentRow = 0;
    Cell* currentCell;
    
    for(int j=0; j<numCells-1; j++){
        cout << "|";
        for(int i=currentRow; i<currentRow+numCells; i++){
            currentCell = &bPointer[i];
            //if the cell was visited, say what number it was visted (mod 10 to keep single digit display)
            if(currentCell->numVisit != 10000000){
                int n = currentCell->numVisit%10;
                cout << n;
            }
            else
                cout << " ";
            if(currentCell->getRight() == NULL)
                cout << "|";
            else
                cout << " ";
            
            
        }
        cout << endl;
        
        cout << "+";
        for(int i=currentRow; i<currentRow+numCells; i++){
            currentCell = &bPointer[i];
            if(currentCell->getDown() == NULL)
                cout << "-";
            else
                cout << " ";
            cout << "+";
            
        }
        cout << endl;
        
        currentRow+=numCells;
    }
    
    //print last row
    cout << "|";
    for(int i=currentRow; i<currentRow+numCells; i++){
        currentCell = &bPointer[i];
        //if the cell was visited, say what number it was visted (mod 10 to keep single digit display)
        if(currentCell->numVisit != 10000000){
            int n = currentCell->numVisit%10;
            cout << n;
        }
        else
            cout << " ";
        if(currentCell->getRight() == NULL)
            cout << "|";
        else
            cout << " ";
        
        
    }
    cout << endl;
    
    for(int i=0; i<numCells-1; i++)
        cout << "+-";
    cout<<"+ +" << endl;
}


//same as normal print, except for commented region
void Graph::perfectPrint(){
    
    cout << "+ ";
    for(int i = 0; i < numCells-1; i++)
        cout << "+-";
    cout << "+" << endl;
    
    int currentRow = 0;
    Cell* currentCell;
    
    for(int j=0; j<numCells-1; j++){
        cout << "|";
        for(int i=currentRow; i<currentRow+numCells; i++){
            currentCell = &bPointer[i];
            //if the cell was visited and has a child, then it was on the perfect path, so print a #
            if((currentCell->numVisit != 10000000) && (currentCell->hasChild())){
                cout << "#";
            }
            else
                cout << " ";
            if(currentCell->getRight() == NULL)
                cout << "|";
            else
                cout << " ";
            
            
        }
        cout << endl;
        
        cout << "+";
        for(int i=currentRow; i<currentRow+numCells; i++){
            currentCell = &bPointer[i];
            if(currentCell->getDown() == NULL)
                cout << "-";
            else
                cout << " ";
            cout << "+";
            
        }
        cout << endl;
        
        currentRow+=numCells;
    }
    
    //print last row
    cout << "|";
    for(int i=currentRow; i<currentRow+numCells-1; i++){
        currentCell = &bPointer[i];
        //if the cell was visited and has a child, then it was on the perfect path, so print a #
        if((currentCell->numVisit != 10000000) && (currentCell->hasChild())){
            cout << "#";
        }
        else
            cout << " ";
        if(currentCell->getRight() == NULL)
            cout << "|";
        else
            cout << " ";
        
        
    }
    cout << "#|";
    cout << endl;
    
    for(int i=0; i<numCells-1; i++)
        cout << "+-";
    cout<<"+ +" << endl;
}