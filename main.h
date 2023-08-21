#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

#define UNUSED(x) (void)(x)
#define BUFF_SIZE 1024

/* Flags */
#define FLAG_MINUS 1
#define FLAG_PLUS  2
#define FLAG_ZERO  4
#define FLAG_HASH  8
#define FLAG_SPACE 16

/* Sizes */
#define SIZE_LONG  2
#define SIZE_SHORT 1

/**
 * struct format - Struct format
 *
 * @format: The format specifier.
 * @fn: The function associated with the specifier.
 */
struct format
{
	char format;
	int (*fn)(va_list, char[], int, int, int, int);
};

typedef struct format format_t;

int _printf(const char *format, ...);
int handle_print(const char *format, int *i,
    va_list list, char buffer[], int flags, int width, int precision, int size);

/* Function prototypes for various print functions */

int print_char(va_list types, char buffer[],
    int flags, int width, int precision, int size);

int print_string(va_list types, char buffer[],
    int flags, int width, int precision, int size);

int print_percent(va_list types, char buffer[],
    int flags, int width, int precision, int size);

/* ... other print function prototypes ... */

/* Utility functions */

int is_printable(char);
int append_hexa_code(char, char[], int);
int is_digit(char);

long int convert_size_number(long int num, int size);
long int convert_size_unsigned(unsigned long int num, int size);

#endif /* MAIN_H */
