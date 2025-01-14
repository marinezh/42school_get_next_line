#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

char	*find_newline(const char *str)
{
	if (!str)
		return (NULL);
	while (*str)
	{
		if (*str == '\n')
		{
			// Debug: Show where the newline is found
			//printf("found newline at position %ld\n", str - str);
			return ((char *)str); // return pointer to the newline
		}
			
		str++;
	}
	return (NULL);
}


int main()
{
    char *str = "Hello\nworld!";
    char *newline_pos = find_newline(str);

    // if (newline_pos)
    //     printf("Newline found at position: %ld\n", newline_pos - str);
    // else
    //     printf("No newline found.\n");
    printf("1 Newline found at position d: %d\n", newline_pos - str); // 5
    printf("2 Newline found at position c: %c\n", *newline_pos); // \n
    printf("3 Newline found at position d: %d\n", *newline_pos); // 10 , Since '\n' has an ASCII value of 10 
    printf("4 Newline found at position p: %p\n", newline_pos); // 0x61cbc980300d memory address stored in pointer
    printf("5 Newline found at position p: %p\n", *newline_pos); // 0xa this is 10 in hexadecimal
    return 0;
}

