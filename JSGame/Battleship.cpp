#include "main.h"

Battleship *battleshipGame = new Battleship();

Battleship::Battleship(){
    
}
Battleship::~Battleship(){
    
}

void Battleship::Init(){
    
}

void Battleship::Quit(){
    
}



static Handle<Value> BattleshipInitCallback(const Arguments& args){
    battleshipGame->Init();
    return Boolean::New(true);
}

Handle<ObjectTemplate> battleshipGameTemplate(){
    Handle<ObjectTemplate> battleship = ObjectTemplate::New();
    battleship->Set(String::New("start"), FunctionTemplate::New(BattleshipInitCallback));
    
    return( battleship );
}