#include "main.h"
/**
* is_printable - Assesses in case a char is printable
* @c: Char to be assessed.
*
* Return: 1 in the event that c is printable, something else
*/
int is_printable(char c)
{
	if (c >= 32 && c < 127)
		return (1);

	return (0);
}
/**
* append_hexa_code - Add ascci in hexadecimal code to buffer
* @buffer: Cluster of chars.
* @i: Record at which to begin adding.
* @ascii_code: ASSCI CODE.
* Return: Continuously 3
*/
int append_hexa_code(char ascii_code, char buffer[], int i)
{
	char map_to[] = "0123456789ABCDEF";
	/* The hexa format code is always 2 digits long */
	if (ascii_code < 0)
		ascii_code *= -1;

	buffer[i++] = '\\';
	buffer[i++] = 'x';

	buffer[i++] = map_to[ascii_code / 16];
	buffer[i] = map_to[ascii_code % 16];

	return (3);
}
/**
* is_digit - Confirms on the off chance that a char could be a digit
* @c: Char to be assessed
*
* Return: 1 in the event that c may be a digit, something else
*/
int is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);

	return (0);
}
/**
* convert_size_number - Casts a number to the desired estimate
* @num: Number to be casted.
* @size: Number demonstrating the sort to be casted.
*
* Return: Casted esteem of num
*/
long int convert_size_number(long int num, int size)
{
	if (size == S_LONG)
		return (num);
	else if (size == S_SHORT)
		return ((short)num);

	return ((int)num);
}
/**
* convert_size_unsgnd - Casts a number to the required measure
* @num: Number to be casted
* @size: Number demonstrating the sort to be casted
*
* Return: Casted esteem of num
*/
long int convert_size_unsgnd(unsigned long int num, int size)
{
	if (size == S_LONG)
		return (num);
	else if (size == S_SHORT)
		return ((unsigned short)num);

	return ((unsigned int)num);
}

