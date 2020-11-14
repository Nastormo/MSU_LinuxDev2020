#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libintl.h>
#include <locale.h>
#define _(STRING) gettext(STRING)
#define LOCALE_PATH "."

int main(int argc, char **argv)
{
    setlocale(LC_ALL,"");
    bindtextdomain("bin_search", LOCALE_PATH);
    textdomain("bin_search");

    int idealNumber;
    int left = 1;
    int right = 100;
    int middle;
    int result;
    char answer[80];
    printf(_("Choose number from 1 to 100: "));
    scanf("%d", &idealNumber);
    while(left != right) {
        middle = (left + right) / 2;
        printf(_("Your number greater than %d?: "), middle);
        scanf("%s", answer);
        if (strstr(answer, _("Yes")) || 
            strstr(answer, _("Y")) || 
            strstr(answer, _("yes")) || 
            strstr(answer, _("y"))) {
            left = middle + 1;
        } else if (strstr(answer, _("No")) ||
            strstr(answer, _("N")) ||
            strstr(answer, _("no")) ||
            strstr(answer, _("n"))) {
            right = middle;
        }
    }
    printf(_("Selected value: %d"), left);
    return 0;
}