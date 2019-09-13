#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int* getNull()
{
    return NULL;
}

void func(int *p)
{

}

int main()
{
    char buffer[5];
    char shortStr[10];
    char longStr[30];
    char *text;
    char *bufferOnHeap = (char *)malloc(5);

    // Buffer overflow audit
    strcpy(shortStr, longStr);      // write large string into small buffer.
    strncpy(text, shortStr, 100);   // copy large from small buffer.
    memcpy(text, shortStr, 100);    // copy large from small buffer.
    strcat(text, longStr);          // write into buffer with unknown size.
    strncat(text, shortStr, 100);   // copy large from small buffer into unknown buffer.
    sprintf(shortStr, "12345678901234567890123456789\n"); // write large string constant into small buffer.
    fscanf(stdin, "012345678910\n", &buffer);             // write large string constant into small buffer.
    sscanf(longStr, "%s", &shortStr);                     // read large string into small buffer
    
    // Heap overflow
    vsprintf(bufferOnHeap, "1\n", NULL);    // write string constant into unknown buffer on heap.
    gets(bufferOnHeap);                     // write into buffer on heap.
    read(stdin, bufferOnHeap, 10);          // write into small buffer on heap.


    // Interger overflow audit
    int longInt = 5;
    short shortInt = 10;
    unsigned int size = 0;

    shortInt = longInt;                     // Interger size overflow
    longInt = (long long)shortInt;          // Ingerger size overflow
    memcpy(longStr, shortStr, shortInt);    // Interger sign overflow
    longInt = shortInt;                     // No vulnerability
    memcpy(longStr, shortStr, size);        // Buffer overflow only

    // Null audit
    char *p = NULL;
    int *ptr = getNull();
    char *notNull = (char *)malloc(sizeof(char) * 100);

    func(p);            // Use null pointer as parameter.
    func(notNull);      // No vulnerability
    int x = *ptr + 6; // Dereference null pointer.
    x = *notNull + 6;

    // Format string audit
    printf("%d %s %s %s", *ptr, buffer, text, longInt);    // use %s for int
    printf("%d %s %s %s", *ptr);   // More format strings.
    
    return 0;
}