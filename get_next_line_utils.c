/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhivoto <mzhivoto@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:25:16 by mzhivoto          #+#    #+#             */
/*   Updated: 2025/01/13 19:05:05 by mzhivoto         ###   ########.fr       */
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
		i++;
	}
	return (dest);
}
char *str_join(char *s1, const char *s2)
{
    size_t s1_len = 0;
    size_t s2_len = 0;
    char *result;

    while (s1 && s1[s1_len])  // Calculate length of s1
        s1_len++;
    while (s2[s2_len])  // Calculate length of s2
        s2_len++;

    result = malloc(s1_len + s2_len + 1);
    if (!result)
        return NULL;

    if (s1) 
        ft_memcpy(result, s1, s1_len);
    ft_memcpy(result + s1_len, s2, s2_len + 1);

    free(s1);  // Free s1 if it exists
    return result;
}

char *find_newline(const char *str)
{
	if (!str)
		return NULL;
	while (*str)
	{
		if (*str == '\n')
			return (char *)str;
		str++;
	}
	  return NULL;
}

char *extract_line(char **buffer)
{
    char *newline_pos;
    char *line;
    char *remaining;

    if (!buffer || !*buffer)  // Check if the buffer is NULL or empty
        return NULL;
    newline_pos = find_newline(*buffer);  // Find the newline character
    if (newline_pos)
    {
        line = malloc(newline_pos - *buffer + 2);  // +1 for the newline, +1 for '\0'
        if (!line)
            return NULL;
        ft_memcpy(line, *buffer, newline_pos - *buffer + 1);  // Copy line + newline
        line[newline_pos - *buffer + 1] = '\0';  // Null-terminate
        remaining = str_join(NULL, newline_pos + 1);
        if (!remaining)
        {
            free(line);
            return NULL;
        }
        free(*buffer);  // Free the original buffer
        *buffer = remaining;  // Update the buffer with the remaining part
    }
    else
    {
        line = *buffer;  // No newline, take the entire buffer
        *buffer = NULL;  // Set buffer to NULL
    }
    return line;
}

char *read_to_buffer(int fd, char *buffer)
{
	char temp_buffer[BUFFER_SIZE + 1];
	ssize_t bytes_read;

	while (!find_newline(buffer))
	{
		bytes_read = read(fd, temp_buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buffer);
			return NULL;
		}
		if (bytes_read == 0)
			break;
		temp_buffer[bytes_read] = '\0';
		buffer = str_join(buffer, temp_buffer);
		if (!buffer)
			return NULL;
	}

	return buffer;
}
