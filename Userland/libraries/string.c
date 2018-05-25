#include "string.h"

int strlen(const char * str){
	int length = 0;
	while(str[length++] != '\0' );
	return length - 1;
}

boolean strcmp(char * str1, char * str2){
	int i;
	boolean equals = true;			
	
	for (i = 0; (str1[i] != 0 || str2[i] != 0) && equals == true; i++){	
		if(str1[i] != str2[i]){
			equals = false;
		}	
	}
	
	if(equals == false){
		return false;
	}

	if(str1[i] == str2[i] && equals){
		return true;
	}
	
	return false;
}

boolean strncmp(char * str1, char * str2, int num){
	int i = 0;
	while(i != num){
		if(*(str1 + i) != *(str2 + i))
			return false;
		i++;
	}
	return true;
}

char * strcpy(char * dest, char * source){
	int sourceLength = strlen(source);
	int i;

	for(i = 0; i <=  sourceLength; i++){
		*(dest + i) = *(source + i);
	}

	*(dest + i) = '\0';
	return dest;
}





