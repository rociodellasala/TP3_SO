#include "./include/exception.h"
#include "./include/shell.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <types.h>

int main(){	
	clear_terminal();
	start_shell();
	return 0;
}

void start_shell(){
	char buffer[MAX_SIZE];
  	int index;
  	char c;
  	int state;
  	boolean isFirst = true;
  	
	while(state != exit){
			
		if(isFirst == true){
			index = 0;
			buffer[0] = 0;
			isFirst = false;
		}

		if ((c = getchar()) != EOF){
			
			if(c == '\b'){
				if(index != 0){
					index--;
	    			buffer[index] = 0;
	    			backspace();
				}
			} else if(c == '\n' && index == 0){
				nextTerminalLine();		
			} else if(c == '\n'){
      			buffer[index] = 0;
      			state = get_command(buffer);
				
				switch(state){
					case 0:
						nextTerminalLine();
						index = 0;
						buffer[0] = 0;
						break;
					case 1:
						nextTerminalLine();
						printf("Unknown command: Type help to see the different functionalities");
						nextTerminalLine();
						index = 0;
						buffer[0] = 0;
						break;
					case 2:
						state = exit;
					case 3:
						isFirst = true;
						break;
				}
  			} else if(c != ' '){
	      		buffer[index] = c;
				putchar(buffer[index]);
				index++;		      		
	      		buffer[index] = 0;
  			} else { 
	      		buffer[index] = c; 
				putchar(buffer[index]);
				index++;		      		
	      		buffer[index] = 0;
  			} 
		}	
	}

	exitProcess();
}

int get_command(char * buffer){
	int x = 0;
	char function[MAX_COMMAND_SIZE];

	while(buffer[x] != ' ' && buffer[x] != 0){
		function[x] = buffer[x];
		x++;
		if(x > MAX_COMMAND_SIZE)
			return 1;		
	}
	
	function[x] = 0;
	
	return call_command(function, buffer + x + 1);
}


int call_command(char * function, char * parameter){
	int ret;
	if(strcmp(function, "echo")){
		echo(parameter);
		return 0;
	} else if(strcmp(function, "font")){
		return changeFontColor(parameter);
	} else if(strcmp(function, "cls")){
		 clear_terminal();
		 return 3;
	} else if(strcmp(function, "help")){
		printHelp(); 
		return 0;
	} else if(strcmp(function, "time")){
		time();
		return 0;
	}else if(strcmp(function, "divideByZero")){		
		divide_by_zero();
	} else if(strcmp(function, "invalidOpcode")){
		invalid_opcode();
	} else if(strncmp(function, "./", 2)){
		ret = startProcess(function + 2);
		if(ret == -1)
			return 1;
		else 
			return 3;
	} else if(strcmp(function, "ps")){
		ps();
		return 0;	
	} else if(strcmp(function, "ls")){
		ls();
		return 0;	
	} else if(strncmp(function, "kill", 4)){
		killProgram(stringToInt(parameter));
		return 0;	
	} else if(strcmp(function,"header")){
		printHeader();
		return 0;
	} else if(strcmp(function,"buddyInfo")){
		printMemoryInformation();
		return 0;
	} else if(strcmp(function,"memInfo")){
		printMemoryInformationVertical();
		return 0;
	} else if(strcmp(function,"processTree")){
		printProcessTree();
		return 0;
	} else if(strcmp(function, "exit")){
		return 2;
	}
	return 1;
}

void printHelp(){
	clear_screen();
	printf("--- HELP --- Manual to interact with the terminal: \n\n");
	printf("cls:                    Clears screen.\n");	
	printf("divideByZero:           Makes an integer division to show how zero exception works.\n");
	printf("echo [message]:         Prints message.\n");
	printf("exit:                   Goes back and displays the menu.\n");
	printf("font [color]:           Changes font color, ex: blue, red, yellow, white or violet.\n");	
	printf("help:                   Displays manual.\n");
	printf("invalidOpcode:          Shows how invalid opcode exception works by calling an undefined instruction.\n");
	printf("ls:                     Displays runnable programs\n");
	printf("ps:                     Displays a snapshot of the status of currently running processes.\n");
	printf("time:                   Displays the current time.\n");
	printf("kill [pid]:             Terminates a specific process by PID\n");
	printf("buddyInfo               Prints buddy allocator tree\n");
	printf("memInfo                 Prints memory state\n");
	printf("processTree             Prints all process like a tree structure\n");
}




