//
//  main.h
//  JSGame
//
//  Created by Andrew Hecht on 8/15/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef JSGame_main_h
#define JSGame_main_h
#include <mach-o/dyld.h>
#include <iostream>
#include <list>
#include <fstream>
#include <stdio.h>
#include <math.h>
#include <v8.h>
#include <pthread.h>
#include <OpenGL/gl.h>
#include <GLUT/GLUT.h>
#include <sys/time.h>

using namespace std;
using namespace v8;


struct gfxPoint{
    GLfloat x,y;
    GLfloat r,g,b;
};

double const DEG_TO_RAD=( M_PI / 180.0 );

// Include our src headers
#include "Player.h"
#include "gfxBox.h"
#include "Display.h"
#include "javascript_main.h"
#include "Mastermind.h"
#include "Battleship.h"

#endif
