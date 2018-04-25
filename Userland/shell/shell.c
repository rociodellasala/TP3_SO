#include <types.h>
#include <shell.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


int main() {
	clear_terminal();
	start_shell();
	return 0;
}

void start_shell() {
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
			}else if(c == '\n'){
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
					case 3:
						isFirst = true;
						break;
				}
  			}else {
	      		buffer[index] = c;
				putchar(buffer[index]);		      		
				index++;
	      		buffer[index] = 0;
  			}	   	
		}	
	}
}

int get_command(char * buffer){
	int x = 0;
	char function[15];

	while(buffer[x] != ' ' && buffer[x] != 0){
		function[x] = buffer[x];
		x++;
		if(x > 14)
			return 1;		
	}
	
	function[x] = 0;
	
	return call_command(function, buffer + x + 1);
}

int call_command(char * function, char * parameter){
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
	} else if(strcmp(function, "sleep")){
		sleep();
		return 0;
	}	else if(strcmp(function, "time")){
		time();
		return 0;
	} else if(strcmp(function, "divideByZero")){		
		divide_by_zero();
	} else if(strcmp(function, "invalidOpcode")){
		invalid_opcode();
	} else if(strcmp(function, "exit")){			
		return 2;
	}
		return 1;
}

void printHelp(){
	clear_screen();
	printf("HELP -- Manual to interact with the terminal: \n\n");
	printf("echo [message]:         Prints message.\n");
	printf("font [color]:           Changes font color, ex: blue, red, yellow, white or violet.\n");	
	printf("cls:                    Clears screen.\n");	
	printf("help:                   Displays manual.\n");
	printf("sleep:                  The console waits for a while.\n");
	printf("time:                   Displays the current time.\n");
	printf("divideByZero:           Makes an integer division to show how zero exception works.\n");
	printf("invalidOpcode:          Shows how invalid opcode exception works by calling an undefined instruction.\n");
	printf("exit:                   Goes back and displays the menu.\n");
}

void echo(char * buffer){
	nextLine();		
	printf(buffer);
}





