#include <atomic>
#include <csignal>
#include <iostream>

#define COMPILE_CLIENT // Use to compile the debugging client

#include "raspberry.h"
#include "client.h" // To remove for server side

std::atomic<bool> program_running{true};

void interrupt(int num){
    program_running.store(false);
}

int main(){
    std::signal(SIGTERM, interrupt);
    std::signal(SIGINT, interrupt);

    #ifdef COMPILE_CLIENT
    if(c_initialize()==-1){
        std::cout << "Couldn't initialize CloudBerry, exiting.";
        return 0;
    }
    #else
    if(initialize()==-1){
        std::cout << "Couldn't initialize CloudBerry, exiting.";
        return 0;
    }
    #endif

    while(program_running.load()){
        #ifdef COMPILE_CLIENT
        c_update();
        #else
        update();
        #endif
    }

    #ifdef COMPILE_CLIENT
    c_shutdown();
    #else
    shutdown();
    #endif
    
    return 0;
}