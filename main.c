#include <stdio.h>
#include <string.h>

char* filePath = "C:\\Users\\Gabriel\\desktop\\notes.txt";
FILE* fptr;

void setKeyValuePair(const char* key, const char* value);
char* getKeyValue(const char* key);

int main(void){
    printf("Welcome to Notes CLI!\n");
    setKeyValuePair("1", "add sound effects to Jufofu promo video");
    char* result = getKeyValue("1");
    printf("%s\n", result);
}

void setKeyValuePair(const char* key, const char* value){
    fptr = fopen(filePath, "a");

    if(fptr == NULL){
        printf("Error while attempting to open the file.\n");
        return;
    }

    fprintf(fptr, "%s=%s\n", key, value); 
    fclose(fptr);
}

char* getKeyValue(const char* searchKey){
    fptr = fopen(filePath, "r");

    if(fptr == NULL){
        printf("Error while attempting to open the file.\n");
        return NULL;
    }

    char line[256];


    while(fgets(line, sizeof(line), fptr)){
        char* key = strtok(line, "=");
        char* value = strtok(NULL, "=");

        if(strcmp(key, searchKey) == 0){
            char* val = strdup(value);
            fclose(fptr);
            return val;
        }
    }

    fclose(fptr);
};