#include <string.h>

void toLower(char text[])
{
    int n = strlen(text);
    for(int i=0; i<n; i++)
    {
        if(text[i] >= 'A' && text[i] <= 'Z')
        {
            text[i] = text[i] + 32;
        }
    }
    return;
}