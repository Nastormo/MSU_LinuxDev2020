#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    char* str = (char*) malloc(sizeof(char) * 100);
    scanf("%s", str);
    sprintf(str + strlen(str), "\t%ld\n", strlen(str));
    printf("%s", str);
    free(str); 
    printf("First free\n");
    free(str);
    printf("Second free\n");

    return 0;
}