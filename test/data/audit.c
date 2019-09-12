#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    char *text;
    text = (char *)malloc(100000);
    char buffer[5];
    char str1[10], str2[30];
    strcpy(str1, str2);
    strncpy(text, str1, 100);
    memcpy(text, str1, 100);
    strcat(text, str1);
    strncat(text, str1, 100);
    sprintf(str1, "12345678901234567890123456789\n");
    vsprintf(str1, "1\n", NULL);
    gets(text);
    read(stdin, buffer, 10);
    sscanf(str1, "012345678910\n", &buffer);
    fscanf(stdin, "012345678910\n", &buffer);

    int int32 = 5;
    short int16 = 10;
    int16 = int32;

    char *p = NULL;
    gets(p);

    printf("%d %s %s %s", p, buffer, text, int32);
    printf("%d %s %s %s", p);

    return 0;
}