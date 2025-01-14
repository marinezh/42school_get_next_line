/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhivoto <mzhivoto@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:25:16 by mzhivoto          #+#    #+#             */
/*   Updated: 2025/01/14 18:54:00 by mzhivoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
		// Debug: Show each byte being copiedprintf("ft_memcpy: 
		//copying byte %zu: %c\n", i, s[i]); // Debug: Show each byte being copied
		printf("ft_memcpy: copying byte %zu: %c\n", i, s[i]); 
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
		// Debug: Print the lengths of s1 and s2
	printf("str_join: s1_len=%zu, s2_len=%zu\n", s1_len, s2_len);
	result = malloc(s1_len + s2_len + 1);
	if (!result)
		return (NULL);
	if (s1)
	{
		ft_memcpy(result, s1, s1_len); // Copy s1 into result
		printf("str_join: copied s1='%s'\n", s1);
	}
		
	ft_memcpy(result + s1_len, s2, s2_len + 1); // Copy s2 (including null terminator)
	printf("str_join: copied s2='%s', result='%s'\n", s2, result);

	free(s1);
	return (result);
}

char	*find_newline(const char *str)
{
	if (!str)
		return (NULL);
	while (*str)
	{
		if (*str == '\n')
		{
			// Debug: Show where the newline is found
			printf("find_newline: found newline at position %ld\n", str - str);
			return ((char *)str); // return pointer to the newline
		}
			
		str++;
	}
	return (NULL);
}

char	*extract_line(char **buffer)
{
	char	*newline_pos;
	char	*line;
	char	*remaining;

	if (!buffer || !*buffer)
		return (NULL);

	// Find the newline position in the buffer
	newline_pos = find_newline(*buffer);
	if (newline_pos) // If a newline is found
	{
		// Allocate memory for the line (including the newline)
		line = malloc(newline_pos - *buffer + 2); // +1 for newline, +1 for null terminator
		if (!line)
			return (NULL); // If memory allocation fails, return NULL
		// Copy the line including the newline character
		ft_memcpy(line, *buffer, newline_pos - *buffer + 1);
		line[newline_pos - *buffer + 1] = '\0'; // Null-terminate the line

		// Allocate memory for the remaining buffer after the newline
		remaining = str_join(NULL, newline_pos + 1);
		free(*buffer); // Free the original buffer
		*buffer = remaining; // Update the buffer to the remaining part after the newline

		// Debug: Show the extracted line and remaining buffer
		printf("extract_line: line='%s', remaining='%s'\n", line, remaining);
	}
	else // If no newline is found, take the entire buffer as the line
	{
		line = str_join(NULL, *buffer); // Copy the whole buffer to line
		free(*buffer); // Free the buffer
		*buffer = NULL; // Set buffer to NULL

		// Debug: Show the extracted line and the buffer is now NULL
		printf("extract_line: line='%s', remaining=NULL\n", line);
	}
	return (line);
}

char *read_to_buffer(int fd, char *buffer)
{
	char temp_buffer[BUFFER_SIZE + 1];  // Temporary buffer for reading from the file
	ssize_t bytes_read;

	// Keep reading until a newline is found in the buffer
	while (!find_newline(buffer))
	{
		bytes_read = read(fd, temp_buffer, BUFFER_SIZE);  // Read up to BUFFER_SIZE bytes
		if (bytes_read < 0)  // If read failed
		{
			free(buffer);  // Free the buffer
			return NULL;  // Return NULL on error
		}
		if (bytes_read == 0)  // If end of file is reached
			break;

		// Null-terminate the temporary buffer
		temp_buffer[bytes_read] = '\0';  
		printf("read_to_buffer: read %zd bytes='%s'\n", bytes_read, temp_buffer);

		// Concatenate the temporary buffer to the existing buffer
		buffer = str_join(buffer, temp_buffer);
		if (!buffer)
			return NULL;// Free buffer if memory allocation fails
		
		// Debug: Show the updated buffer
		printf("read_to_buffer: buffer='%s'\n", buffer);
	}
	return buffer;  // Return the updated buffer
}
char *get_next_line(int fd)
{
	static char *buffer = NULL;  // Static buffer to hold the file data between calls
	char *line;

	// Check for invalid file descriptor or invalid buffer size
	if (fd < 0 || BUFFER_SIZE <= 0)
		return NULL;

	// Read data from file to buffer
	buffer = read_to_buffer(fd, buffer);
	if (!buffer)
		return NULL;  // If reading fails, return NULL

	if (*buffer)  // If buffer has data
		line = extract_line(&buffer);  // Extract the next line
	else
	{
		free(buffer);  // Free buffer if empty
		buffer = NULL;
		return NULL;  // Return NULL if no data left
	}

	return line;  // Return the extracted line
}

int main()
{
	int fd = open("text.txt", O_RDONLY);  // Open the file
	char *line;

	if (fd < 0)  // If the file cannot be opened, print error and exit
	{
		perror("Error opening file");
		return 1;
	}

	// Loop through each line in the file
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("Read line: '%s'\n", line);  // Print the extracted line
		free(line);  // Free the memory used by the line
	}

	close(fd);  // Close the file
	return 0;
}