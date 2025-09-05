#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>

char* filePath = "C:\\Users\\Gabriel\\desktop\\notes.txt";
FILE* fptr;

void showNotes();
void printColored(const char *text, int color);
void printWelcomeInfo();
void storeNoteInFile(const char* note);
void deleteStoredNote(char *noteNumber);

int main(int argc, char *argv[]){
    if(argc < 2){
        printWelcomeInfo();
    }
    else if(strcmp(argv[1], "show") == 0){
        showNotes();
    }
    else if(strcmp(argv[1], "add") == 0){
        if(argv[2] == NULL){
            printf("Error! No input found to be added.");
            return 0;
        }
        else{
            storeNoteInFile(argv[2]);
        }
    }
    else if(strcmp(argv[1], "delete") == 0){
        if(argv[2] == NULL){
            printf("Error! Please specify the number of the note as second argument.");
            return 0;
        }
        else{
            deleteStoredNote(argv[2]);
        }
    }

}

void printWelcomeInfo(){
    printf("\n");
    printf("Welcome ");
    printf("to ");
    printColored("Notes CLI", FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    printf("!\n");
    printf("\n");
    printColored("Commands: ", FOREGROUND_BLUE| FOREGROUND_INTENSITY);
    printf("show, add, delete\n");
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

void showNotes(){
    printf("\n");
    fptr = fopen(filePath, "r");

    if(fptr == NULL){
        printf("Error while attempting to open the file.\n");
        return;
    }

    char noteInLine[256];
    int i = 0;

    while(fgets(noteInLine, sizeof(noteInLine), fptr)){
        i++;
        char noteNumber[8];
        sprintf(noteNumber, "[%d]", i);
        
        char result[300];
        sprintf(result, "%s %s", noteNumber, noteInLine);
        
        printf("%s", result);
    }
    fclose(fptr);
}

void storeNoteInFile(const char* note){
    fptr = fopen(filePath, "a");

    if(fptr == NULL){
        printf("Error while attempting to open the file.\n");
        return;
    }

    fprintf(fptr, "%s\n", note); 
    fclose(fptr);
}

void deleteStoredNote(char* noteNumber){
    fptr = fopen(filePath, "r");
    int n = atoi(noteNumber);

    FILE *temp = fopen("temp_notes.txt", "w");
    if(temp == NULL){
        printf("Error opening temporary file.\n");
        fclose(temp);
        return;
    }

    char line[300];
    int count = 1;
    bool deleted = false;

    while(fgets(line, sizeof(line), fptr)){
        if(count != n){
            fputs(line, temp);
        }
        else{
            deleted = true;
        }
        count++;
    }

    fclose(fptr);
    fclose(temp);

    if(deleted){
        remove(filePath);
        rename("temp_notes.txt", filePath);
    }
    else{
        remove("temp_notes.txt");
        printf("Error! Note number not found.");
    }
}