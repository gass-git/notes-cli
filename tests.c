#include "unity/unity.h"
#include "notes.h"
#include <stdio.h>
#include <string.h>

extern char filePath[1024];

void setUp(void) {
    snprintf(filePath, sizeof(filePath), "test-file.txt");
    FILE* f = fopen(filePath, "w");

    if (f) {
        fclose(f);
    }
}

void tearDown(void) {
    remove(filePath);
}

void test_storeNoteInFile_writesNote(void) {
    storeNoteInFile("Hello test note!");
    FILE* f = fopen(filePath, "r");
    TEST_ASSERT_NOT_NULL(f);

    char buffer[256];
    fgets(buffer, sizeof(buffer), f);
    fclose(f);

    buffer[strcspn(buffer, "\n")] = 0;
    TEST_ASSERT_EQUAL_STRING("Hello test note!", buffer);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_storeNoteInFile_writesNote);
    return UNITY_END();
}
