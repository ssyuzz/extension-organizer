#ifndef FUNC_H

#define FUNC_H

int createDir(char name[]);
void getAllFiles();
int checkIfDirExist(char dirName[]);
int moveFiles(char dirName[], char extension[]);
int exist(char origin[],char extension[]);
int replaceFiles(char fileName[], char extension[]);
#endif