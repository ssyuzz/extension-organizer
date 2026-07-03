#include "parser.h"
#include "print_func.h"
#include "function.h"
#include <string.h>

int cliParser(int argc, char *argv[])
{
    if(argc == 1)
        return 0;
    int active = 0;
    char dest[512];

    for(int i=1; i<argc; i++)
    {
        char ex[] = ".";
        if(strcmp(argv[i], "-h") == 0)
        {
            printHelp();
        }
        else if(strcmp(argv[i], "-f") == 0 && strstr(argv[i+1], ex) != NULL)
        {
            char dirName[1024];
            strcpy(dirName, argv[i+1]);
            int check = checkIfDirExist(dirName);
            if(check == 0)
            {
                createDir(dirName);
                return moveFiles(dirName, argv[i+1]);
                
            }
            else
            {
                return moveFiles(dirName, argv[i+1]);
            }
            active = 1;
        }
        else if(strcmp(argv[i], "-l") == 0)
        {
            getAllFiles();
        }
        
    }
 
}
void copyStr(char dest[], char source[])
{
    strcpy(dest, source);
}

int str_comp(char text1[], char text2[])
{
    return strcmp(text1, text2);
}
int getEx(char fileName[], char ex[])
{
    char *str = strrchr(fileName, '.');
    
    if(str == NULL)
        return 0;
    
    
    if(strcmp(str, ex) == 0)
    {
        return 1;
    }
    return 0;
    
}
