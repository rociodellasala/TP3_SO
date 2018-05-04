#include <types.h>
#include <string.h>

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




