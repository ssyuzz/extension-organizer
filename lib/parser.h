#ifndef CLI_H

#define CLI_H

int cliParser(int argc, char *argv[]);

void getTime(char name[], long long int time);

int getEx(char fileName[], char ex[]);

int str_comp(char text1[], char text2[]);

void copyStr(char dest[], char source[]);



#endif