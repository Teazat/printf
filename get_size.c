#include "main.h"

/**
* calculate_casting_size - Calculate the casting size for argument
* @format_str: The formatted string to process
* @current_idx: The current position in the format string
*
* Return: Calculated casting size
*/
int calculate_casting_size(const char *format_str, int *current_idx)
{
int currentIdx = *current_idx + 1;
int castingSize = 0;
if (format_str[currentIdx] == 'l')
castingSize = S_LONG;
else if (format_str[currentIdx] == 'h')
castingSize = S_SHORT;
if (castingSize == 0)
*current_idx = currentIdx - 1;
else
*current_idx = currentIdx;
return (castingSize);
}
