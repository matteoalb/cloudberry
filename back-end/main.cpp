#include <atomic>
#include <csignal>
#include <iostream>

#include "raspberry.h"
#include "client.h" // To remove for server side

std::atomic<bool> program_running{true};

void interrupt(int num){
    program_running.store(false);
}

int main(){
    std::signal(SIGTERM, interrupt);
    std::signal(SIGINT, interrupt);

    if(c_initialize()==-1){ // Use c_initialize to compile a debugging_client
        std::cout << "Couldn't initialize CloudBerry, exiting.";
        return 0;
    }

    while(program_running.load()){
        c_update(); // Use c_update to compile a debugging_client
    }

    c_shutdown(); // Use c_shutdown to compile a debugging_client

    return 0;
}