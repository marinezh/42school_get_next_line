/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhivoto <mzhivoto@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:25:16 by mzhivoto          #+#    #+#             */
/*   Updated: 2025/01/15 12:20:27 by mzhivoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 32  // Define a buffer size (adjust as needed)

// Function to copy memory from src to dest
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*d = (unsigned char *)dest;
	unsigned char	*s = (unsigned char *)src;
	for (size_t i = 0; i < n; i++)
		d[i] = s[i];
	return dest;
}

// Function to join two strings (s1 and s2)
char *str_join(char *s1, const char *s2)
{
	size_t s1_len = s1 ? strlen(s1) : 0;
	size_t s2_len = strlen(s2);
	char *result = malloc(s1_len + s2_len + 1);
	if (!result) return NULL;
	if (s1) ft_memcpy(result, s1, s1_len);
	ft_memcpy(result + s1_len, s2, s2_len + 1);
	free(s1);
	return result;
}

// Function to find the first newline character in a string
char *find_newline(const char *str)
{
	while (*str)
		if (*str++ == '\n') return (char *)(str - 1);
	return NULL;
}

// Function to read data from file into buffer until newline or EOF is found
char *read_to_buffer(int fd, char *buffer)
{
	char temp_buffer[BUFFER_SIZE + 1];
	ssize_t bytes_read;
	while (!find_newline(buffer))
	{
		bytes_read = read(fd, temp_buffer, BUFFER_SIZE);
		if (bytes_read <= 0) return bytes_read < 0 ? NULL : buffer;
		temp_buffer[bytes_read] = '\0';
		buffer = str_join(buffer, temp_buffer);
		if (!buffer) return NULL;
	}
	return buffer;
}

// Function to extract the next line from the buffer
// char *get_next_line(int fd)
// {
// 	static char *buffer = NULL;
// 	if (fd < 0 || BUFFER_SIZE <= 0) return NULL;
// 	buffer = read_to_buffer(fd, buffer);
// 	if (!buffer || !*buffer) return NULL;
// 	char *newline_pos = find_newline(buffer);
// 	size_t line_len = newline_pos ? newline_pos - buffer + 1 : strlen(buffer);
// 	char *line = malloc(line_len + 1);
// 	if (!line) return NULL;
// 	ft_memcpy(line, buffer, line_len);
// 	line[line_len] = '\0';
// 	if (newline_pos) buffer = str_join(NULL, newline_pos + 1);
// 	else { free(buffer); buffer = NULL; }
// 	return line;
// }

// int main()
// {
// 	int fd = open("text.txt", O_RDONLY);
// 	if (fd < 0) { perror("Error opening file"); return 1; }
// 	char *line;
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return 0;
// }



