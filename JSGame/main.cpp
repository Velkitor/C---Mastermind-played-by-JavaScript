#include "main.h"

#define NUM_THREADS     5

void *PrintHello(void *threadid)
{
    long tid;
    tid = (long)threadid;
    cout << "Hello World! Thread ID, " << tid << endl;
    pthread_exit(NULL);
}

void *RunGL(void *threadid){
    long tid;
    tid = (long)threadid;
    cout << "OpenGL on Thread ID: " << tid << endl;
    display->Run();
    pthread_exit(NULL);
}
void *RunJS(void *threadid){
    long tid;
    tid = (long)threadid;
    cout << "JavaScript on Thread ID: " << tid << endl;
    initJsEngine();
    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
    display = new Display(argc, argv);    

    
    
    pthread_t threads[NUM_THREADS];
    int i=0;
    int rc = pthread_create(&threads[i], NULL, RunJS, (void *)i);
    if (rc){
        cout << "Error:unable to create JavaScript Thread," << rc << endl;
    }
    
//    initJsEngine();
    display->Run();
    while(true){  }
    pthread_exit(NULL);
    return 0;
}