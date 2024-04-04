#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <stdbool.h>

#define MAX_HISTORY_LINES 5
#define MAX_INPUT_LENGTH 1000
#define MAX_ARR_SIZE 3

// -- READ INPUT --

char inputStr[MAX_INPUT_LENGTH];
int histCountLine = 0;
char* hist = '\0';
int result = 0; // for storing output after perform execution
int a = 0, b = 0, ans = 0;
char op = ' ';
bool isMathError = false;
bool isSyntaxError = false;

void deleteFirstChars(char *str, size_t n)
{
    assert(n != 0 && str != 0);
    size_t len = strlen(str);
    if (n > len)
        return; // Or: n = len;
    memmove(str, str + n, len - n + 1);
}

char *DeleteMethod0(char *string)
{
    for (char *p = string;; ++p)
        if (*p != '\n')
            return p;
}

// append two string together
char *getConcatString(const char *str1, const char *str2)
{
    char *finalString = NULL;
    size_t n = 0;

    if (str1)
        n += strlen(str1);
    if (str2)
        n += strlen(str2);

    if ((str1 || str2) && (finalString = malloc(n + 1)) != NULL)
    {
        *finalString = '\0';

        if (str1)
            strcpy(finalString, str1);
        if (str2)
            strcat(finalString, str2);
    }

    return finalString;
}

// -- CONVERT OPERANDS --
void convertOperands(char *a_str, char* op_str ,char *b_str)
{
    if (a_str == "ANS")
    {
        a = ans;
    }
    else
    {
        a = *a_str - '0';
    }

    if (b_str == "ANS")
    {
        b = ans;
    }
    else
    {
        b = *b_str - '0';
    }

    op = *op_str;

    return;
}

void readInput(char input[])
{
    printf(">> ");
    fgets(input, MAX_INPUT_LENGTH, stdin);
    if (input == "HIST")
    {
        deleteFirstChars(hist, 2);
        puts(hist);
        getchar();
    }
    else
    {
        hist = getConcatString(hist, inputStr);
        histCountLine++;

        // split string here
        const char delimiter[] = " ,?"; // Delimiters: space, comma, and question mark
        char *token;
        char *array[20]; // Assuming a maximum of 20 substrings

        // Splitting the string and storing substrings into the array
        int count = 0;
        token = strtok(inputStr, delimiter);
        while (token != NULL && count < 20)
        {
            array[count++] = token;
            token = strtok(NULL, delimiter);
        }

        convertOperands(array[0], array[1] ,array[2]);
    }
}

int division(int a, int b)
{
    if (b == 0)
    {
        isMathError = true;
        return 0;
    }
    return a / b;
}

int calculate()
{
    switch (op)
    {
    case '+':
        result = a + b;
        break;
    case '-':
        result = a - b;
        break;
    case '*':
        result = a * b;
        break;
    case '/':
        result = a / b;
        break;
    case '%':
        result = a % b;
        break;
    default:
        break;
    }
    return result;

    if (isMathError == false && isSyntaxError == false)
    {
        return result;
    }
    else
    {
        ans = result;
        return 0;
    }
}

void showOutput()
{
    if (isMathError == true)
    {
        printf("MATH ERROR\n");
    }
    else if (isSyntaxError == true)
    {
        printf("SYNTAX ERROR\n");
    }
    else
    {
        printf("%.2f\n", result); 
    }
}

int main()
{
    readInput(inputStr);

    while (inputStr != "EXIT")
    {
        if (inputStr != "HIST")
        {
            calculate();
            showOutput();
        }
        readInput(inputStr);
    }
    return 0;
}