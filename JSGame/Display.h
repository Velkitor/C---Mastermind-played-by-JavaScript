//
//  Display.h
//  JSGame
//
//  Created by Andrew Hecht on 8/15/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef JSGame_Display_h
#define JSGame_Display_h
#include "main.h"
#include "gfxBox.h"

class Display
{
public:
    gfxBox *box;
    int height, width;
    Display(int argc, char* argv[]);
    virtual ~Display();
    void Run();
//    GLint* getScreenSize();
};
extern Display *display;
extern timeval lastDraw;
extern long drawDeltaMS;

Handle<Value> MoveBox(const Arguments& args);
Handle<Value> SetBoxLocation(const Arguments& args);
Handle<Value> SetBoxColor(const Arguments& args);
Handle<Value> BoxPositionGetter(Local<String> property, const AccessorInfo& info);
Handle<Value> ScreenSizeGetter(Local<String> property, const AccessorInfo& info);
#endif
