/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhivoto <mzhivoto@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:25:16 by mzhivoto          #+#    #+#             */
/*   Updated: 2025/01/13 18:16:17 by mzhivoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "get_next_line.h"

// char	*str_join(char *s1, const char *s2)
// {
// 	size_t	str1_len;
// 	size_t	str2_len;
// 	size_t	i;
// 	char	*result;

// 	if (!s1 || !s2)
// 		return (NULL);
// 	str1_len = 0;
// 	str2_len = 0;
// 	if(s1)
//     	while (s1[str1_len])
//         	str1_len++;
//     while (s2[str2_len])
//         str2_len++;
// 	result = (char *)malloc((str1_len + str2_len + 1) * sizeof(char));
// 	if (!result)
// 		return (NULL);
// 	i = 0;
// 	while(*s1)
// 		result[i++] = *s1++;
// 	while (*s2)
// 		result[i++] = *s2++;
// 	result[i] = '\0';
// 	free(s1);
// 	return (result);
// }
char	*str_join(char *s1, const char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;
	char	*result;

	s1_len = 0;
	s2_len = 0;
	i = 0;
	if (s1)
		while (s1[s1_len])
			s1_len++;
	while (s2[s2_len])
		s2_len++;
	result = (char *)malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	while (i < s1_len)
		result[i++] = s1[i];
	while (i < s1_len + s2_len)
		result[i++] = s2[i - s1_len];
	result[i] = '\0';
	if (s1)
		free(s1);
	return (result);
}


// char *str_join(char *s1, const char *s2)
// {
//     size_t len1 = s1 ? strlen(s1) : 0;
//     size_t len2 = s2 ? strlen(s2) : 0;
//     char *result = malloc(len1 + len2 + 1);
//     if (!result)
//         return NULL;
//     if (s1)
//         strcpy(result, s1);
//     if (s2)
//         strcpy(result + len1, s2);
//     free(s1);
//     return result;
// }
// char *ft_strndup(const char *s, size_t n)
// {
//     size_t len = 0;
//     char *dup;

//     while (s[len] && len < n) // Calculate the length to copy
//         len++;

//     dup = (char *)malloc(len + 1); // Allocate memory for the substring
//     if (!dup)
//         return NULL;

//     memcpy(dup, s, len); // Copy the substring into the allocated memory
//     dup[len] = '\0';     // Null-terminate the new string

//     return dup;
// }

char *find_newline(const char *str)
{
    if (!str)
        return NULL;
    return strchr(str, '\n');
}

// Helper function to join two strings


// Helper function to extract a line from the buffer
char *extract_line(char **buffer)
{
    char *newline_pos = find_newline(*buffer);
    char *line;
    char *remaining;

    if (!buffer || !*buffer)
        return NULL;

    if (newline_pos)
    {
        line = str_join(NULL, *buffer);  // Use str_join to duplicate the line up to the newline
        if (!line) return NULL;

        remaining = str_join(NULL, newline_pos + 1);  // Use str_join to duplicate the remainder
        if (!remaining) { free(line); return NULL; }

        free(*buffer);
        *buffer = remaining;
    }
    else
    {
        line = *buffer;
        *buffer = NULL;
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