#include <stdarg.h>
#include <string.h>
#include <types.h>
#include <stdlib.h>
#include <stdio.h>

#define FONT_WIDTH 10
#define FONT_HEIGHT 16
#define MAX_SIZE 2000

#define WIDTH 1024
#define HEIGHT 768

#define WAIT 100000000

void coordinates(){
	int x = (WIDTH / 2) - 1;
	int y = (HEIGHT / 2) - 1;
	int i, j;

	for (j = 0; j < HEIGHT; j++) {
		draw_pixel(x, j);
	}

	for(i = 0; i < WIDTH; i++){
		draw_pixel(i, y);
	}
}


void draw(int a, int b){
	int ejex;
	int ejey;
	int i;
	int y;
	coordinates();

	if(a == 0){
		for(i = 0; i < WIDTH; i++){
			draw_pixel(i, HEIGHT / 2 -  b);
		}	
	} else {
		for(i = -WIDTH / 2 + (WIDTH / 2 - HEIGHT / 2); i < WIDTH - (WIDTH / 2 - HEIGHT / 2); i++){
			y = a * i + b;
			ejex = i + (2 * (WIDTH / 2 - HEIGHT / 2) + (WIDTH / 2 - 2 * (WIDTH / 2 - HEIGHT / 2)));
			ejey = HEIGHT / 2 - y;
		
			draw_pixel(ejex  , ejey);
		}
	}
	while(i < WAIT){
		i++;
	}
}

int main(void){
	int a = 0; 
	int b = 0;
	printf("\n--- LINEAR GRAPH ---\n");
	nextLine();
	printf("f(x) = ax + b\n");
	nextLine();
	printf(" - Input 'a': ");
	
	while(getNum(&a) == 1)
		printf("\nError: Incorrect parameter\n");
	
	printf("\n");
	printf(" - Input 'b': ");
	while(getNum(&b) == 1)
		printf("\nError: Incorrect parameter\n");
	

	clear_screen();
	
	draw(a,b);
	
	clear_screen();
	clear_buffer();
	exitProcess();
	return 0;
}









