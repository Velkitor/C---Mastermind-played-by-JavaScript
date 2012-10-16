//
//  Display.cpp
//  JSGame
//
//  Created by Andrew Hecht on 8/15/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "main.h"

Display *display;

timeval lastDraw;
long drawDeltaMS = 0;

void setDrawDelta(){
    timeval now;
    gettimeofday(&now, NULL);
    long seconds, useconds; 
    seconds  = now.tv_sec  - lastDraw.tv_sec;
    useconds = now.tv_usec - lastDraw.tv_usec;
    
    drawDeltaMS = ((seconds) * 1000 + useconds/1000.0) + 0.5;
    
    lastDraw = now;
}

void glDisplay(void)
{
    setDrawDelta();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    if (mastermindGame->playing) {
        MastermindDraw();
    } else {
        glBegin(GL_QUADS);
        glColor3d(display->box->r,display->box->g,display->box->b);
        glVertex2f(display->box->pos.x, display->box->pos.y);
        glVertex2f(display->box->pos.x + display->box->width,   display->box->pos.y);
        glVertex2f(display->box->pos.x + display->box->width,   display->box->pos.y + display->box->height);
        glVertex2f(display->box->pos.x,   display->box->pos.y + display->box->height);
        glEnd();
    }    
    
    glutSwapBuffers();
}

void glReshape(int width, int height)
{
    display->width = width;
    display->height = height;
    glViewport(0, 0, width, height);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);
    glMatrixMode(GL_MODELVIEW);
}

void glIdle(void)
{
    glutPostRedisplay();
}





Display::Display(int argc, char* argv[]){
    this->box = new gfxBox(0.0f, 0.0f, 128,128);
    this->width = 640;
    this->height = 480;
    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    
    glutCreateWindow("JS Game!");
    
    glutDisplayFunc(glDisplay);
    glutReshapeFunc(glReshape);
    glutIdleFunc(glIdle);
}

Display::~Display(){
    
}

void Display::Run(){
    glutMainLoop();
}

Handle<Value> MoveBox(const Arguments& args) {
    display->box->pos.x += 1;
    display->box->pos.y += 1;
    return( v8::Undefined() );
}


Handle<Value> SetBoxLocation(const Arguments& args) {
    if (args.Length() < 1) return v8::Undefined();
    HandleScope scope;
    Handle<Value> arg_x = args[0], arg_y = args[1];
    double x = arg_x->NumberValue(), y = arg_y->NumberValue();
    
    display->box->pos.x = (GLfloat)x;
    display->box->pos.y = (GLfloat)y;
    return( v8::Undefined() );
}

Handle<Value> SetBoxColor(const Arguments& args) {
    if (args.Length() < 2) return v8::Undefined();
    HandleScope scope;
    double r = args[0]->NumberValue(), g  = args[1]->NumberValue(), b  = args[2]->NumberValue();

    display->box->r = r;
    display->box->g = g;
    display->box->b = b;
    return( v8::Undefined() );
}

Handle<Value> BoxPositionGetter(Local<String> property, 
                            const AccessorInfo& info) {
    Local<v8::Array> position = v8::Array::New(2);
    position->Set(Number::New(0), Number::New(display->box->pos.x) );
    position->Set(Number::New(1), Number::New(display->box->pos.y) );
    return( position );
}

Handle<Value> ScreenSizeGetter(Local<String> property, const AccessorInfo& info){
    Local<v8::Array> size = v8::Array::New(2);

    size->Set(Number::New(0), Number::New( display->width ) );
    size->Set(Number::New(1), Number::New( display->height ) );
    return( size );
}