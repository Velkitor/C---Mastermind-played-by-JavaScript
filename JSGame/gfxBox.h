//
//  gfxBox.h
//  JSGame
//
//  Created by Andrew Hecht on 8/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef JSGame_gfxBox_h
#define JSGame_gfxBox_h
#include "main.h"


class gfxBox
{
public:
    gfxPoint pos;
    GLfloat width, height;
    GLdouble r,g,b;
    gfxBox(GLfloat x, GLfloat y, GLfloat width, GLfloat height);
    virtual ~gfxBox();
    void setPosition(GLfloat x, GLfloat y);
};

#endif
