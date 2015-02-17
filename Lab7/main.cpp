/*
 * Gus Boling & Robert Bayer
 * COEN 70 Lab #7 // Tuesday 9:15 - 12:00
 * TA Patrick
 *
 * Filename: main.cpp
 *
 *
 * Polymorphism Lab - Guessing Game
 * */

#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;

//prototypes for functions not associated with classes
void play();
bool isAnswer(int, int);

//base class
class player
{
public:
    virtual int getGuess() = 0;
    virtual void lastWasTooHigh(bool tooHigh) = 0;
    virtual void opponentsGuess(int guess, bool tooHigh) = 0;
    virtual void reset() = 0;
};

//class for a computer player
class computer: public player
{
public:
    computer()
    {
        //initiate private variables
        low = 0;
        high = 99;
        mid = 49;
    }
    
    ~computer()
    {
        delete this;
    }
    
    int getGuess()
    {
        //binary search for correct answer (guess)
        mid = (high+low)/2;
        return mid;
    }
    
    void lastWasTooHigh(bool tooHigh)
    {
        if(tooHigh){
            //update high and tell computer (user) that last guess was too high
            high = mid;
            cout << "Your last guess was too high." << endl;
        }
        else{
            //update low and tell computer (user) that last guess was too low
            low = mid;
            cout << "Your last guess was too low." << endl;
        }
        
    }
    
    void opponentsGuess(int guess, bool tooHigh)
    {
        //a guess of 100 is out of bounds and represents no guesses
        if(guess == 100)
        {
            cout << "You have the first move." << endl;
            return;
        }
        //make sure the user cannot trick the computer into messing up bounds
        if(tooHigh && guess < high)
            high = guess;
        //update low and make sure user can't trick computer
        else if(!tooHigh && guess>low)
            low = guess;
        //output opponents last guess
        cout << "Your opponent's last guess was " << guess << endl;
    }
    
    void reset()
    {
        //basically just a repeat of the constructor
        high = 99;
        low = 0;
        mid = 49;
    }
    
private:
    int low, high, mid;
};

class human: public player
{
public:
    //no private vars or dynamic memory, so constructor and destructor are empty
    human(){}
    
    ~human(){}
    
    //read in guess from user
    int getGuess()
    {
        int answer;
        cout << "Enter your guess" << endl;
        cin >> answer;
        return answer;
    }

    //tell the user if their guess was too high or too low
    void lastWasTooHigh(bool tooHigh)
    {
        if(tooHigh)
            cout << "Your last guess was too high." << endl;
        else
            cout << "Your last guess was too low." << endl;
        
    }

    //tell the user what their opponents last guess was
    void opponentsGuess(int guess, bool tooHigh)
    {
        //100 denotes no guesses made (out of bounds)
        if(guess == 100){
			cout << "You are the first player." << endl;
		}
		else{
			cout << "Your opponent's last guess was " << guess;
        	if(tooHigh){
            	cout << " and it was too high." << endl;
        	}
        	else {
            	cout << " and it was too low." << endl;
        	}
		}
    }

    //no private variables, so reset is empty
    void reset(){}
    
};


void play() {
    
        //initiate guesses to out of bounds (100) to designate no current guesses
        int p1Guess = 100, p2Guess = 100;
        //loop condition
        bool foundAnswer = false;
        //bool whether the guess was too high
        bool tooHigh;
        //play 1 & 2 designate whether human or computer, answer is random
        int play1, play2, answer;
       	
		player* p1;
	   	player*	p2;

        //seed random with time
        srand(time(NULL));
        //set answer to random number between 0 and 99
        answer = rand() % 100;
    
        //tell the user the answer (for debugging/cheating)
        cout << "Shh... the answer is " << answer << endl;
    
        //have player 1 choose to be computer or human
        cout << "Player 1: Enter 0 to be a human or 1 to be a computer." << endl;
        cin >> play1;
        if(play1 == 0){
			human* h1 = new human();
            p1 = h1;
        }
        else if(play1 == 1){
            computer* c1 = new computer();
			p1 = c1;
        }
        else{
            cout << "Invalid entry." << endl;
        }
        
        //have player 2 choose to be computer or human
        cout << "Player 2: Enter 0 to be a human or 1 to be a computer." << endl;
        cin >> play2;
        if(play2 == 0){
            human* h2 = new human();
			p2 = h2;
        }
        else if(play2 == 1){
            computer* c2 = new computer();
			p2 = c2;
        }
        else{
            cout << "Invalid entry." << endl;
        }
        
        //loop while the answer hasn't been found
        while(!foundAnswer){
            //tell p1 what the opponents last guess was
            p1->opponentsGuess(p2Guess, tooHigh);
            //let p1 guess
            p1Guess = p1->getGuess();
            //if they guess correctly, the game ends
            if(isAnswer(p1Guess, answer)) {
                cout << "Congratulations!! Player 1 wins! The answer was " << answer << endl;
                p2->reset();
				foundAnswer = true;
            	return;
			}
            //otherwise, call lastWasTooHigh to tell p1 whether they guessed high or low
            else{
                tooHigh = p1Guess > answer;
                p1->lastWasTooHigh(tooHigh);
            }
            
            
            //tell p2 what opponents last guess was
            p2->opponentsGuess(p1Guess, tooHigh);
            //let p2 guess
            p2Guess = p2->getGuess();
            //if they guess correctly, the game ends
            if(isAnswer(p2Guess, answer)) {
                cout << "Congratulations!! Player 2 wins! The answer was " << answer << endl;
                p2->reset();
				foundAnswer = true;
            	return;
			}
            //otherwise, call lastWasTooHigh to tell p2 whether they guessed high or low
            else{
                tooHigh = p2Guess > answer;
                p2->lastWasTooHigh(tooHigh);
            }
            
        }
        
        
        
    }

//return whether the guess is equal to answer
bool isAnswer(int guess, int answer){
    if(guess == answer){
        return true;
    }
    else
        return false;
}
    
int main(){
    //loop while user wants to play
    bool playing = true;
    while(playing){
        bool response;
        cout << "Do you want to play a game? (Enter 1 for yes or 0 for no)" << endl;
        cin >> response;
        if(response){
            play();
        }
        else{
            playing = false;
        }
    }
}
