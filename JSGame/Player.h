//
//  Player.h
//  JSGame
//
//  Created by Andrew Hecht on 8/15/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
#ifndef JSGame_Player_h
#define JSGame_Player_h
#include "main.h"


class Player{
public:
    double x,y, direction, speed;
    
    Player();
    virtual    ~Player();
    void SetDirection( double );
    
};

/*
 ==========
 */
Handle<Value> PlayerMove(const Arguments& args);
Handle<Value> PlayerXGetter(Local<String> property, const AccessorInfo& info);
void PlayerXSetter(Local<String> property, Local<Value> value, const AccessorInfo& info);
Handle<Value> PlayerYGetter(Local<String> property, const AccessorInfo& info);
void PlayerYSetter(Local<String> property, Local<Value> value, const AccessorInfo& info);
Handle<Value> PlayerDirectionGetter(Local<String> property, const AccessorInfo& info);
void PlayerDirectionSetter(Local<String> property, Local<Value> value, const AccessorInfo& info);
Handle<Value> PlayerSpeedGetter(Local<String> property, const AccessorInfo& info);
void PlayerSpeedSetter(Local<String> property, Local<Value> value, const AccessorInfo& info);

extern Player *player;
#endif
