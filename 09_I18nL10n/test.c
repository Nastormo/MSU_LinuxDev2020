#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    for (int idealNumber = 1; idealNumber <= 100; idealNumber++) {
        int left = 1;
        int right = 100;
        int middle;
        while(right != left) {
            middle = (left + right) / 2;
            printf("%d %d %d %d\n", left, middle, right, idealNumber);
            if (middle < idealNumber) {
                left = middle + 1;
            } else if (middle >= idealNumber) {
                right = middle;
            }
        }
        printf("%d %d\n", idealNumber, idealNumber == left);
    }
    return 0;
}