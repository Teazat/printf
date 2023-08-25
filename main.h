#ifndef UNIQUE_MAIN_H
#define UNIQUE_MAIN_H
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#define UNUSED_ARG(x) (void)(x)
#define BUFFER_SIZE 1024
/* FLAG CONSTANTS */
#define FLAG_MINUS 1
#define FLAG_PLUS 2
#define FLAG_ZERO 4
#define FLAG_HASH 8
#define FLAG_SPACE 16
/* SIZE CONSTANTS */
#define SIZE_LONG 2
#define SIZE_SHORT 1
/**
* CustomFmt - Structure to hold format and associated function
* struct CustomFmt
* @formatSpecifier: The format specifier.
* @associatedFunction: The corresponding function.
*/
struct CustomFmt
{
char formatSpecifier;
int (*associatedFunction)(va_list, char[], int, int, int, int);
};
typedef struct CustomFmt CustomFmt_t;
int customPrintf(const char *format, ...);
int printHandler(const char *fmt, int *index,
va_list list, char buffer[], int flags, int width, int precision, int size);

/****************** FUNCTION DECLARATIONS ******************/
/* Functions for printing characters and strings */
int printCharacter(va_list types, char buffer[],
int flags, int width, int precision, int size);
int printString(va_list types, char buffer[],
int flags, int width, int precision, int size);
int printPercent(va_list types, char buffer[],
int flags, int width, int precision, int size);
/* Functions for printing numbers */
int printInteger(va_list types, char buffer[],
int flags, int width, int precision, int size);
int printBinary(va_list types, char buffer[],
int flags, int width, int precision, int size);
int printUnsigned(va_list types, char buffer[],
int flags, int width, int precision, int size);
int printOctal(va_list types, char buffer[],
int flags, int width, int precision, int size);
int printHexadecimal(va_list types, char buffer[],
int flags, int width, int precision, int size);
int printHexaUpper(va_list types, char buffer[],
int flags, int width, int precision, int size);
int printHexa(va_list types, char mapTo[],
char buffer[], int flags, char flagChar, int width, int precision, int size);
/* Function for printing non-printable characters */
int printNonPrintable(va_list types, char buffer[],
int flags, int width, int precision, int size);
/* Function for printing memory addresses */
int printPointer(va_list types, char buffer[],
int flags, int width, int precision, int size);
/* Functions to handle other specifiers */
int getFlags(const char *format, int *index);
int getWidth(const char *format, int *index, va_list list);
int getPrecision(const char *format, int *index, va_list list);
int getSize(const char *format, int *index);
/* Function for printing reversed strings */
int handleWriteChar(char character, char buffer[],
int flags, int width, int precision, int size);
int writeNumber(int isPositive, int index, char buffer[],
int flags, int width, int precision, int size);
int writeNum(int index, char buffer[], int flags, int width, int precision,
int length, char padding, char extraChar);
int writePointer(char buffer[], int index, int length,
int width, int flags, char padding, char extraChar, int paddingStart);
int writeUnsigned(int isNegative, int index,
char buffer[],
int flags, int width, int precision, int size);
/****************** UTILITY FUNCTIONS ******************/
int isPrintableCharacter(char);
int appendHexaCode(char, char[], int);
int isDigitCharacter(char);
long int convertSizeNumber(long int num, int size);
long int convertSizeUnsigned(unsigned long int num, int size);
#endif /* UNIQUE_MAIN_H */
