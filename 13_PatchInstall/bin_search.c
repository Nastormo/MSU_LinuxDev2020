/*! 
 * \mainpage Главная страница
 * Использование: bin_search [ОПЦИИ]
 * 
 * Мини игра по угадыванию чисел.
 * 
 * Опции:
 * 
 *     -r, --roman    римское представление чисел
 * 
 *     -h, --help    печать информации о приложении
 * 
 * Это мини игра где вам необходимо выбрать число от 1
 * 
 * до 100, а программа угадает его при помощи бин поиска.
 */

/*! 
 *  \file bin_search.c
 *  \brief Главный C файл 
 *  \authors Лев Смирнов
 *  \version 1.0
 *  \date 21.11.2020
 *  Данный файл содержит основную логику программы
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libintl.h>
#include <locale.h>
#define _(STRING) gettext(STRING)
#define LOCALE_PATH "."

#define MAX_ROMAN 3999  ///<Максимальное переводимое число
#define SYMBOL_ROMAN 28 ///<Количество элементов в мапе
#define MAX_STRING 80   ///<Максимальное количество символов в строке

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

///Набор возможных записей чисел
enum NumberType {
    NUMBER_NORMAL = 0, ///<Арабская запись
    NUMBER_ROMAN       ///<Римская запись
};

///Набор возможных типов работы
enum WorkType {
    WORK_NORMAL = 0, ///<Стандартная работа
    WORK_HELP        ///<Печать информационной сводки
};

/*!
 * \brief Структура хранящая в себе состояние программы
 * 
 * Данная структура содержит конфигурацию работы программы
 */
struct Config {
    enum NumberType numberType; ///<Тип представления чисел
    enum WorkType workType;     ///<Тип работы программы
};

/*!
 * Переводит арабскую запись числа в римскую.
 * \param n Число в арабской записи
 * \return Число в римской записи в виде строки
 */
char* intToRoman(int n) 
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

/*!
 * Переводит римскую запись числа в арабскую.
 * \param romanN число в римской в виде строки
 * \return Число в арабской записи в виде челочисленного числа
 */
int romanToInt(char* romanN) {
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

/*!
 * Парсинг входных данных.
 * \param argc Число параметров
 * \param argv Параметры в виде масива строк
 * \param conf Конфигурация работы програмы
 * \return Число в арабской записи в виде челочисленного числа
 */
void checkParam(int argc, char **argv, struct Config* conf) {
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "--roman") == 0 || strcmp(argv[i], "-r") == 0) {
            conf->numberType = NUMBER_ROMAN;
        } else if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
            conf->workType = WORK_HELP;
        }
    }
}

/*!
 * Печать информационной справки.
 */
void printHelp() {
    printf("%s", _(
        "Usage: bin_search [OPTION]\n"
        "Number guessing mini game.\n\n"
        "Options:\n"
        "\t-r, --roman\tenable roman number\n"
        "\t-h, --help\tprint help information\n\n"
        "It is a guessing mini game where you choose a number\n"
        "from 1 to 100 and the program finds it whis bin search.\n"
    ));
}

/*!
 * Главная функция программы.
 * \param argc Число параметров
 * \param argv Параметры в виде масива строк
 * \return Код завершения программы
 */
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
    struct Config* conf = malloc(sizeof(struct Config));
    
    checkParam(argc, argv, conf);
    if(conf->workType == WORK_HELP) {
        printHelp();
        return 0;
    }

    if (conf->numberType == NUMBER_NORMAL) {
        printf(_("Choose number from 1 to 100\n"));
    } else if (conf->numberType == NUMBER_ROMAN) {
        printf(_("Choose number from %s to %s\n"), intToRoman(1), intToRoman(100));
    }
    while(left != right) {
        middle = (left + right) / 2;
        if (conf->numberType == NUMBER_NORMAL) {
            printf(_("Your number greater than %d?: "), middle);
        } else if (conf->numberType == NUMBER_ROMAN) {
            printf(_("Your number greater than %s?: "), intToRoman(middle));
        }
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
    if (conf->numberType == NUMBER_NORMAL) {
        printf(_("Selected value: %d"), left);
    } else if (conf->numberType == NUMBER_ROMAN) {
        printf(_("Selected value: %s"), intToRoman(left));
    }
    return 0;
}