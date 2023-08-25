#include "custom_printing.h"
/************************* CUSTOM PRINT CHAR *************************/
/**
* custom_print_char - Custom print char function
* @custom_args: List of arguments
* @custom_buffer: Buffer array to handle print
* @custom_flags: Calculate active flags
* @custom_width: Width
* @custom_precision: Precision specification
* @custom_size: Size specifier
* Return: Number of characters printed
*/
int custom_print_char(va_list custom_args, char custom_buffer[],
int custom_flags, int custom_width, int custom_precision, int custom_size)
{
char c = va_arg(custom_args, int);
return (custom_handle_write_char(c, custom_buffer, custom_flags,
			custom_width, custom_precision, custom_size));
}
/************************* CUSTOM PRINT STRING *************************/
/**
* custom_print_string - Custom print string function
* @custom_args: List of arguments
* @custom_buffer: Buffer array to handle print
* @custom_flags: Calculate active flags
* @custom_width: Get width.
* @custom_precision: Precision specification
* @custom_size: Size specifier
* Return: Number of characters printed
*/
int custom_print_string(va_list custom_args, char custom_buffer[],
int custom_flags, int custom_width, int custom_precision, int custom_size)
{
int custom_length = 0, i;
char *custom_str = va_arg(custom_args, char *);
UNUSED(custom_buffer);
UNUSED(custom_flags);
UNUSED(custom_width);
UNUSED(custom_precision);
UNUSED(custom_size);
if (custom_str == NULL)
{
custom_str = "(null)";
if (custom_precision >= 6)
custom_str = "      ";
}
while (custom_str[custom_length] != '\0')
custom_length++;
if (custom_precision >= 0 && custom_precision < custom_length)
custom_length = custom_precision;
if (custom_width > custom_length)
{
if (custom_flags & F_MINUS)
{
write(1, &custom_str[0], custom_length);
for (i = custom_width - custom_length; i > 0; i--)
write(1, " ", 1);
return (custom_width);
}
else
{
for (i = custom_width - custom_length; i > 0; i--)
write(1, " ", 1);
write(1, &custom_str[0], custom_length);
return (custom_width);
}
}
return (write(1, custom_str, custom_length));
}
/************************* CUSTOM PRINT PERCENT SIGN *************************/
/**
* custom_print_percent - Custom print percent sign function
* @custom_args: List of arguments
* @custom_buffer: Buffer array to handle print
* @custom_flags: Calculate active flags
* @custom_width: Get width.
* @custom_precision: Precision specification
* @custom_size: Size specifier
* Return: Number of characters printed
*/
int custom_print_percent(va_list custom_args, char custom_buffer[],
int custom_flags, int custom_width, int custom_precision, int custom_size)
{
UNUSED(custom_args);
UNUSED(custom_buffer);
UNUSED(custom_flags);
UNUSED(custom_width);
UNUSED(custom_precision);
UNUSED(custom_size);
return (write(1, "%%", 1));
}
/************************* CUSTOM PRINT INT *************************/
/**
* custom_print_int - Custom print int function
* @custom_args: List of arguments
* @custom_buffer: Buffer array to handle print
* @custom_flags: Calculate active flags
* @custom_width: Get width.
* @custom_precision: Precision specification
* @custom_size: Size specifier
* Return: Number of characters printed
*/
int custom_print_int(va_list custom_args, char custom_buffer[],
int custom_flags, int custom_width, int custom_precision, int custom_size)
{
int i = CUSTOM_BUFF_SIZE - 2;
int custom_negative = 0;
long int custom_n = va_arg(custom_args, long int);
unsigned long int custom_num;
custom_n = custom_convert_size_number(custom_n, custom_size);
if (custom_n == 0)
custom_buffer[i--] = '0';
custom_buffer[CUSTOM_BUFF_SIZE - 1] = '\0';
custom_num = (unsigned long int)custom_n;
if (custom_n < 0)
{
custom_num = (unsigned long int)((-1) * custom_n);
custom_negative = 1;
}
while (custom_num > 0)
{
custom_buffer[i--] = (custom_num % 10) + '0';
custom_num /= 10;
}
i++;
return (custom_write_number(custom_negative, i, custom_buffer,
			custom_flags, custom_width, custom_precision, custom_size));
}
/************************* CUSTOM PRINT BINARY *************************/
/**
* custom_print_binary - Custom print binary function
* @custom_args: List of arguments
* @custom_buffer: Buffer array to handle print
* @custom_flags: Calculate active flags
* @custom_width: Get width.
* @custom_precision: Precision specification
* @custom_size: Size specifier
* Return: Number of characters printed
*/
int custom_print_binary(va_list custom_args, char custom_buffer[],
int custom_flags, int custom_width, int custom_precision, int custom_size)
{
unsigned int custom_n, custom_m, i, custom_sum;
unsigned int custom_a[32];
int custom_count;
UNUSED(custom_buffer);
UNUSED(custom_flags);
UNUSED(custom_width);
UNUSED(custom_precision);
UNUSED(custom_size);
custom_n = va_arg(custom_args, unsigned int);
custom_m = 2147483648; /* (2 ^ 31) */
custom_a[0] = custom_n / custom_m;
for (i = 1; i < 32; i++)
{
custom_m /= 2;
custom_a[i] = (custom_n / custom_m) % 2;
}
for (i = 0, custom_sum = 0, custom_count = 0; i < 32; i++)
{
custom_sum += custom_a[i];
if (custom_sum || i == 31)
{
char z = '0' + custom_a[i];
write(1, &z, 1);
custom_count++;
}
}
return (custom_count);
}
