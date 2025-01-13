/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhivoto <mzhivoto@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 13:59:30 by mzhivoto          #+#    #+#             */
/*   Updated: 2025/01/13 17:30:59 by mzhivoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// Helper function to find the newline character

char *get_next_line(int fd)
{
    static char *buffer = NULL;
    char *line;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;

    buffer = read_to_buffer(fd, buffer);
    if (!buffer)
        return NULL;

    if (*buffer)
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