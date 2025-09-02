#include <stdio.h>

char* filePath = "C:\\Users\\Gabriel\\desktop\\notes.txt";
FILE* fptr;

void addKeyValuePair(const char* key, const char* value);

int main(void){
    printf("Welcome to Notes CLI!");
    addKeyValuePair("1", "add sound effects to Jufofu promo video");
}

void addKeyValuePair(const char* key, const char* value){
    fptr = fopen(filePath, "a");

    if(fptr == NULL){
        printf("There was an error while attempting to open the file.\n");
        return;
    }

    fprintf(fptr, "%s=%s\n", key, value); 
    fclose(fptr);
}