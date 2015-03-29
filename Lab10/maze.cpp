/*
 * Robert Bayer & Davis Allen
 * COEN 70 Lab #10 // Tuesday 9:15 - 12:00
 * TA Patrick
 *
 * Filename: maze.cpp
 * (Program is dependent on graph.h, which is dependent on cell.h.)
 *
 * This file includes a test program for our maze. It asks how wide to make the maze, randomly generates a maze, prints the empty maze, prints a solved maze with the order of traversal, and then prints the perfect method of quickest traversal.
 * */

#include "graph.h"

int main(){
    int entry;
    cout << "Enter the width/height you would like to make your square maze." << endl;
    cin >> entry;
	Graph g(entry);
	g.createMaze();
	g.print();
    g.solve();
    cout << endl;
    g.solvedPrint();
    cout << endl;
    g.perfectPrint();
    cout << endl;

	return 0;
}
