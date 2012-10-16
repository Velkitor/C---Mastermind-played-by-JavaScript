#include "main.h"
Mastermind *mastermindGame = new Mastermind();
    
Mastermind::Mastermind(){
    this->playing = false;
}
Mastermind::~Mastermind(){
    
}
//Tell mastermind that we want to start playing a game/reset game.
void Mastermind::Init(){
    srand ( time(NULL) );
    this->pieces[0] = rand()%4;
    this->pieces[1] = rand()%4;
    this->pieces[2] = rand()%4;
    this->pieces[3] = rand()%4;
    this->playing = true;
    this->guesses = 0;
    cout << "Pieces: " << pieces[0] << ", " << pieces[1] << ", " << pieces[2] << ", " << pieces[3] << endl;
}

void Mastermind::Quit(){
    this->playing = false;
    this->pieces[0] = 0;
    this->pieces[1] = 0;
    this->pieces[2] = 0;
    this->pieces[3] = 0;
}
int Mastermind::Guess( int *guess){
    for (int i=0; i<4; i++) {
        this->lastGuess[i] = guess[i];
    }
    int matches = 0;
    for (int i = 0; i < 4; i++) {
        for(int n=0; n < 4; n++){
            if (guess[n] != -1 && guess[n] == this->pieces[i]) {
                matches++;
                guess[n] = -1;
                break;
            }
        }
    }
    this->guesses++;
    usleep(100000);
    return matches;
}

bool Mastermind::Solve( int *guess ){
    bool solved = true;
    for (int i = 0; i < 4; i++) {
        if (this->pieces[i] != guess[i]) {
            solved = false;
            break;
        }
    }
    this->solved = solved;
    return solved;   
}

bool Mastermind::isSolved(){
    return this->solved;
}

int Mastermind::getGuesses(){
    return this->guesses;
}
static Handle<Value> MastermindInitCallback(const Arguments& args){
    mastermindGame->Init();
    return Boolean::New(true);
}

static Handle<Value> MastermindGuessCallback(const Arguments& args){
    if (args.Length() < 4) return v8::Undefined();
    int guess[4];
    guess[0] = args[0]->IntegerValue();
    guess[1] = args[1]->IntegerValue();
    guess[2] = args[2]->IntegerValue();
    guess[3] = args[3]->IntegerValue();

    int matches = mastermindGame->Guess(guess);
    return Number::New(matches);
}

static Handle<Value> MastermindSolveCallback(const Arguments& args){
    if (args.Length() < 4) return v8::Undefined();
    int guess[4];
    guess[0] = args[0]->IntegerValue();
    guess[1] = args[1]->IntegerValue();
    guess[2] = args[2]->IntegerValue();
    guess[3] = args[3]->IntegerValue();
    
    bool solved = mastermindGame->Solve(guess);
    return Boolean::New(solved);
}

Handle<ObjectTemplate> mastermindGameTemplate(){
    Handle<ObjectTemplate> mastermind = ObjectTemplate::New();
    mastermind->Set(String::New("start"), FunctionTemplate::New(MastermindInitCallback));
    mastermind->Set(String::New("guess"), FunctionTemplate::New(MastermindGuessCallback));
    mastermind->Set(String::New("solve"), FunctionTemplate::New(MastermindSolveCallback));
    
    return( mastermind );
}

void drawGLString(GLfloat x, GLfloat y, char *string)
{
    int len, i;
    
    glRasterPos2f(x, y);
    len = (int) strlen(string);
    for (i = 0; i < len; i++) {
        
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
    }
}
void drawGLStringColor(GLfloat x, GLfloat y, char *string, double r, double g, double b)
{
    int len, i;
    glColor3d(r, g, b);
    glRasterPos2f(x, y);
    len = (int) strlen(string);
    for (i = 0; i < len; i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
    }
}

long colorOffsetInt;
void MastermindDraw(){
    int w = display->width, h = display->height;
    int boxWidth = w/9, boxHeight = boxWidth;
    int boxY = ( h - boxWidth ) / 2;
    
    
    colorOffsetInt += drawDeltaMS;
    if (colorOffsetInt > 1000) {
        colorOffsetInt = 0;
    }
    double colorOffset = 0.0;
    if (colorOffsetInt < 500) {
        colorOffset = (double)colorOffsetInt/2000;
    } else {
        colorOffset = (double)(1000 - colorOffsetInt)/2000;
    }

    char title[] = "Mastermind", guesses[64];
    sprintf(guesses, "Guesses: %d", mastermindGame->getGuesses());
    drawGLStringColor( boxWidth, h-24, title, 1.0, 0.5 + colorOffset, 0.0 );
    
    double guessRed = (double)mastermindGame->getGuesses() / 20, guessGreen = 1.0 - (double)mastermindGame->getGuesses() / 20;
    if( guessRed > 1.0)
        guessRed = 1.0;
    if (guessGreen < 0.0) 
        guessGreen = 0.0;
    drawGLStringColor( boxWidth, h-48, guesses, guessRed, guessGreen, 0.0 );
    if (mastermindGame->isSolved()) {
        drawGLStringColor( boxWidth, h-72, "Solved", 0.1, 1.0, 0.3 - colorOffset );
    }

    //Calculate the size of our boxes
    //_[]_[]_[]_[]_
    //Box width is screen width / 9
    //Lets make them square.
    for(int i = 0; i < 4; i++){
        int thisX = boxWidth*2*i + boxWidth ;
        glBegin(GL_QUADS);
        switch ((MastermindColors)mastermindGame->lastGuess[i]) {
            case RED:
                glColor3d( 1.0,0.0,0.0);
                break;
            case YELLOW:
                glColor3d( 1.0,1.0,0.0);
                break;
            case BLUE:
                glColor3d( 0.0,0.0,1.0);
                break;
            case GREEN:
                glColor3d( 0.0,1.0,0.0);
                break;
            default:
                break;
        }

        glVertex2f(thisX, boxY);
        glVertex2f(thisX + boxWidth,   boxY);
        glVertex2f(thisX + boxWidth,   boxY + boxHeight);
        glVertex2f(thisX,   boxY + boxHeight);
        glEnd();   
    }
}