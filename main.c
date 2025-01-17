/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhivoto <mzhivoto@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 01:16:52 by mzhivoto          #+#    #+#             */
/*   Updated: 2025/01/16 15:34:38 by mzhivoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

int main()
{
	int fd = open("text.txt", O_RDONLY);
	//int fd = 0;
	char *line;


	while (1)
	{
		line = get_next_line(fd);
		
		printf("%s", line);
		if (line == NULL)
			break;
		
		free(line);
	}
		close(fd);
	return 0;
}
// int main()
// {
// 	int fd = open("text.txt", O_RDONLY);
// 	int fd1 = open("text1.txt", O_RDONLY);
// 	printf("fd: %d; fd1: %d\n", fd, fd1);
// 	char *line;
// 	char *line1;

// 	while (1)
// 	{
// 		line = get_next_line(fd);
// 		line1 = get_next_line(fd1);
// 		printf("%s", line);
// 		printf("%s", line1);
// 		if (line1 == NULL || line == NULL)
// 			break;
// 		free(line);
// 		free(line1);
// 	}
// 	close(fd);
// 	close(fd1);
// 	return 0;
// }
