//
//  Mastermind.h
//  JSGame
//
//  Created by Andrew Hecht on 8/17/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef JSGame_Mastermind_h
#define JSGame_Mastermind_h
#include "main.h"

class Mastermind{
    int pieces[4];
    int guesses;
    bool solved;
public:
    int lastGuess[4];
    bool playing;
    Mastermind();
    virtual ~Mastermind();
    void Init();
    void Quit();
    int Guess( int *);
    bool Solve( int * );
    bool isSolved();
    int getGuesses();
};

enum MastermindColors { RED, YELLOW, BLUE, GREEN };
extern Mastermind *mastermindGame;
Handle<ObjectTemplate> mastermindGameTemplate();

void MastermindDraw();

#endif
