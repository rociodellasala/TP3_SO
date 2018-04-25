#include <stdarg.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include <types.h>
#include <stdlib.h>

#define FONT_WIDTH 10
#define FONT_HEIGHT 16
#define MAX_SIZE 2000
#define exit 2
#define WIDTH 1024
#define HEIGHT 768

#include "./include/stdio.h"

int main (void){
	clear_screen();
	int a = 0; 
	int b = 0;
	int q = 0; //Seria mi c pero como 'c' ya lo uso para getchar uso q
	int y;
  
	printf("f(x) = ax^2 + bx + c\n");
	printf("Input'a':\n");

  	if(getNum(&a) == 1){
		printf("Error: Incorrect parameter\n");
		int j = 0;
		while(j < 50000000){
			j++;
		}

		return 0;
	}

	printf("\n");
	printf("Input 'b':\n");

	if(getNum(&b) == 1){
		printf("Error: Incorrect parameter\n");
		int j = 0;
		while(j < 50000000){
			j++;
		}

		return 0;
	}

	printf("\n");
	printf("Input 'c':\n");

	if(getNum(&q) == 1){
		printf("Error: Incorrect parameter\n");
		int j = 0;
		while(j < 50000000){
			j++;
		}

		return 0;
	}

	printf("\n");

	clear_screen();
	coordinates();

	int ejex;
	int ejey;

	if (a != 0){
		for(int i = -(WIDTH / 2 - HEIGHT / 2); i < WIDTH - (WIDTH / 2 - HEIGHT / 2); i++){
			y = a * i * i + b * i + q;
			ejex = i + (2 * (WIDTH / 2 - HEIGHT / 2) + (WIDTH / 2 - 2 * (WIDTH / 2 - HEIGHT / 2)));
			ejey = HEIGHT / 2 - y / 25;
			draw_pixel(ejex, ejey);
		}
	}else{
		if(b == 0){
			for(int i = 0; i < WIDTH; i++){
				draw_pixel(i, HEIGHT / 2 -  q);
			}	
		}else{
			for(int i = -WIDTH / 2 + (WIDTH / 2 - HEIGHT / 2); i < WIDTH - (WIDTH / 2 - HEIGHT / 2); i++){
					y = b * i + q;
					ejex = i + (2 * (WIDTH / 2 - HEIGHT / 2) + (WIDTH / 2 - 2 * (WIDTH / 2 - HEIGHT / 2)));
					ejey = HEIGHT / 2 - y;
			
					draw_pixel(ejex, ejey);
			}
		}
	}

	int i = 0;

	while(i < 500000000){
		i++;
	}

	return 0;
}

void coordinates(){
	int x = (WIDTH / 2) - 1;
	int y = (HEIGHT / 2) - 1;

	for (int j = 0; j < HEIGHT; j++){
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

	while(state != exit) {
		if ((c = getchar()) != EOF){
    		if(c == '\n'){
	      		if(index == 0){
					return 1; //error
				}
	      		
	      		buffer[index] = 0;
				state = exit;

			}else if((c < '0' || c > '9' ) && c != '-'){
				return 1; //error
			}else{
		      	buffer[index] = c;
		      	index++;
		   		buffer[index] = 0;
		  		putchar(buffer[index-1]);	
	  		}	   	
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








