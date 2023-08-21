#include "main.h"

/************************* PRINT CHAR *************************/

int print_char(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	char c = va_arg(types, int);
	return (handle_write_char(c, buffer, flags, width, precision, size));
}

/************************* PRINT A STRING *************************/

int print_string(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	char *str = va_arg(types, char *);
	int length = (str != NULL) ? strlen(str) : 6; // Default length for "(null)"

	UNUSED(flags);
	UNUSED(precision);
	UNUSED(size);

	if (precision >= 0 && precision < length)
		length = precision;

	if (width > length && !(flags & FLAG_MINUS))
		handle_write_padding(buffer, width - length);

	write(1, (str != NULL) ? str : "(null)", length);

	if (width > length && (flags & FLAG_MINUS))
		handle_write_padding(buffer, width - length);

	return (width > length ? width : length);
}

/************************* PRINT PERCENT SIGN *************************/

int print_percent(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(precision);
	UNUSED(size);

	if (width > 1 && !(flags & FLAG_MINUS))
		handle_write_padding(buffer, width - 1);

	write(1, "%", 1);

	if (width > 1 && (flags & FLAG_MINUS))
		handle_write_padding(buffer, width - 1);

	return (width > 1 ? width : 1);
}

/************************* PRINT INT *************************/

int print_int(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	long int n = convert_size_number(va_arg(types, long int), size);
	int is_negative = (n < 0);
	unsigned long int num = (is_negative) ? -n : n;

	int printed_chars = write_signed_number(num, is_negative, buffer,
						flags, width, precision, '0', ' ');

	return (printed_chars);
}

/************************* PRINT BINARY *************************/

int print_binary(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	unsigned int n = va_arg(types, unsigned int);
	int length = get_unsigned_number_length(n, 2);

	UNUSED(flags);
	UNUSED(precision);
	UNUSED(size);

	if (precision >= 0)
		length = (length > precision) ? length : precision;

	if (width > length && !(flags & FLAG_MINUS))
		handle_write_padding(buffer, width - length);

	write_unsigned_number(n, 2, buffer, length);

	if (width > length && (flags & FLAG_MINUS))
		handle_write_padding(buffer, width - length);

	return (width > length ? width : length);
}
