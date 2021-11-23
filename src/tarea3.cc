
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <unistd.h> 
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
#include <signal.h>
#include <thread>
#include <csignal>

void signal_handler( int signal_num ) { 
	
	std::cout << "Detención no permitida" << std::endl;
}

void signal_handler1( int signal_num ) { 
	
	std::raise(SIGTERM);
} 

void signal_handler2( int signal_num ) { 
	
	std::raise(SIGTERM);
} 


int main(int argc, char* argv[]){

	std::signal(SIGTSTP, signal_handler);   
	std::signal(SIGINT, signal_handler);
	std::signal(SIGQUIT, signal_handler); 
	std::signal(SIGUSR1, signal_handler1);
	std::signal(SIGUSR2, signal_handler2);

	int result = fork();

	if( result == 0 ) {
		int impar = 1;
		for(int x=0; x < 50; x++){
			std::cout << "Valor Impar: " << impar << "- PID:" << getpid() << std::endl;
			impar = impar + 2;
			sleep(1);
		}
	}

	else if( result > 0 ) {

		int fibo1 = 0;
		int fibo2= 1;
		int result2 = 0;
		for(int y=0; y < 50; y++){
			fibo1 = fibo2;
			fibo2 = result2;
			result2 = fibo1 + fibo2;
			std::cout << "Valor Fibonacci: " << result2 << " - PPIDE:" << getpid() << std::endl;
			sleep(1);
		}
		wait(NULL);
	}
	return EXIT_SUCCESS;
}
