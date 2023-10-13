#include "shell.h"

#define BUFFER_SIZE 1024

/**
* _memcpy_custom - Copy memory from source to destination.
* @dest: Pointer to the destination buffer.
* @src: Pointer to the source buffer. 
* @n: Number of bytes to copy from source to destination.
* Return: Pointer to the destination buffer.
*/

void *_memcpy_custom(void *dest, const void *src, size_t n)
{
char *csrc = (char *)src;
char *cdest = (char *)dest;
size_t i;


for (i = 0; i < n; i++)
cdest[i] = csrc[i];
return (dest);
}

/**
* refillBuffer - Refill the buffer with data from the stream.
* @stream: Input stream from which to read the data
* @buf: A buffer to store the read data
* @buf_index: Pointer to the index showing the current position
* @bytes_remaining: Pointer to the number of bytes to be read
*
* Return: Number of bytes read,
* * or -1 on failure (EOF or error)
*/
ssize_t refillBuffer(FILE *stream, char buf[], size_t *buf_index, ssize_t *bytes_remaining)
{
	*bytes_remaining = read(fileno(stream), buf, BUFFER_SIZE);
	*buf_index = 0;
	return (*bytes_remaining);
}


/**
* resizeLineBuffer - Resize the line buffer to store more data
* @lineptr: Pointer to the line buffer that needs resizing
* @n: Pointer to current size of the buffer
* @bytes_read: Number of bytes read so far, showing the current buffer size.
*
* Return: Pointer to the resized buffer
* * or NULL on failure
*/

char *resizeLineBuffer(char *lineptr, size_t *n, ssize_t bytes_read)
{
char *temp;

*n += BUFFER_SIZE;
temp = malloc(*n);

if (temp == NULL)
{
perror("malloc failed");
return (NULL);
}
_memcpy_custom(temp, lineptr, bytes_read);
free(lineptr);
return (temp);
}

/**
* customGetLine - Read input using a buffer and minimize the use of the read system call
* @lineptr: A pointer to a pointer that will store the read line.
* @n: A pointer to the size of the buffer pointed by lineptr.
* @stream: Input stream from which to read the data.
*
* Return: The number of bytes read,
* or -1 on failure
*/

ssize_t customGetLine(char **lineptr, size_t *n, FILE *stream)
{
static char buf[BUFFER_SIZE];
static size_t buf_index;
static ssize_t bytes_remaining;
ssize_t bytes_read = 0;

if (*lineptr == NULL || *n == 0)
{
	*n = BUFFER_SIZE;
	*lineptr = malloc(*n);

if (*lineptr == NULL)
{
perror("malloc failed");
return (-1);
}
}
while (1)
{
if ((ssize_t)buf_index >= bytes_remaining)
{
if (refillBuffer(stream, buf, &buf_index, &bytes_remaining) <= 0)
return (bytes_read == 0 ? -1 : bytes_read);
}
(*lineptr)[bytes_read] = buf[buf_index];
bytes_read++;
buf_index++;

if ((*lineptr)[bytes_read - 1] == '\n')
{
(*lineptr)[bytes_read] = '\0';
return (bytes_read);
}
if ((size_t)bytes_read == *n)
{
*lineptr = resizeLineBuffer(*lineptr, n, bytes_read);
if (*lineptr == NULL)
return (-1);
}
}
return (-1);
}
