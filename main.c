/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhivoto <mzhivoto@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 01:16:52 by mzhivoto          #+#    #+#             */
/*   Updated: 2025/01/13 01:42:51 by mzhivoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

// int main()
// {
// 	int fd = open("text.txt", O_RDONLY);
// 	char *line;

// 	if (fd < 0)
// 	{
// 		printf("Error");
// 		return(1);
// 	}
// 	line = get_next_line(fd);
// 	while (line != NULL)
// 	{
// 		printf("%s", line);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	close(fd);
// 	return (0);
// }
#include <fcntl.h>
#include <stdio.h>

int main()
{
    int fd = open("example.txt", O_RDONLY);
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