//
//  Player.cpp
//  JSGame
//
//  Created by Andrew Hecht on 8/15/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "main.h"

Player *player = new Player();

Player::Player(){
    x=0; y=0;
    direction = 0;
    speed = 0;
}

Player::~Player(){
    
}

void Player::SetDirection(double deg){
     direction = fmod( deg, 360);
}

Handle<Value> PlayerMove(const Arguments& args) {
    double point[2];
    point[0] = sin(player->direction * DEG_TO_RAD) * player->speed;
    point[1] = cos(player->direction * DEG_TO_RAD) * player->speed;
    if ( point[0] != 0) {
        player->x += point[0];
    }
    if ( point[1] != 0) {
        player->y += point[1];
    }
    return( v8::Undefined() );
}


Handle<Value> PlayerXGetter(Local<String> property, 
                      const AccessorInfo& info) {
    double clean_x = player->x;
    clean_x *= 100;
    clean_x = int( clean_x);
    clean_x /= 100;
    return Number::New(clean_x);
}

void PlayerXSetter(Local<String> property, Local<Value> value,
             const AccessorInfo& info) {
    player->x = value->NumberValue();
}


Handle<Value> PlayerYGetter(Local<String> property, 
                      const AccessorInfo& info) {
    double clean_y = player->y;
    clean_y *= 100;
    clean_y = int( clean_y);
    clean_y /= 100;
    return Number::New(clean_y);
}

void PlayerYSetter(Local<String> property, Local<Value> value,
             const AccessorInfo& info) {
    player->y = value->NumberValue();
}

Handle<Value> PlayerDirectionGetter(Local<String> property, 
                              const AccessorInfo& info) {
    
    double clean_direction = player->direction;
    clean_direction *= 100;
    clean_direction = int( clean_direction );
    clean_direction /= 100;
    return Number::New(clean_direction);
}

void PlayerDirectionSetter(Local<String> property, Local<Value> value,
                     const AccessorInfo& info) {   
    player->SetDirection( value->NumberValue() );
}

Handle<Value> PlayerSpeedGetter(Local<String> property, 
                          const AccessorInfo& info) {
    double clean_speed = player->speed;
    clean_speed *= 100;
    clean_speed = int( clean_speed );
    clean_speed /= 100;
    return Number::New(clean_speed );
}

void PlayerSpeedSetter(Local<String> property, Local<Value> value,
                 const AccessorInfo& info) {
   
    player->speed = value->NumberValue();
}
