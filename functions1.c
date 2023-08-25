#include "custom_formatting.h"

/******************** CUSTOM PRINT UNSIGNED NUMBER ***************/
/**
 * custom_print_unsigned - Custom print an unsigned number
 * @custom_args: List of arguments
 * @custom_buffer: Buffer array to handle print
 * @custom_flags: Calculate active flags
 * @custom_width: Get width
 * @custom_precision: Precision specification
 * @custom_size: Size specifier
 * Return: Number of characters printed
 */
int custom_print_unsigned(va_list custom_args, char custom_buffer[],
	int custom_flags, int custom_width, int custom_precision, int custom_size)
{
	int custom_index = CUSTOM_BUFF_SIZE - 2;
	unsigned long int custom_num = va_arg(custom_args, unsigned long int);

	custom_num = custom_convert_size_unsgnd(custom_num, custom_size);

	if (custom_num == 0)
		custom_buffer[custom_index--] = '0';

	custom_buffer[CUSTOM_BUFF_SIZE - 1] = '\0';

	while (custom_num > 0)
	{
		custom_buffer[custom_index--] = (custom_num % 10) + '0';
		custom_num /= 10;
	}

	custom_index++;

	return (custom_write_unsgnd(0, custom_index, custom_buffer,
				custom_flags, custom_width, custom_precision, custom_size));
}

/************* CUSTOM PRINT UNSIGNED NUMBER IN OCTAL ****************/
/**
 * custom_print_octal - Custom print an unsigned number in octal notation
 * @custom_args: List of arguments
 * @custom_buffer: Buffer array to handle print
 * @custom_flags: Calculate active flags
 * @custom_width: Get width
 * @custom_precision: Precision specification
 * @custom_size: Size specifier
 * Return: Number of characters printed
 */
int custom_print_octal(va_list custom_args, char custom_buffer[],
	int custom_flags, int custom_width, int custom_precision, int custom_size)
{
	int custom_index = CUSTOM_BUFF_SIZE - 2;
	unsigned long int custom_num = va_arg(custom_args, unsigned long int);
	unsigned long int custom_init_num = custom_num;

	UNUSED(custom_width);

	custom_num = custom_convert_size_unsgnd(custom_num, custom_size);

	if (custom_num == 0)
		custom_buffer[custom_index--] = '0';

	custom_buffer[CUSTOM_BUFF_SIZE - 1] = '\0';

	while (custom_num > 0)
	{
		custom_buffer[custom_index--] = (custom_num % 8) + '0';
		custom_num /= 8;
	}

	if (custom_flags & F_HASH && custom_init_num != 0)
	custom_buffer[custom_index--] = '0';

	custom_index++;

	return (custom_write_unsgnd(0, custom_index, custom_buffer,
				custom_flags, custom_width, custom_precision, custom_size));
}

/************** CUSTOM PRINT UNSIGNED NUMBER IN HEXADECIMAL **************/
/**
 * custom_print_hexadecimal - Custom print unsigned number in hexadecimal
 * @custom_args: List of arguments
 * @custom_buffer: Buffer array to handle print
 * @custom_flags: Calculate active flags
 * @custom_width: Get width
 * @custom_precision: Precision specification
 * @custom_size: Size specifier
 * Return: Number of characters printed
 */
int custom_print_hexadecimal(va_list custom_args, char custom_buffer[],
	int custom_flags, int custom_width, int custom_precision, int custom_size)
{
	return (custom_print_hexa(custom_args, "0123456789abcdef", custom_buffer,
		custom_flags, 'x', custom_width, custom_precision, custom_size));
}

/********** CUSTOM PRINT UNSIGNED NUMBER IN UPPER HEXADECIMAL ***********/
/**
 * custom_print_hexa_upper - Custom print unsigned number in upper hexadecimal
 * @custom_args: List of arguments
 * @custom_buffer: Buffer array to handle print
 * @custom_flags: Calculate active flags
 * @custom_width: Get width
 * @custom_precision: Precision specification
 * @custom_size: Size specifier
 * Return: Number of characters printed
 */
int custom_print_hexa_upper(va_list custom_args, char custom_buffer[],
	int custom_flags, int custom_width, int custom_precision, int custom_size)
{
	return (custom_print_hexa(custom_args, "0123456789ABCDEF", custom_buffer,
		custom_flags, 'X', custom_width, custom_precision, custom_size));
}

/************** CUSTOM PRINT HEX NUM IN LOWER OR UPPER **************/
/**
 * custom_print_hexa - Custom print a hexadecimal number in lower or upper
 * @custom_args: List of arguments
 * @custom_map_to: Array of values to map the number to
 * @custom_buffer: Buffer array to handle print
 * @custom_flags: Calculate active flags
 * @custom_flag_ch: Calculate active flags
 * @custom_width: Get width
 * @custom_precision: Precision specification
 * @custom_size: Size specifier
 * @custom_size: Size specification
 * Return: Number of characters printed
 */
int custom_print_hexa(va_list custom_args, char custom_map_to[],
	char custom_buffer[], int custom_flags, char custom_flag_ch,
	int custom_width, int custom_precision, int custom_size)
{
	int custom_index = CUSTOM_BUFF_SIZE - 2;
	unsigned long int custom_num = va_arg(custom_args, unsigned long int);
	unsigned long int custom_init_num = custom_num;

	UNUSED(custom_width);

	custom_num = custom_convert_size_unsgnd(custom_num, custom_size);

	if (custom_num == 0)
		custom_buffer[custom_index--] = '0';

	custom_buffer[CUSTOM_BUFF_SIZE - 1] = '\0';

	while (custom_num > 0)
	{
		custom_buffer[custom_index--] = custom_map_to[custom_num % 16];
		custom_num /= 16;
	}

	if (custom_flags & F_HASH && custom_init_num != 0)
	{
		custom_buffer[custom_index--] = custom_flag_ch;
		custom_buffer[custom_index--] = '0';
	}

	custom_index++;

	return (custom_write_unsgnd(0, custom_index, custom_buffer,
				custom_flags, custom_width, custom_precision, custom_size));
}
