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

    while(program_running.load()){
        update();
    }

    return 0;
}