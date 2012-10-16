//
//  gfxBox.cpp
//  JSGame
//
//  Created by Andrew Hecht on 8/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "main.h"

gfxBox::gfxBox(GLfloat x, GLfloat y, GLfloat width, GLfloat height){
    this->pos.x = x;
    this->pos.y = y;
    this->width = width;
    this->height = height;
    this->r = 255;
    this->g = 255;
    this->b = 255;
}
gfxBox::~gfxBox(){
    
}
void gfxBox::setPosition(GLfloat x, GLfloat y){
    this->pos.x = x;
    this->pos.y = y;
}