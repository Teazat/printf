#include "main.h"

/**
* calculate_printing_width - Calculate the printing width for formatting
* @format_str: The formatted string to process
* @current_idx: The current position in the format string
* @arg_list: The list of arguments
*
* Return: Calculated printing width
*/
int calculate_printing_width(const char *format_str,
		int *current_idx, va_list arg_list)
{
int currentIndex = *current_idx + 1;
int printingWidth = 0;
for (; format_str[currentIndex] != '\0'; currentIndex++)
{
if (is_digit(format_str[currentIndex]))
{
printingWidth *= 10;
printingWidth += format_str[currentIndex] - '0';
}
else if (format_str[currentIndex] == '*')
{
currentIndex++;
printingWidth = va_arg(arg_list, int);
break;
}
else
break;
}
*current_idx = currentIndex - 1;
return (printingWidth);
}
