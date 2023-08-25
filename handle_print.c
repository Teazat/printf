#include "main.h"

/**
* handle_specific_format - Handles printing based on the format specifier
* @format: The format string
* @current_index: The current index in the format string
* @arg_list: The list of arguments
* @buffer: Buffer array to handle print
* @flags: Calculates active flags
* @width: get width
* @precision: Precision specification
* @size: Size specifier
* Return: Number of characters printed
*/
int handle_specific_format(const char *format,
int *current_index, va_list arg_list,
char buffer[], int flags, int width, int precision, int size)
{
int i, unknown_length = 0, printed_chars = -1;
fmt_t fmt_types[] = {
{'c', print_char}, {'s', print_string}, {'%', print_percent},
{'i', print_int}, {'d', print_int}, {'b', print_binary},
{'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},
{'X', print_hexa_upper}, {'p', print_pointer}, {'S', print_non_printable},
{'r', print_reverse}, {'R', print_rot13string}, {'\0', NULL}
};
for (i = 0; fmt_types[i].fmt != '\0'; i++)
{
if (format[*current_index] == fmt_types[i].fmt)
{
return (fmt_types[i].fn(arg_list, buffer, flags, width, precision, size));
}
}
if (fmt_types[i].fmt == '\0')
{
if (format[*current_index] == '\0')
{
return (-1);
}
unknown_length += write(1, "%%", 1);
if (format[*current_index - 1] == ' ')
{
unknown_length += write(1, " ", 1);
}
else if (width)
{
--(*current_index);
while (format[*current_index] != ' ' && format[*current_index] != '%')
{
--(*current_index);
}
if (format[*current_index] == ' ')
{
--(*current_index);
}
return (1);
}
unknown_length += write(1, &format[*current_index], 1);
return (unknown_length);
}
return (printed_chars);
}
