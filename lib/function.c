#include <direct.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <WinBase.h>
#include <stdlib.h>

#include "function.h"
#include "print_func.h"
#include "parser.h"
#include "utils.h"
#include <errno.h>

int createDir(char name[])
{
    time_t now = time(NULL);

    _mkdir(name);

    return 1;
}
int checkIfDirExist(char dirName[])
{
    WIN32_FIND_DATA fd;

    HANDLE h = FindFirstFile(dirName, &fd);

    if(h != NULL && fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
void getAllFiles()
{
    WIN32_FIND_DATA fd;

    HANDLE h = FindFirstFile("*", &fd);
    printA("[D] : Directory | [F] : Files\n");
    if(h != 0)
    {
        do{
            if(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                printA("[D] ");
                printA(fd.cFileName);
                printA("\n");
            }
            else{
                printA("[F] ");
                printA(fd.cFileName);
                printA(" : ");
                printUi(fd.nFileSizeLow);
                printA("KB");
                printA("\n");
            }
            
        }
        while(FindNextFile(h, &fd));
    }

    FindClose(h);
    
}
int checkFileExist(char fileName[])
{
    WIN32_FIND_DATA fd;

    HANDLE h = FindFirstFile(fileName, &fd);

    if(h != 0)
    {
        
        return 0;
    }
    else
    {
        return 1;
    }
    FindClose(h);

}
int exist(char origin[],char extension[])
{
    char opt[1024];
    char newFileName[1024];
    printf("%s already exist!!\n", origin);
    printf("[Replace | y(yes) | n(no) | a(all) ] : ");
    scanf("%s", opt);
    toLower(opt);
    if(strcmp(opt, "y") == 0 || strcmp(opt, "yes")==0)
    {
        return 0;
    }
    else if(strcmp(opt, "a") == 0 || strcmp(opt, "all") ==0)
    {
        return 2;
    }
    else if(strcmp(opt, "n") == 0 || strcmp(opt, "no") ==0)
    {
        return 1;
    }
    else 
    {
        printf("Invalid option!!! try again\n");
        exist(origin, extension);
    }
    
   
}
int replaceFiles(char fileName[], char extension[])
{
    WIN32_FIND_DATA fd;

    char editedfileName[512];

    strcpy(editedfileName, fileName);

    char *str1 = strtok(editedfileName,".");

    
    int i = 1;
    while(1)
    {
        char newFileName[512];

        char str2[1024];
        strcpy(newFileName, extension);

        sprintf(str2,"%s(%d)%s",str1,i,extension);
        
        sprintf(newFileName,"%s/%s",extension,str2);
        
        HANDLE h = FindFirstFile(newFileName, &fd);
        if(h == INVALID_HANDLE_VALUE)
        {

            MoveFileA(fileName, newFileName);
            return 1;
        }
        FindClose(h);
        i++;
    }
}
int moveFiles(char dirName[], char extension[])
{
    WIN32_FIND_DATA fd;

    int replace = 0;

    HANDLE h = FindFirstFile("*", &fd);
    int count = 0;
    if(h != INVALID_HANDLE_VALUE)
    {
        do{
            if(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                continue; // skip
            }
            else
            {   
                if(strstr(fd.cFileName, dirName))
                {
                    char newFileName[1024];
                    char newFileEkstension[1024];
                    copyStr(newFileName,dirName );
                    
                    if(getEx(fd.cFileName, dirName) == 1)
                    {
                        
                        copyDirStr(newFileName,fd.cFileName);
                        if(checkFileExist(newFileName) == 0)
                        {
                            
                            if(replace == 2)
                            {
                                MoveFileExA(fd.cFileName, newFileName, MOVEFILE_REPLACE_EXISTING);
                                count++;
                            }
                            else
                            {
                                replace = exist(fd.cFileName,extension);
                                if(replace == 0)
                                {
                                    MoveFileExA(fd.cFileName, newFileName, MOVEFILE_REPLACE_EXISTING);
                                    count++;
                                    
                                }
                                else if(replace == 1)
                                {
                                    count += replaceFiles(fd.cFileName, dirName);
                                }
                                else if(replace == 2)
                                {
                                    MoveFileExA(fd.cFileName, newFileName, MOVEFILE_REPLACE_EXISTING);
                                }
                            }
                        }
                        else
                        {
                            count++;
                            MoveFileA(fd.cFileName, newFileName);
                        }
                    }
                    
                }
             
            }
        }
        while(FindNextFileA(h, &fd));
        printf("Moved %d files\n", count);

    }
    FindClose(h);
  
}