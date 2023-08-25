#ifndef CUSTOM_PRINTF_H
#define CUSTOM_PRINTF_H

#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

#define UNUSED(x) (void)(x)
#define BUFFER_SIZE 1024

/* Flags*/
#define FLAG_MINUS   1
#define FLAG_PLUS    2
#define FLAG_ZERO    4
#define FLAG_HASH    8
#define FLAG_SPACE  16

/* Sizes*/
#define SIZE_LONG    2
#define SIZE_SHORT   1

/* Structure to hold format information*/
struct FormatSpecifier {
    char fmt;
    int (*fn)(va_list, char[], int, int, int, int);
};

typedef struct FormatSpecifier FormatSpecifier;

/* Function prototypes */
int custom_printf(const char *format, ...);
int handle_specific_format(const char *fmt, int *current_index, va_list arg_list,
                           char buffer[], int flags, int width, int precision, int size);

/* Other function prototypes... */

/* Constants... */

/* Macro for checking if a character is printable */
int is_printable(char);

/* Function to append hexadecimal code to buffer */
int append_hexa_code(char, char[], int);

/* Function to check if a character is a digit */
int is_digit(char);

/* Functions to handle number size conversion */
long int convert_size_number(long int num, int size);
long int convert_size_unsgnd(unsigned long int num, int size);

#endif /* CUSTOM_PRINTF_H */
