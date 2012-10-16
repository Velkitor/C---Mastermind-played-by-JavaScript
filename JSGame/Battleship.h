//
//  Battleship.h
//  JSGame
//
//  Created by Andrew Hecht on 8/24/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef JSGame_Battleship_h
#define JSGame_Battleship_h
#include "main.h"

class Battleship{
    bool won;
public:
    bool playing;
    Battleship();
    virtual ~Battleship();
    void Init();
    void Quit();
};

extern Battleship *battleshipGame;
Handle<ObjectTemplate> battleshipGameTemplate();

void BattleshipDraw();


#endif
