#include "main.h"
/************************* CHARACTER PRINTING *************************/
/**
* handle_write_char - Output a character
* @c: Character argument.
* @buffer: Buffer for handling output.
* @flags:  Flag analysis.
* @width: Width specification.
* @precision: Precision value.
* @size: Size specification.
*
* Return: Count of characters printed.
*/
int handle_write_char(char c, char buffer[],
int flags, int width, int precision, int size)
{
int i = 0;
char padding_ch = ' ';
UNUSED(precision);
UNUSED(size);
if (flags & F_ZERO)
padding_ch = '0';
buffer[i++] = c;
buffer[i] = '\0';
if (width > 1)
{
buffer[BUFF_SIZE - 1] = '\0';
for (i = 0; i < width - 1; i++)
buffer[BUFF_SIZE - i - 2] = padding_ch;
if (flags & F_MINUS)
return (write(1, &buffer[0], 1) + write(1, &buffer[BUFF_SIZE - i - 1], width - 1));
else
return (write(1, &buffer[BUFF_SIZE - i - 1], width - 1) + write(1, &buffer[0], 1));
}
return (write(1, &buffer[0], 1));
}
/************************* NUMBER PRINTING *************************/
/**
* write_number - Print a number
* @is_negative: Negative flag.
* @ind: Index argument.
* @buffer: Buffer for printing.
* @flags: Flag interpretation.
* @width: Width specification.
* @precision: Precision specification.
* @size: Size specification.
*
* Return: Count of printed characters.
*/
int write_number(int is_negative, int ind, char buffer[],
int flags, int width, int precision, int size)
{
int length = BUFF_SIZE - ind - 1;
char padding_ch = ' ', extra_ch = 0;
UNUSED(size);
if ((flags & F_ZERO) && !(flags & F_MINUS))
padding_ch = '0';
if (is_negative)
extra_ch = '-';
else if (flags & F_PLUS)
extra_ch = '+';
else if (flags & F_SPACE)
extra_ch = ' ';
return (write_num(ind, buffer, flags, width, precision,
length, padding_ch, extra_ch));
}
/**
* write_num - Utilize a buffer to write a number
* @ind: Index for starting number in buffer.
* @buffer: Buffer for writing.
* @flags: Flag details.
* @width: Width value.
* @prec: Precision specification.
* @length: Number length.
* @padding_ch: Padding character.
* @extra_ch: Extra character.
*
* Return: Count of printed characters.
*/
int write_num(int ind, char buffer[],
int flags, int width, int prec,
int length, char padding_ch, char extra_ch)
{
int i, padd_start = 1;
if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
return (0); /* Case: ".0d" prints nothing */
if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
buffer[ind] = padding_ch = ' '; /* Display width with padding ' ' */
if (prec > 0 && prec < length)
padding_ch = ' ';
while (prec > length)
buffer[--ind] = '0', length++;
if (extra_ch != 0)
length++;
if (width > length)
{
for (i = 1; i < width - length + 1; i++)
buffer[i] = padding_ch;
buffer[i] = '\0';
if (flags & F_MINUS && padding_ch == ' ')/* Extra char on left of buffer */
{
if (extra_ch)
buffer[--ind] = extra_ch;
return (write(1, &buffer[ind], length) + write(1, &buffer[1], i - 1));
}
else if (!(flags & F_MINUS) && padding_ch == ' ')/* Extra char on left of buffer */
{
if (extra_ch)
buffer[--ind] = extra_ch;
return (write(1, &buffer[1], i - 1) + write(1, &buffer[ind], length));
}
else if (!(flags & F_MINUS) && padding_ch == '0')/* Extra char on left of padding */
{
if (extra_ch)
buffer[--padd_start] = extra_ch;
return (write(1, &buffer[padd_start], i - padd_start) +
write(1, &buffer[ind], length - (1 - padd_start)));
}
}
if (extra_ch)
buffer[--ind] = extra_ch;
return (write(1, &buffer[ind], length));
}
/**
* write_unsgnd - Print an unsigned number
* @is_negative: Negative indicator.
* @ind: Index argument.
* @buffer: Buffer for printing.
* @flags: Flag details.
* @width: Width specification.
* @precision: Precision specification.
* @size: Size specification.
*
* Return: Count of printed characters.
*/
int write_unsgnd(int is_negative, int ind,
char buffer[],
int flags, int width, int precision, int size)
{
/* The number is on the buffer's right, starting at index i */
int length = BUFF_SIZE - ind - 1, i = 0;
char padding_ch = ' ';
UNUSED(is_negative);
UNUSED(size);
if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
return (0); /* Case: ".0d" prints nothing */
if (precision > 0 && precision < length)
padding_ch = ' ';
while (precision > length)
{
buffer[--ind] = '0';
length++;
}
if ((flags & F_ZERO) && !(flags & F_MINUS))
padding_ch = '0';
if (width > length)
{
for (i = 0; i < width - length; i++)
buffer[i] = padding_ch;
buffer[i] = '\0';
if (flags & F_MINUS) /* Extra char on left of buffer [buffer > padding] */
{
return (write(1, &buffer[ind], length));
}
