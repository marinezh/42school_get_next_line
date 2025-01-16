/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhivoto <mzhivoto@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 13:59:30 by mzhivoto          #+#    #+#             */
/*   Updated: 2025/01/15 13:37:10 by mzhivoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	*buffer[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer[fd] = read_to_buffer(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	if (*buffer[fd])
		line = extract_line(&buffer[fd]);
	else
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
		return (NULL);
	}
	return (line);
}
// printf("line for fd %d is: %s", fd, line);
	// printf("fd is %d:", fd);
// #include <stdio.h>
// int main()
// {
// 	int fd = open("text.txt", O_RDONLY);
// 	int fd1 = open("text1.txt", O_RDONLY);
// 	printf("fd: %d; fd1: %d\n", fd, fd1);
// 	char *line;
// 	char *line1;

// 	while (line || line1)
// 	{
// 		line = get_next_line(fd);
// 		line1 = get_next_line(fd1);
// 		if (line1 == NULL || line == NULL)
// 			break;
// 		printf("%s", line);
// 		printf("%s", line1);
// 		free(line);
// 		free(line1);
// 	}
// 	free(line);
// 	free(line1);
// 	close(fd);
// 	close(fd1);
// 	return 0;
// }