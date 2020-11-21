#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_ROMAN 3999
#define SYMBOL_ROMAN 28
#define MAX_STRING 80

static int arabValue[SYMBOL_ROMAN] = {
    1000, //0
    900,  //1
    800,  //2
    700,  //3
    600,  //4
    500,  //5
    400,  //6
    300,  //7
    200,  //8
    100,  //9
    90,   //10
    80,   //11
    70,   //12
    60,   //13
    50,   //14
    40,   //15
    30,   //16
    20,   //17
    10,   //18
    9,    //19
    8,    //20
    7,    //21
    6,    //22
    5,    //23
    4,    //24
    3,    //25
    2,    //26
    1     //27
};

static char romanValue[SYMBOL_ROMAN][MAX_STRING] = {
    "M",    //0
    "CM",   //1
    "DCCC", //2
    "DCC",  //3
    "DC",   //4
    "D",    //5
    "CD",   //6
    "CCC",  //7
    "CC",   //8
    "C",    //9
    "XC",   //10
    "LXXX", //11
    "LXX",  //12
    "LX",   //13
    "L",    //14
    "XL",   //15
    "XXX",  //16
    "XX",   //17
    "X",    //18
    "IX",   //19
    "VIII", //20
    "VII",  //21
    "VI",   //22
    "V",    //23
    "IV",   //24
    "III",  //25
    "II",   //26
    "I"     //27
};

char* int_to_roman(int n) 
{
    if (n < 0 || n > MAX_ROMAN) return NULL;
    char* romanN = malloc(MAX_STRING);
    int curN = 0;
    int shift = 0;
    while(curN < SYMBOL_ROMAN) {
        if(n >= arabValue[curN]) {
            n -= arabValue[curN];
            sprintf(romanN + shift, "%s", romanValue[curN]);
            shift += strlen(romanValue[curN]);
        } else {
            curN++;
        }
    }
    return romanN;
}

int roman_to_int(char* romanN) {
    int n = 0;
    int curN = 0;
    int shift = 0;
    while(curN < SYMBOL_ROMAN) {
        if(romanN + shift == strstr(romanN + shift, romanValue[curN])) {
            n += arabValue[curN];
            shift += strlen(romanValue[curN]);
        } else {
            curN++;
        }
    }
    return n;
}

int main(int argc, char **argv)
{
    for (int i = 1; i <= MAX_ROMAN; i++) {
        char *romanN = int_to_roman(i);
        int new_number = roman_to_int(romanN);
        if(new_number != i)
            printf("%d %s %d\n", i, romanN, new_number == i);
    }
}