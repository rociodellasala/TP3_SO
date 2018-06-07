#include <stdlib.h>
#include <mutex.h>
#include <types.h>
#include <stdio.h>
#include <pipe.h>
#include <string.h>

void getWord(unsigned char * vector,char * information);
void getOption(int * option);
void pipeProcess(char * process,char * first, char * second, char * result);

int main (void){
	int option = 0;
	char result[50] = {0};
	char * one = "Hola";
	char * two = "chau";

	clear_screen();
	printf("In this program we are going to do some test over pipes using proA proB and proC\n");
	printf("We are gonna need two words\n\n");


	printf("Words chosen: %s  |||  %s \n", one,two);
	
	printf("Now we have to choose how to pipe proA, proB and proC\n");
	printf("Option one: A -> C -> A -> B -> A\n");
	printf("Option two: A -> B -> A -> C -> A\n");

	getOption(&option);

	strcat(result,one);

	if(option == 1){
		pipeProcess("proC",one,two,result);
		pipeProcess("proB",one,two,result);
	}
	else{
		pipeProcess("proB",one,two,result);
		pipeProcess("proC",one,two,result);
	}

	strcat(result,two);

	printf("The final word was: %s\n", result);
	exitProcess();
	return 0;
}

void pipeProcess(char * process,char * first, char * second, char * result){
	char word[8];
	int pipePID;
	int childPID;


	childPID = startProcess(process);

	pipePID = pipe(childPID);

	read(pipePID,word,5);

	strcat(result,word);

}


void getWord(unsigned char * vector,char * information){
	int i = 0;
	int state = 1;
	unsigned char c;

	printf("\nPlease enter word %s: ", information);

	clear_buffer();
	while(state){
		if( (c = getchar()) == '\n')
			state = 0;
		else
			vector[i++] = c;
	}

	if(i == 0)
		getWord(vector,information);
	else
		return;
}

void getOption(int * option){
	do{
		*option = 0;
		printf("\nPlease enter an option: ");
		getNum(option);
	}while(*option != 1 && *option != 2);
	return;
}
