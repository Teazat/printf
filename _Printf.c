#include "custom_printer.h"

void custom_flush_buffer(char custom_buf[], int *custom_buf_index);

/**
 * custom_printf - Custom Printf function
 * @custom_format: Custom format.
 * Return: Number of printed characters.
 */
int custom_printf(const char *custom_format, ...)
{
	int i, printed = 0, total_printed_chars = 0;
	int custom_flags, custom_width, custom_precision,
	    custom_size, custom_buf_index = 0;
	va_list custom_list;
	char custom_buffer[CUSTOM_BUFF_SIZE];

	if (custom_format == NULL)
	return (-1);

	va_start(custom_list, custom_format);

	for (i = 0; custom_format && custom_format[i] != '\0'; i++)
	{
		if (custom_format[i] != '%')
		{
			custom_buffer[custom_buf_index++] = custom_format[i];
			if (custom_buf_index == CUSTOM_BUFF_SIZE)
			custom_flush_buffer(custom_buffer, &custom_buf_index);
			total_printed_chars++;
		}
		else
		{
			custom_flush_buffer(custom_buffer, &custom_buf_index);
			custom_flags = custom_get_flags(custom_format, &i);
			custom_width = custom_get_width(custom_format, &i, custom_list);
			custom_precision = custom_get_precision(custom_format, &i, custom_list);
			custom_size = custom_get_size(custom_format, &i);
			++i;
			printed = custom_handle_print(custom_format, &i, custom_list, custom_buffer,
					custom_flags, custom_width, custom_precision, custom_size);
			if (printed == -1)
				return (-1);
			total_printed_chars += printed;
		}
	}

	custom_flush_buffer(custom_buffer, &custom_buf_index);

	va_end(custom_list);

	return (total_printed_chars);
}

/**
 * custom_flush_buffer - Prints the contents of the buffer if it exists
 * @custom_buf: Array of characters
 * @custom_buf_index: Index to add the next character, represents length.
 */
void custom_flush_buffer(char custom_buf[], int *custom_buf_index)
{
	if (*custom_buf_index > 0)
	write(1, &custom_buf[0], *custom_buf_index);

	*custom_buf_index = 0;
}
