#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <windows.h>

char* filePath = "C:\\Users\\Gabriel\\desktop\\notes.txt";
FILE* fptr;

void setKeyValuePair(const char* key, const char* value);
char* getKeyValue(const char* searchKey);
void showNotes();
bool keyIsAvailable(const char* searchKey);
void printHeader();
void printColored(const char *text, int color);

int main(void){
    printHeader();
    showNotes();
    printf("\n");
    printf("\n");
}

void printHeader(){
    printf("\n");
    printf("Welcome ");
    printf("to ");
    printColored("Notes CLI", FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    printf("!\n");
    printf("\n");
}

void printColored(const char *text, int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    WORD saved_attributes = consoleInfo.wAttributes;

    SetConsoleTextAttribute(hConsole, color);
    printf("%s", text);

    SetConsoleTextAttribute(hConsole, saved_attributes);
}

bool keyIsAvailable(const char* searchKey){
    fptr = fopen(filePath, "r");

    if(fptr == NULL){
        printf("Error while attempting to open the file.\n");
        return false;
    }

    char line[256];

    while(fgets(line, sizeof(line), fptr)){
        char* key;
        key = strtok(line, "=");

        if(strcmp(key, searchKey) == 0){
            return false;
        }
    }

    return true;
}

void showNotes(){
    fptr = fopen(filePath, "r");

    if(fptr == NULL){
        printf("Error while attempting to open the file.\n");
        return;
    }

    char line[256];

    while(fgets(line, sizeof(line), fptr)){
        char* ptr = &line[0];
        memmove(ptr + 1, ptr, strlen(ptr) + 1);

        ptr[0] = '[';
        ptr = strchr(line, '=');

        if(ptr != NULL){
            memmove(ptr + 2, ptr + 1, strlen(ptr) + 1);

            ptr[0] = ']';
            ptr[1] = ' ';
            ptr[2] = toupper(ptr[2]);
        }
        
        printf("%s", line);
    }

    fclose(fptr);
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

