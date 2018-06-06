#include "types.h"
#include "string.h"
#include "converter.h"

int strlen(const char * str){
	int length = 0;
	while(str[length++] != '\0');
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

char * strcpy(char * dest,const char * source){
	int sourceLength = strlen(source);
	int i;

	for(i = 0; i <=  sourceLength; i++){
		*(dest + i) = *(source + i);
	}

	*(dest + i) = '\0';
	return dest;
}

char * strncpy(char * dest, const char * source, int charsToCopy){
	int i;
	for(i = 0; i <  charsToCopy; i++){
		*(dest + i) = *(source + i);
	}

	*(dest + i) = '\0';
	return dest;
}

char charAtPos(char * str, int i){
	char * aux = str;
	int j = 0;

	while(*aux != '\0' && j < i){
		j++;
		aux++;	
	}
	
	return *aux;
}

char * strcat(char * dest, const char * source){
	int i;
	int j;
	int destLengh = strlen(dest);
	int sourceLength = strlen(source);

	for(i = 0; i <  destLengh; i++){
		if(dest[i] == '\0')
			break;
	}

	for(j = 0; j <  sourceLength; j++){
		dest[i] = source[j];
		i++;
	}

	dest[i] = '\0';

	return dest;
}

void getNodeInfo(char * vector, char * processName, int pid, char * processInfo){
	char pidString[5] = {0};
	intToString(pid,pidString);
	strcat(vector,processInfo);
	strcat(vector,processName);
	strcat(vector," PID: ");
	strcat(vector,pidString);
}