#include "main.h"

/**
* get_calculated_precision - Calculate precision for printing
* @format_str: The formatted string to process
* @curr_pos: The current position in the format string
* @arg_list: The list of arguments
*
* Return: Calculated precision
*/
int get_calculated_precision(const char *format_str,
		int *curr_pos, va_list arg_list)
{
int currentIndex = *curr_pos + 1;
int precisionValue = -1;
if (format_str[currentIndex] != '.')
return (precisionValue);
precisionValue = 0;
for (currentIndex += 1; format_str[currentIndex] != '\0'; currentIndex++)
{
if (is_digit(format_str[currentIndex]))
{
precisionValue *= 10;
precisionValue += format_str[currentIndex] - '0';
}
else if (format_str[currentIndex] == '*')
{
currentIndex++;
precisionValue = va_arg(arg_list, int);
break;
}
else
break;
}
*curr_pos = currentIndex - 1;
return (precisionValue);
}
