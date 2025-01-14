#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

#include <stdlib.h>

char	*find_newline(const char *str)
{
	if (!str)
		return (NULL);
	while (*str)
	{
		if (*str == '\n')
			return ((char *)str); // return pointer to the newline
		str++;
	}
	return (NULL);
}
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			i;

	if (!dest && !src)
		return (NULL);
	i = 0;
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

char	*str_join(char *s1, const char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*result;

	s1_len = 0;
	s2_len = 0;
	while (s1 && s1[s1_len])
		s1_len++;
	while (s2[s2_len])
		s2_len++;
	result = malloc(s1_len + s2_len + 1);
	if (!result)
		return (NULL);
	if (s1)
		ft_memcpy(result, s1, s1_len);
	ft_memcpy(result + s1_len, s2, s2_len + 1);
	free(s1);
	return (result);
}
// Shortened version of extract_line
char	*extract_line(char **buffer)
{
	char	*newline_pos;
	char	*line;
	char	*remaining;

	if (!buffer || !*buffer)
		return (NULL);
	newline_pos = find_newline(*buffer); // Locate the newline character
	if (newline_pos)
	{
		// Allocate memory for the line, including '\n' and '\0'
		line = malloc(newline_pos - *buffer + 2);
		if (!line)
			return (NULL);
		// Copy the line including the '\n'
		ft_memcpy(line, *buffer, newline_pos - *buffer + 1);
		line[newline_pos - *buffer + 1] = '\0'; // Null-terminate the string

		// Create a new buffer for the remaining part
		remaining = str_join(NULL, newline_pos + 1); // Copy everything after '\n'
		free(*buffer); // Free the old buffer
		*buffer = remaining; // Update the buffer pointer
	}
	else
	{
		// No newline, return the entire buffer as the last line
		line = str_join(NULL, *buffer); // Duplicate the buffer
		free(*buffer); // Free the buffer
		*buffer = NULL; // Set buffer to NULL
	}
	return (line);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Helper functions like find_newline, ft_memcpy, and str_join should be defined here.

int main()
{
	char *buffer = strdup("Hello\nworld\nThis is a test.");
	char *line;

	while ((line = extract_line(&buffer)) != NULL)
	{
		printf("Extracted line: %s\n", line);
		free(line);
	}

	free(buffer); // Free any remaining buffer (if not NULL)
	return 0;
}
