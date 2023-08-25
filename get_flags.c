#include "main.h"
/**
* get_calculated_flags - Calculate active flags
* @format_str: The formatted string to process
* @curr_pos: The current position in the format string
* Return: Calculated flags
*/
int get_calculated_flags(const char *format_str, int *curr_pos)
{
int flagIndex, currentIndex;
int calculatedFlags = 0;
const char FLAG_CHARS[] = {'-', '+', '0', '#', ' ', '\0'};
const int FLAG_VALUES[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};
for (currentIndex = *curr_pos + 1;
		format_str[currentIndex] != '\0'; currentIndex++)
{
for (flagIndex = 0; FLAG_CHARS[flagIndex] != '\0'; flagIndex++)
{
if (format_str[currentIndex] == FLAG_CHARS[flagIndex])
{
calculatedFlags |= FLAG_VALUES[flagIndex];
break;
}
}
if (FLAG_CHARS[flagIndex] == 0)
break;
}
*curr_pos = currentIndex - 1;
return (calculatedFlags);
}
