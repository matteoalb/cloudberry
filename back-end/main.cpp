#include <atomic>
#include <csignal>
#include <iostream>

#include "raspberry.h"

std::atomic<bool> program_running{true};

void interrupt(int num){
    program_running.store(false);
}

int main(){
    std::signal(SIGTERM, interrupt);
    std::signal(SIGINT, interrupt);

    if(initialize()==-1){
        std::cout << "Couldn't initialize CloudBerry, exiting.";
        return 0;
    }

    while(program_running.load()){
        update();
    }

    shutdown();

    return 0;
}