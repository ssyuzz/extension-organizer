#include "print_func.h"

#include <stdio.h>


void printHelp()
{
    printf("=====================================\n");
    printf("        File Organizer Help\n");
    printf("=====================================\n");
    printf("Usage:\n");
    printf("    app.exe [option] [directory]\n\n");

    printf("Options:\n");
    printf("    -h              Show this help message\n");
    printf("    -l              List all files in a directory\n");
    printf("    -f              Organize files by extension\n");
    printf("    -v              Show program version\n");
}

void printA(char text[])
{
    printf(text);
}

void printI(int num)
{
    printf("%d", &num);
}

void printUi(long unsigned int num)
{
    printf("%lu", num);
}
void copyDirStr(char text[], char text1[])
{

    sprintf(text,"%s/%s",text, text1);
}

