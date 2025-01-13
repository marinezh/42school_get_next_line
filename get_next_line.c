/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhivoto <mzhivoto@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 13:59:30 by mzhivoto          #+#    #+#             */
/*   Updated: 2025/01/13 01:44:26 by mzhivoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>


#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42 // Default buffer size if not defined
#endif

// Helper function to find the newline character
static char *find_newline(const char *str)
{
    if (!str)
        return NULL;
    return strchr(str, '\n');
}

// Helper function to join two strings
static char *str_join(char *s1, const char *s2)
{
    size_t len1 = s1 ? strlen(s1) : 0;
    size_t len2 = s2 ? strlen(s2) : 0;
    char *result = malloc(len1 + len2 + 1);
    if (!result)
        return NULL;
    if (s1)
        strcpy(result, s1);
    if (s2)
        strcpy(result + len1, s2);
    free(s1);
    return result;
}

// Helper function to extract a line from the buffer
static char *extract_line(char **buffer)
{
    char *newline_pos = find_newline(*buffer);
    char *line;
    char *remaining;

    if (newline_pos)
    {
        size_t line_len = newline_pos - *buffer + 1;
        line = strndup(*buffer, line_len);
        remaining = strdup(newline_pos + 1);
        free(*buffer);
        *buffer = remaining;
    }
    else
    {
        line = strdup(*buffer);
        free(*buffer);
        *buffer = NULL;
    }

    return line;
}

// The get_next_line function
char *get_next_line(int fd)
{
    static char *buffer = NULL;
    char *line;
    char temp_buffer[BUFFER_SIZE + 1];
    ssize_t bytes_read;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;

    while (!find_newline(buffer))
    {
        bytes_read = read(fd, temp_buffer, BUFFER_SIZE);
        if (bytes_read < 0)
        {
            free(buffer);
            buffer = NULL;
            return NULL;
        }
        if (bytes_read == 0)
            break;
        temp_buffer[bytes_read] = '\0';
        buffer = str_join(buffer, temp_buffer);
        if (!buffer)
            return NULL;
    }

    if (buffer && *buffer)
        line = extract_line(&buffer);
    else
    {
        free(buffer);
        buffer = NULL;
        return NULL;
    }

    return line;
}
int main()
{
    int fd = open("text.txt", O_RDONLY);
    char *line;

    if (fd < 0)
    {
        perror("Error opening file");
        return 1;
    }

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }

    close(fd);
    return 0;
}