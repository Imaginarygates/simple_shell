#include "shell.h"

/**
* _custom_strcmp - Compare two strings.
* @str1: The first string to compare.
* @str2: The second string to compare.
*
* Return: A negative value if str1 is less than str2,
* A positive value if str1 is greater than str2,
* 0 if str1 is equal to str2.
*/
int _custom_strcmp(const char *str1, const char *str2)
{
while (*str1 && (*str1 == *str2))
{
str1++;
str2++;
}
return ((unsigned char)(*str1) - (unsigned char)(*str2));
}

/**
* _custom_strlen - Calculate the length of a string.
* @str: The input string.
*
* Return: The length of the string (excluding the null terminator).
*/
size_t _custom_strlen(const char *str)
{
size_t length = 0;

while (str[length] != '\0')
{
length++;
}
return length;
}

/**
* _custom_strdup - Duplicate a string.
* @src: The source string to duplicate.
*
* Return: A pointer to the newly allocated duplicated string,
* or NULL if there is insufficient memory.
*/
char *_custom_strdup(const char *src)
{
char *dest;
size_t length = 0;
size_t i;

while (src[length])
length++;

dest = malloc((length + 1) * sizeof(char));

if (dest == NULL)
return NULL;

for (i = 0; i <= length; i++)
dest[i] = src[i];

return dest;
}

/**
* _custom_strcpy - Copy a string to a buffer.
* @dest: The destination buffer.
* @src: The source string to copy.
*
* Return: A pointer to the destination buffer.
*/
char *_custom_strcpy(char *dest, const char *src)
{
char *destStart = dest;

while (*src)
{
*dest = *src;
dest++;
src++;
}
*dest = '\0';

return destStart;
}

/**
* _custom_strcat - Concatenate two strings.
* @dest: The destination buffer where the resulting string will be stored.
* @src: The source string to be appended to the destination.
*
* Return: A pointer to the destination buffer.
*/
char *_custom_strcat(char *dest, const char *src)
{
char *temp = dest;

while (*dest)
dest++;

while (*src)
{
*dest = *src;
dest++;
src++;
}
*dest = '\0'; /* Null-terminate the concatenated string */

return temp;
}
