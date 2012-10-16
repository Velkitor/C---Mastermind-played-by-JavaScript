#include "main.h"

// Our global vars
const char *js_file;
void setJsFile( const char *f){
    js_file = f;
}

// Global JS functions

static Handle<Value> LogCallback(const Arguments& args) {
    if (args.Length() < 1) return v8::Undefined();
    HandleScope scope;
    Handle<Value> arg = args[0];
    String::Utf8Value value(arg);
    printf("%s\n", *value);
    return v8::Undefined();
}

static Handle<Value> SleepCallback(const Arguments& args){
    if (args.Length() < 1) return v8::Undefined();
    HandleScope scope;
    Handle<Value> arg = args[0];
    double duration = arg->NumberValue();
    sleep((int)duration);
    return v8::Undefined();
}

static Handle<Value> uSleepCallback(const Arguments& args){
    if (args.Length() < 1) return v8::Undefined();
    HandleScope scope;
    Handle<Value> arg = args[0];
    double duration = arg->NumberValue();
    usleep((int)duration);
    return v8::Undefined();
}

Handle<ObjectTemplate> getSystemTemplate(){
    Handle<ObjectTemplate> system = ObjectTemplate::New();
    system->Set(String::New("log"), FunctionTemplate::New(LogCallback));
    system->Set(String::New("moveBox"), FunctionTemplate::New(MoveBox));
    system->Set(String::New("positionBox"), FunctionTemplate::New(SetBoxLocation));
    system->Set(String::New("setBoxColor"), FunctionTemplate::New(SetBoxColor));
    system->SetAccessor(String::New("boxPosition"), BoxPositionGetter, NULL);
    system->SetAccessor(String::New("screenSize"), ScreenSizeGetter, NULL);
    system->Set(String::New("sleep"), FunctionTemplate::New(SleepCallback));
    system->Set(String::New("usleep"), FunctionTemplate::New(uSleepCallback));
    
    return( system );
}

Handle<ObjectTemplate> getPlayerTemplate(){
    Handle<ObjectTemplate> player = ObjectTemplate::New();
    player->SetAccessor(String::New("x"), PlayerXGetter, PlayerXSetter);
    player->SetAccessor(String::New("y"), PlayerYGetter, PlayerYSetter);
    player->SetAccessor(String::New("direction"), PlayerDirectionGetter, PlayerDirectionSetter);
    player->SetAccessor(String::New("speed"), PlayerSpeedGetter, PlayerSpeedSetter);
    player->Set(String::New("move"), FunctionTemplate::New(PlayerMove));

    return( player );
}

Handle<ObjectTemplate> getGamesTemplate(){
    Handle<ObjectTemplate> games = ObjectTemplate::New();
    games->Set(String::New("Mastermind"), mastermindGameTemplate()->NewInstance());
    
    return( games );
}

// Load up the JS engine
void initJsEngine(){
    char path[1024];
    uint32_t size = sizeof(path);
    if (_NSGetExecutablePath(path, &size) != 0)
       printf("buffer too small; need size %u\n", size);
    
    string script_path;
    char *pch, *next_pch;
    pch = strtok(path, "/");
    next_pch = strtok(NULL, "/");
    //Rebuild the path, ommitting the last part (the exe name)
    while (next_pch != NULL) {
        script_path.append( "/" );
        script_path.append( pch );
        pch = next_pch;
        next_pch = strtok(NULL, "/");
    }
    script_path.append("/script.js");
    ifstream infile;
    
    infile.open (script_path.c_str(), ifstream::in);
    string file = "";
    while (infile.good()){
        file += (char) infile.get();
    }
    //Get rid of the of character
    file[file.length() - 1] = ' ';
    setJsFile( file.c_str() );
    infile.close();

    // Lock this v8 instance to this thread?
    Locker locker;
    HandleScope handle_scope;
    Persistent<Context> context = Context::New();
    Context::Scope context_scope(context);
    

    context->Global()->Set(String::New("System"), getSystemTemplate()->NewInstance() ); 
    context->Global()->Set(String::New("Player"), getPlayerTemplate()->NewInstance() );
    context->Global()->Set(String::New("Games"),  getGamesTemplate()->NewInstance() );
    
    Handle<String> source = String::New(js_file);
    Handle<Script> script = Script::Compile(source);
    Handle<Value> result = script->Run();
    context.Dispose();
}
