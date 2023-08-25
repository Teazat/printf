#include "custom_printing_functions.h"

/****************** CUSTOM PRINT POINTER ******************/
/**
 * custom_print_ptr - Custom print the value of a pointer variable
 * @custom_args: List of arguments
 * @custom_buffer: Buffer array to handle print
 * @custom_flags: Calculate active flags
 * @custom_width: Get width
 * @custom_precision: Precision specification
 * @custom_size: Size specifier
 * Return: Number of characters printed
 */
int custom_print_ptr(va_list custom_args, char custom_buffer[],
	int custom_flags, int custom_width, int custom_precision, int custom_size)
{
	char custom_extra_c = 0, custom_padd = ' ';
	int custom_index = CUSTOM_BUFF_SIZE - 2,
	    custom_length = 2, custom_padd_start = 1;
	unsigned long custom_num_addrs;
	char custom_map_to[] = "0123456789abcdef";
	void *custom_addrs = va_arg(custom_args, void *);

	UNUSED(custom_width);
	UNUSED(custom_size);

	if (custom_addrs == NULL)
		return (write(1, "(nil)", 5));

	custom_buffer[CUSTOM_BUFF_SIZE - 1] = '\0';
	UNUSED(custom_precision);

	custom_num_addrs = (unsigned long)custom_addrs;

	while (custom_num_addrs > 0)
	{
		custom_buffer[custom_index--] = custom_map_to[custom_num_addrs % 16];
		custom_num_addrs /= 16;
		custom_length++;
	}

	if ((custom_flags & F_ZERO) && !(custom_flags & F_MINUS))
		custom_padd = '0';
	if (custom_flags & F_PLUS)
		custom_extra_c = '+', custom_length++;
	else if (custom_flags & F_SPACE)
		custom_extra_c = ' ', custom_length++;

	custom_index++;

	return (custom_write_pointer(custom_buffer, custom_index, custom_length,
		custom_width, custom_flags, custom_padd, custom_extra_c,
		custom_padd_start));
}

/************************ CUSTOM PRINT NON PRINTABLE *************************/
/**
 * custom_print_non_printable - Print ASCII in hexadecimal non-printable char
 * @custom_args: List of arguments
 * @custom_buffer: Buffer array to handle print
 * @custom_flags: Calculate active flags
 * @custom_width: Get width
 * @custom_precision: Precision specification
 * @custom_size: Size specifier
 * Return: Number of characters printed
 */
int custom_print_non_printable(va_list custom_args, char custom_buffer[],
	int custom_flags, int custom_width, int custom_precision, int custom_size)
{
	int custom_i = 0, custom_offset = 0;
	char *custom_str = va_arg(custom_args, char *);

	UNUSED(custom_flags);
	UNUSED(custom_width);
	UNUSED(custom_precision);
	UNUSED(custom_size);

	if (custom_str == NULL)
		return (write(1, "(null)", 6));

	while (custom_str[custom_i] != '\0')
	{
		if (custom_is_printable(custom_str[custom_i]))
			custom_buffer[custom_i + custom_offset] = custom_str[custom_i];
		else
			custom_offset += custom_append_hexa_code(custom_str[custom_i],
					custom_buffer, custom_i + custom_offset);

		custom_i++;
	}

	custom_buffer[custom_i + custom_offset] = '\0';

	return (write(1, custom_buffer, custom_i + custom_offset));
}

/********************** CUSTOM PRINT REVERSE ****************/
/**
 * custom_print_reverse - Custom print a reverse string.
 * @custom_args: List of arguments
 * @custom_buffer: Buffer array to handle print
 * @custom_flags: Calculate active flags
 * @custom_width: Get width
 * @custom_precision: Precision specification
 * @custom_size: Size specifier
 * Return: Number of characters printed
 */
int custom_print_reverse(va_list custom_args, char custom_buffer[],
	int custom_flags, int custom_width, int custom_precision, int custom_size)
{
	char *custom_str;
	int custom_i, custom_count = 0;

	UNUSED(custom_buffer);
	UNUSED(custom_flags);
	UNUSED(custom_width);
	UNUSED(custom_size);

	custom_str = va_arg(custom_args, char *);

	if (custom_str == NULL)
	{
		UNUSED(custom_precision);
		custom_str = ")Null(";
	}

	for (custom_i = 0; custom_str[custom_i]; custom_i++)
		;

	for (custom_i = custom_i - 1; custom_i >= 0; custom_i--)
	{
		char custom_ch = custom_str[custom_i];

		write(1, &custom_ch, 1);
		custom_count++;
	}

	return (custom_count);
}

/******************* CUSTOM PRINT A STRING IN ROT13 ****************/
/**
 * custom_print_rot13string - Custom print a string in ROT13.
 * @custom_args: List of arguments
 * @custom_buffer: Buffer array to handle print
 * @custom_flags: Calculate active flags
 * @custom_width: Get width
 * @custom_precision: Precision specification
 * @custom_size: Size specifier
 * Return: Number of characters printed
 */
int custom_print_rot13string(va_list custom_args, char custom_buffer[],
	int custom_flags, int custom_width, int custom_precision, int custom_size)
{
	char custom_ch;
	char *custom_str;
	unsigned int custom_i, custom_j;
	int custom_count = 0;
	char custom_in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char custom_out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	custom_str = va_arg(custom_args, char *);

	UNUSED(custom_buffer);
	UNUSED(custom_flags);
	UNUSED(custom_width);
	UNUSED(custom_precision);
	UNUSED(custom_size);

	if (custom_str == NULL)
		custom_str = "(AHYY)";

	for (custom_i = 0; custom_str[custom_i]; custom_i++)
	{
		for (custom_j = 0; custom_in[custom_j]; custom_j++)
		{
			if (custom_in[custom_j] == custom_str[custom_i])
			{
				custom_ch = custom_out[custom_j];
				write(1, &custom_ch, 1);
				custom_count++;
				break;
			}
		}
		if (!custom_in[custom_j])
		{
			custom_ch = custom_str[custom_i];
			write(1, &custom_ch, 1);
			custom_count++;
		}
	}
	return (custom_count);
}
