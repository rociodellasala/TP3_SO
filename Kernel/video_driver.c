#include <types.h>
#include <font.h>
#include <video_driver.h>
#define FONT_WIDTH     10
#define FONT_HEIGHT    16
//http://wiki.osdev.org/VESA_Video_Modes

#pragma pack(push)
#pragma pack(1)

typedef struct {

	  word attributes;
	  byte winA,winB;
	  word granularity;
	  word winsize;
	  word segmentA, segmentB;
	  dword farptr;
	  word pitch; // bpp 

	  word Xres, Yres;
	  byte Wchar, Ychar, planes, bpp, banks;
	  byte memory_model, bank_size, image_pages;
	  byte reserved0;

	  byte red_mask, red_position;
	  byte green_mask, green_position;
	  byte blue_mask, blue_position;
	  byte rsv_mask, rsv_position;
	  byte directcolor_attributes;

	  dword physbase;  // Linear Framebuffer
	  dword reserved1;
	  word reserved2;

} ModeInfoBlock;
#pragma pack(pop)


//http://wiki.osdev.org/ing_In_Protected_Mode
/* Start of table */
static ModeInfoBlock * screen_info = (ModeInfoBlock *) 0x5C00; 
static byte * screen;
static int pitch;
static int pixel_width;
static int xres, yres;
static int buffer_position = 0;
static int buffer_max_per_line;
static int buffer_max_per_column;
static int currColor;


void
start_video_mode(){

	screen = (byte *) (qword) screen_info -> physbase;

	pitch = screen_info -> pitch;
	pixel_width = screen_info -> bpp / 8;
	xres = screen_info -> Xres;
	yres = screen_info -> Yres;
  	buffer_max_per_line = xres / FONT_WIDTH;
  	buffer_max_per_column = yres / FONT_HEIGHT;
 	currColor = 0xFFFFFF;
}

void
draw_pixel(int x, int y){
	unsigned pos = x * pixel_width + y * pitch;
    	screen[pos] = currColor & 255;              // BLUE
    	screen[pos + 1] = (currColor >> 8) & 255;   // GREEN
    	screen[pos + 2] = (currColor >> 16) & 255;  // RED
}


void
draw_char(unsigned char c, int x, int y){
	int cx, cy;
	int mask[8] = {1, 2, 4, 8, 16, 32, 64, 128};
	unsigned char * glyph = font[c - 32];

	for(cy = 0; cy < 13; cy++){
		for(cx = 0; cx < 8; cx++){
			if(glyph[cy] & mask[cx]){
				draw_pixel(x + 8 - cx, y + 13 - cy);
			}
		}
	}
}

void
draw_string(char * str, int x, int y){
	int i = 0;

	while(str[i] != '\0'){
		draw_char(str[i], x + (10 * i), y);
   	 	i++;
	}
}

void
draw_filled_rectangle(int x1, int y1, int x2, int y2, int color){
	int i, j;
	byte blue = color & 255;
	byte green = (color >> 8 ) & 255;
	byte red = (color >> 16) & 255;
	int pos1 = x1 * pixel_width + y1 * pitch;
	byte * draw = &screen[pos1];

	for (i = 0; i <= y2 - y1; i++){
	  for (j = 0 ;j <= x2 - x1; j++){
	    draw[pixel_width * j] = blue;
	    draw[pixel_width * j + 1] = green;
	    draw[pixel_width * j + 2] = red;
	  }
	 draw += pitch;
	}
}

void
clear_screen(){
  	int i, j;
 	byte * draw = screen;
  	buffer_position = 0;
	
	for ( i = 0; i <= yres; i++){
	  for( j = 0; j <= xres; j++){
	    draw[pixel_width * j] = 0;
	    draw[pixel_width * j + 1 ] = 0;
	    draw[pixel_width * j + 2 ] = 0;
	  }
	draw += pitch;
	}
}

void
print_char(unsigned char c){
  	if(c == '\n'){
    	nextLine();
    	return;
  	}
  
	draw_char(c, (buffer_position % buffer_max_per_line) * FONT_WIDTH, (buffer_position / buffer_max_per_line) * FONT_HEIGHT);
  
	if ( buffer_position / buffer_max_per_line == (buffer_max_per_column) ){
   		move_screen();
    	buffer_position -= buffer_max_per_line;
  	}
  
	buffer_position++;
}

void
print_string(const char * str){
  	int i = 0;
 	
	while(str[i] != '\0'){
    		print_char(str[i]);
    		i++;
  	}
}

void
print_string_by_length(const char * str, int length){
  	int i = 0;
  
	while( i < length){
    		print_char(str[i]);
    		i++;
  	}
}

void
delete(){
  	if ( buffer_position > 0){
		int x = ((buffer_position - 1) % buffer_max_per_line) * FONT_WIDTH;
	   	int y = ((buffer_position - 1) / buffer_max_per_line) * FONT_HEIGHT;
	    draw_filled_rectangle(x, y, x + FONT_WIDTH, y + FONT_HEIGHT, 0x000000);
	    buffer_position--;
  	}
}

void
deleteLine(int line){
  	draw_filled_rectangle(0, line * FONT_HEIGHT + 1, xres, line * (1 + FONT_HEIGHT) + 1, 0x000000);
  	buffer_position -= (buffer_position % buffer_max_per_line);
}

void
nextLine(){
	if ( buffer_position / buffer_max_per_line == (buffer_max_per_column - 3) ){
		move_screen();
  	} else {
		buffer_position += buffer_max_per_line - buffer_position % buffer_max_per_line;
	}
}

void
move_screen(){
	int i;
	int pos1 = 0;
 	int pos2 = FONT_HEIGHT * pitch;
  	
	for ( i = 0; i < xres * yres - buffer_max_per_line; i++ ){
      	screen[pos1] = screen[pos2];
     	screen[pos1 + 1] = screen[pos2 + 1];
      	screen[pos1 + 2] = screen[pos2 + 2];
      	pos1 += pixel_width;
      	pos2 += pixel_width;
 	}

	deleteLine(buffer_position / buffer_max_per_line );
}


void
print_line(int x1, int y1, int x2, int y2){
	double dx = x2 - x1;
	double dy = y2 - y1;
	int x, y;
	  
	for ( x = x1; x <= x2; x++){
		y = y1 + dy * (x - x1) / dx;
		draw_pixel(x, y);
	}
}

void
changeFontColor(int color){
  	currColor = color;
}

void
print_int(qword n){
	char s[16] = {0};
	int digits = countDigits(n) - 1;

	/* Calculate character */
	while(digits >= 0){
		s[digits] = n % 10 + '0';
		n /= 10;
		digits--;
	}

	/* Print array */
	print_string(s);
}

int
countDigits(qword n){
	int i = 1;

	while(n >= 10){
		n /= 10;
		i++;
	}

	return i;
}

void
print_menu(){
	clear_screen();
	print_string("1: SHELL");
	nextLine();
	print_string("2: LINEAR GRAPH");
	nextLine();
	print_string("3: PARABOLIC GRAPH");
	nextLine();
}

