#ifndef NOTES_H
#define NOTES_H
#include <stdbool.h>

extern char filePath[1024];

void setFilePath();
void printWelcomeInfo();
void printColored(const char *text, int color);
void showNotes();
void storeNoteInFile(const char* note);
void deleteStoredNote(char *noteNumber);

#endif