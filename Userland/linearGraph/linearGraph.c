#include <stdarg.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include <types.h>
#include <stdlib.h>
#include "./include/stdio.h"

#define FONT_WIDTH 10
#define FONT_HEIGHT 16
#define MAX_SIZE 2000

#define WIDTH 1024
#define HEIGHT 768

void exit(){
	int80(14,0,0,0,0);
}

int main (void){
	//clear_screen();
	int y;
	int a = 0; 
	int b = 0;
	printf("\n");
	printf("f(x) = ax + b\n");
	printf("Input 'a': ");
  	char c;
  	int state;
  	char * str;
	
	while(getNum(&a) == 1){
		printf("\nError: Incorrect parameter\n");
	}
	printf("\n");
	printf("Input 'b': ");
	while(getNum(&b) == 1){
		printf("\nError: Incorrect parameter\n");
	}

	clear_screen();
	
	coordinates();
	int ejex;
	int ejey;

	if(a == 0){
		for(int i = 0; i < WIDTH; i++){
			draw_pixel(i, HEIGHT / 2 -  b);
		}	
	}else{
		for(int i = -WIDTH / 2 + (WIDTH / 2 - HEIGHT / 2); i < WIDTH - (WIDTH / 2 - HEIGHT / 2); i++){
			y = a * i + b;
			ejex = i + (2 * (WIDTH / 2 - HEIGHT / 2) + (WIDTH / 2 - 2 * (WIDTH / 2 - HEIGHT / 2)));
			ejey = HEIGHT / 2 - y;
		
			draw_pixel(ejex  , ejey);
		}
	}

	int i = 0;
	
	while(i < 50000000){
		i++;
	}
	clear_screen();
	exit();
}

void coordinates(){
	int x = (WIDTH / 2) - 1;
	int y = (HEIGHT / 2) - 1;

	for (int j = 0; j < HEIGHT; j++) {
		draw_pixel(x, j);
	}

	for(int i = 0; i < WIDTH; i++){
		draw_pixel(i, y);
	}
}

int getNum(int * a){
	int state = 0;
	char c;
	char buffer[MAX_SIZE];
	int index = 0;

	while(state != exit){
		if ((c = getchar()) != EOF){
			if(c == '\n'){
      			if(index == 0){
					return 1; //error
				}
      			
      			buffer[index] = 0;
				state = exit;
			} else if(c != ' '){
	      		buffer[index] = c;
	      		index++;
	      		buffer[index] = 0;
	     		putchar(buffer[index - 1]);	
	  		} /*else if( c == ' '){
	  			printf("HOLA"); // --------------------------- MAGIA CAMBIAR ----------------------------
	  		}*/ else if((c < '0' || c > '9' ) && c != '-' && c != ' ') // problema del getchar, same en shell
				return 1; //error
		}	
	}

	if(buffer[0] == '-'){
		for(int k = 1; k < index; k++){
			buffer[k] = buffer[k] - '0';
			*a = (*a) * 10 + buffer[k];
		}

		*a = (-1) * (*a);
		return 0;
	}else{
		for(int k = 0; k < index; k++){
			buffer[k] = buffer[k] - '0';
			*a = (*a) * 10 + buffer[k];
		}

		return 0;
	}
}








